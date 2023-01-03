#include "Scene2.h"

using namespace Resource;

void Scene2::Init(Resource::ResourceManager& resourcesManager)
{
	Clear();
	reloadStart = std::chrono::high_resolution_clock::now();
	musicFile = "Resources/Sounds/Scene2.ogg";

	// Create shader
	Resource::Shader* shader = (Resource::Shader*)resourcesManager.Get<Resource::Texture>("Shader");
	if (shader == nullptr)
	{
		shader = (Resource::Shader*)resourcesManager.Create<Resource::Shader>("Shader", "Shader");
		shader->createShader("Resources/Shaders/vertexShader.glsl", "Resources/Shaders/fragmentShader.glsl");
	}

	// Create Textures
	Resource::Texture* wallTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("wallTexture");
	if(wallTexture == nullptr)
		wallTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/wall.jpg", "wallTexture");

	Resource::Texture* companionTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("companionTexture");
	if (companionTexture == nullptr)
		companionTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/companion.png", "companionTexture");

	Resource::Texture* ahriTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("ahriTexture");
	if (ahriTexture == nullptr)
		ahriTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/Ahri.png", "ahriTexture");

	// Create models
	Resource::Model* cubeModel = (Resource::Model*)resourcesManager.Get<Resource::Texture>("cubeModel");
	if (cubeModel == nullptr)
		cubeModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/cube.obj", "cubeModel");
	
	Resource::Model* companionModel = (Resource::Model*)resourcesManager.Get<Resource::Texture>("companionModel");
	if (companionModel == nullptr)
		companionModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/companion.obj", "companionModel");
	
	Resource::Model* ahriModel = (Resource::Model*)resourcesManager.Get<Resource::Texture>("ahriModel");
	if (ahriModel == nullptr)
		ahriModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/Ahri.obj", "ahriModel");

	// Create and add light
	lowRenderer::Light* dirlight = new lowRenderer::Light("Directional", lowRenderer::lightType::LT_DIRECTIONAL, 1);
	dirlight->SetDir(myMaths::Float3(0.f, -1.f, 0.f));
	dirlight->SetLight(myMaths::Float3(0.5f, 0.5f, 0.5f), myMaths::Float3(1.f, 1.f, 1.f), myMaths::Float3(0.25f, 0.25f, 0.25f));
	dirlight->SetIntensity(0.5f);
	dirlight->setActive(true);
	AddLight(dirlight);

	lowRenderer::Light* spotLightBlue = new lowRenderer::Light("Spot Blue", lowRenderer::lightType::LT_SPOT, 2);
	spotLightBlue->SetPos(myMaths::Float3(1.5f, 8.0f, 0.f));
	spotLightBlue->SetDir(myMaths::Float3(0.f, -1.f, 0.f));
	spotLightBlue->SetLight(myMaths::Float3(0.f, 0.f, 0.f), myMaths::Float3(0.f, 0.f, 1.f), myMaths::Float3(0.2f, 0.2f, 0.2f));
	spotLightBlue->setAtenuation(1.0f, 0.09f, 0.032f);
	spotLightBlue->SetCutOff(1);
	spotLightBlue->SetOuterCutOff(0.90f);
	spotLightBlue->setActive(true);
	spotLightBlue->SetIntensity(40);
	AddLight(spotLightBlue);

	lowRenderer::Light* spotLightRed = new lowRenderer::Light("Spot Red", lowRenderer::lightType::LT_SPOT, 3);
	spotLightRed->SetPos(myMaths::Float3(-1.f, 8.0f, -1.5f));
	spotLightRed->SetDir(myMaths::Float3(0.f, -1.f, -0.f));
	spotLightRed->SetLight(myMaths::Float3(0.f, 0.f, 0.f), myMaths::Float3(1.f, 0.f, 0.f), myMaths::Float3(0.2f, 0.2f, 0.2f));
	spotLightRed->setAtenuation(1.0f, 0.09f, 0.032f);
	spotLightRed->SetCutOff(1);
	spotLightRed->SetOuterCutOff(0.90f);
	spotLightRed->setActive(true);
	spotLightRed->SetIntensity(40);
	AddLight(spotLightRed);

	lowRenderer::Light* spotLightGreen = new lowRenderer::Light("Spot Green", lowRenderer::lightType::LT_SPOT, 4);
	spotLightGreen->SetPos(myMaths::Float3(1.5f, 8.0f, -2.f));
	spotLightGreen->SetDir(myMaths::Float3(0.f, -1.f, 0.f));
	spotLightGreen->SetLight(myMaths::Float3(0.f, 0.f, 0.f), myMaths::Float3(0.f, 1.f, 0.f), myMaths::Float3(0.2f, 0.2f, 0.2f));
	spotLightGreen->setAtenuation(1.0f, 0.09f, 0.032f);
	spotLightGreen->SetCutOff(1);
	spotLightGreen->SetOuterCutOff(0.90f);
	spotLightGreen->setActive(true);
	spotLightGreen->SetIntensity(40);
	AddLight(spotLightGreen);

	// Create Meshes
	// ------------------------------------------------
	lowRenderer::Mesh* cubeMesh = new lowRenderer::Mesh(cubeModel, wallTexture, shader);
	meshes.push_back(cubeMesh);
	lowRenderer::Mesh* portalMesh = new lowRenderer::Mesh(companionModel, companionTexture, shader);
	meshes.push_back(portalMesh);
	lowRenderer::Mesh* ahriMesh = new lowRenderer::Mesh(ahriModel, ahriTexture, shader);
	meshes.push_back(ahriMesh);

	// Create and add object
	// ------------------------------------------------
	lowRenderer::GameObject* cube = new lowRenderer::GameObject(cubeMesh);
	cube->name = "Big Boy";
	cube->position = myMaths::Float3(0.f, -2.5f, 0.f);
	cube->scale = myMaths::Float3(5.f, 5.f, 5.f);
	AddObject(cube);

	lowRenderer::GameObject* portal = new lowRenderer::GameObject(portalMesh);
	portal->position = myMaths::Float3(0.270f, 1.3f, 0.15f);
	portal->scale = myMaths::Float3(0.005f, 0.005f, 0.005f);
	portal->rotation = myMaths::Float3(0.f,170.f, 0.f);
	portal->name = "Portal cube";
	cube->AddChild(*portal);
	AddObject(portal);

	lowRenderer::GameObject* ahri = new lowRenderer::GameObject(ahriMesh);
	cube->AddChild(*ahri);
	ahri->position = myMaths::Float3(-0.270f, 1.f, -0.400f);
	ahri->scale = myMaths::Float3(0.2f, 0.2f, 0.2f);
	ahri->rotation = myMaths::Float3(0.f, 40.f, 0.f);
	ahri->name = "Ahri";
	AddObject(ahri);

	lowRenderer::GameObject* everything = new lowRenderer::GameObject(nullptr);
	everything->position = myMaths::Float3(0.f, -2.f, 0.f);
	everything->AddChild(*cube);
	everything->name = "Everything";
	AddObject(everything);
}