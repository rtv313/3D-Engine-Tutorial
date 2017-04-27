#include "OpenGL_Renderer.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glm/glm.hpp"
#include "glm/vec3.hpp" // glm::vec3


OpenGL_Renderer::OpenGL_Renderer() 
{
	//shaderTriangle = new TriangleWithShader();
	//uniformVarTriangle = new TriangleWithShaderUniformVar();
	//tutorialTexture = new TutorialTexture();
	//tutorialTransform = new TutorialTransforms();
	//tutorialProjectionView = new TutorialTransformProjectionViewModel();
	//tutorialBasicCamera = new TutorialBasicCamera();
	//colorTutorial = new BasicColorTutorial();
	//basicLight = new BasicLighting();
	//materialTutorial = new MaterialTutorial();
	//lightMapsTutorial = new LightingMaps();
	//directionalLightTutorial = new DirectionalLightTutorial();
	//pointLigthTutorial = new PointLightTutorial();
	//spotLightTutorial = new SpotLightTutorial();
	//multipleLightsTutorial = new MultipleLightsTutorial();
	nanosuit = new Model("../Models/street/Street.obj");
	sceneGraph = new SceneGraph("../Models/street/Street.obj");

}
OpenGL_Renderer::~OpenGL_Renderer() 
{
	//delete shaderTriangle;
	//delete uniformVarTriangle;
	//delete tutorialTexture;
	//delete tutorialTransform;
	//delete tutorialProjectionView;
	//delete tutorialBasicCamera;
	//delete colorTutorial;
	//delete basicLight;
	//delete materialTutorial;
	//delete lightMapsTutorial;
	//delete directionalLightTutorial;
	//delete pointLigthTutorial;
	//delete spotLightTutorial;
	//delete multipleLightsTutorial;
	delete nanosuit;
	delete sceneGraph;
}

void  OpenGL_Renderer::RenderOpenGL()
{
	nanosuit->Draw();
	//sceneGraph->Draw();

	
}

