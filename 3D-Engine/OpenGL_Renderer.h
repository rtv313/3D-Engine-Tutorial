#ifndef __RENDER_OBJECT_H_
#define __RENDER_OBJECT_H_

#include "Tutorial03-Triangle.h"
#include "Tutorial04-Shader.h"
#include "Tutorial05-UniformVariables.h"
#include "GeometryTexture.h"
#include "GeometryTransformation.h"
#include "GeometryWithTransformView.h"
#include "BasicTutorialCamera.h"
#include "Colors.h"
#include "BasicLigthing.h"
#include "MaterialTutorial.h"
#include "LigthingMaps.h"
#include "DirectionalLightTutorial.h"
#include "PointLightTutorial.h"
#include "SpotLightTutorial.h"
#include "MultipleLightsTutorial.h"
#include "Model.h"
#include "SceneGraph.h"
#include "ModuleScene.h"

class OpenGL_Renderer {
public:
	OpenGL_Renderer();
	~OpenGL_Renderer();
	void RenderOpenGL();
private:
	//BasicTriangle basicTriangle;
	//TriangleWithShader *shaderTriangle;
	//TriangleWithShaderUniformVar *uniformVarTriangle;
	//TutorialTexture * tutorialTexture;
	//TutorialTransforms * tutorialTransform;
	//TutorialTransformProjectionViewModel * tutorialProjectionView;
	//TutorialBasicCamera * tutorialBasicCamera;
	//BasicColorTutorial * colorTutorial;
	//BasicLighting * basicLight;
	//MaterialTutorial * materialTutorial;
	//LightingMaps * lightMapsTutorial;
	//DirectionalLightTutorial *directionalLightTutorial;
	//PointLightTutorial *pointLigthTutorial;
	//SpotLightTutorial * spotLightTutorial;
	//MultipleLightsTutorial * multipleLightsTutorial;
	/*Model* nanosuit; */
	/*SceneGraph * sceneGraph;*/
	/*GameObject * gameObject; */
	ModuleScene *moduleScene;
	
}; 
#endif // !__RENDER_OBJECT_H_
