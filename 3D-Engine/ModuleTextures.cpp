#include "ModuleTextures.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"
#include <cassert>
#pragma comment(lib, "DevIL/lib/x86/Release/DevIL.lib")
#pragma comment(lib, "DevIL/lib/x86/Release/ILU.lib")
#pragma comment(lib, "DevIL/lib/x86/Release/ILUT.lib")

ModuleTextures::ModuleTextures()
{
}

bool ModuleTextures::Init() 
{
	// Initialize IL
	ilInit();
	// Initialize ILU
	iluInit();
	// Initialize ILUT with OpenGL support.
	ilutRenderer(ILUT_OPENGL);

	return true;
}

// Destructor
ModuleTextures::~ModuleTextures()
{
	CleanUp();
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");
	for (auto it = textures.begin(); it != textures.end(); ++it)
	{
		glDeleteTextures(1, &it->second);
	}

	textures.clear();
	return true;
}

// Load new texture from file path
GLuint const ModuleTextures::Load(const char* path)
{
	GLuint imageId;
	bool success;			// Create a flag to keep track of success/failure
	ILenum error;				// Create a flag to keep track of the IL error state
	ilGenImages(1, &imageId); 		// Generate the image ID
	ilBindImage(imageId); 			// Bind the image


	if (textures.count(path) > 0) { //check if exists
		return textures[path];
	}

	success = ilLoadImage(path);

	if (!success)
	{
		error = ilGetError();
		LOG("Image conversion failed - IL reports error: %S - %S ", error , iluErrorString(error));
		exit(-1);
	}


	
	ILinfo ImageInfo;
	iluGetImageInfo(&ImageInfo);
	if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
	{
		iluFlipImage();
	}

	int channels = ilGetInteger(IL_IMAGE_CHANNELS);

	if (channels == 3)
	{
		ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
	}
	else if (channels == 4)
	{
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	}
	


	ILubyte * pixmap = ilGetData();
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);

	glGenTextures(1, &imageId);
	glBindTexture(GL_TEXTURE_2D, imageId); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Create texture and generate mipmaps

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), width,
		height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, pixmap);

	glGenerateMipmap(GL_TEXTURE_2D);

	ilDeleteImages(1,&imageId);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	textures[path] = imageId;

	return imageId;
	
}

