#include "Scene1.h"

using namespace Resource;

void Scene1::Init(Resource::ResourceManager& resourcesManager) 
{
	Clear();
	reloadStart = std::chrono::high_resolution_clock::now();

	musicFile = "Resources/Sounds/Scene1.ogg";

	// Create shader
	Resource::Shader* shader = (Resource::Shader*)resourcesManager.Get<Resource::Texture>("Shader");
	if (shader == nullptr)
	{
		shader = (Resource::Shader*)resourcesManager.Create<Resource::Shader>("Shader", "Shader");
		shader->createShader("Resources/Shaders/vertexShader.glsl", "Resources/Shaders/fragmentShader.glsl");
	}

	// Create Textures
	Resource::Texture* wallTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("wallTexture");
	if (wallTexture == nullptr)
		wallTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/wall.jpg", "wallTexture");

	Resource::Texture* companionTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("companionTexture");
	if (companionTexture == nullptr)
		companionTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/companion.png", "companionTexture");

	Resource::Texture* ahriTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("ahriTexture");
	if (ahriTexture == nullptr)
		ahriTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/Ahri.png", "ahriTexture");

	Resource::Texture* baronTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("baronTexture");
	if (baronTexture == nullptr)
		baronTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/nashor.png", "baronTexture");

	Resource::Texture* keyTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("keyTexture");
	if (keyTexture == nullptr)
		keyTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/key.png", "keyTexture");

	Resource::Texture* clankTexture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>("clankTexture");
	if (clankTexture == nullptr)
		clankTexture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>("Resources/Textures/clank.png", "clankTexture");
		
	// Create models
	Resource::Model* cubeModel = (Resource::Model*)resourcesManager.Get<Resource::Model>("cubeModel");
	if (cubeModel == nullptr)
		cubeModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/cube.obj", "cubeModel");

	Resource::Model* companionModel = (Resource::Model*)resourcesManager.Get<Resource::Model>("companionModel");
	if (companionModel == nullptr)
		companionModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/companion.obj", "companionModel");

	Resource::Model* ahriModel = (Resource::Model*)resourcesManager.Get<Resource::Model>("ahriModel");
	if (ahriModel == nullptr)
		ahriModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/Ahri.obj", "ahriModel");

	Resource::Model* baronModel = (Resource::Model*)resourcesManager.Get<Resource::Model>("baronModel");
	if (baronModel == nullptr)
		baronModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/baron.obj", "baronModel");

	Resource::Model* castleModel = (Resource::Model*)resourcesManager.Get<Resource::Model>("castleModel");
	if (castleModel == nullptr)
		castleModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/castle.obj", "castleModel");

	Resource::Model* keyModel = (Resource::Model*)resourcesManager.Get<Resource::Model>("keyModel");
	if (keyModel == nullptr)
		keyModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/key.obj", "keyModel");
	
	Resource::Model* clankModel = (Resource::Model*)resourcesManager.Get<Resource::Model>("clankModel");
	if (clankModel == nullptr)
		clankModel = (Resource::Model*)resourcesManager.Create<Resource::Model>("Resources/Obj/clank.obj", "clankModel");
		
	// Create and add light
	lowRenderer::Light* dirlight = new lowRenderer::Light("Directional", lowRenderer::lightType::LT_DIRECTIONAL, 1);
	dirlight->SetDir(myMaths::Float3(0.f, -1.f, 0.f));
	dirlight->SetLight(myMaths::Float3(0.5f, 0.5f, 0.5f), myMaths::Float3(1.f, 1.f, 1.f), myMaths::Float3(0.25f, 0.25f, 0.25f));
	dirlight->SetIntensity(0.5f);
	dirlight->setActive(true);
	AddLight(dirlight);

	lowRenderer::Light* pointLight = new lowRenderer::Light("Point", lowRenderer::lightType::LT_POINT, 2);
	pointLight->SetPos(myMaths::Float3(3.f, 3.0f, 2.f));
	pointLight->SetLight(myMaths::Float3(0.f, 0.f, 0.f), myMaths::Float3(1.f, 1.f, 1.f), myMaths::Float3(0.f, 0.f, 0.f));
	pointLight->setAtenuation(1.0f, 0.09f, 0.032f);
	pointLight->setActive(false);
	AddLight(pointLight);

	lowRenderer::Light* spotLight = new lowRenderer::Light("Spot 1", lowRenderer::lightType::LT_SPOT, 3);
	spotLight->SetPos(myMaths::Float3(-3.5f, 2.0f, 5.f));
	spotLight->SetDir(myMaths::Float3(0.f, -0.f, -1.f));
	spotLight->SetLight(myMaths::Float3(0.f, 0.f, 0.f), myMaths::Float3(1.f, 1.f, 1.f), myMaths::Float3(0.2f, 0.2f, 0.2f));
	spotLight->setAtenuation(1.0f, 0.09f, 0.032f);
	spotLight->setActive(true);
	spotLight->SetCutOff(1);
	spotLight->SetOuterCutOff(0.90f);
	spotLight->SetIntensity(6);
	AddLight(spotLight);

	lowRenderer::Light* spotLight2 = new lowRenderer::Light("Spot 2", lowRenderer::lightType::LT_SPOT, 4);
	spotLight2->SetPos(myMaths::Float3(3.5f, 2.0f, 5.f));
	spotLight2->SetDir(myMaths::Float3(0.f, 0.f, -1.f));
	spotLight2->SetLight(myMaths::Float3(0.f, 0.f, 0.f), myMaths::Float3(0.6f, 0.3f, 1.f), myMaths::Float3(0.2f, 0.2f, 0.2f));
	spotLight2->setAtenuation(1.0f, 0.09f, 0.032f);
	spotLight2->SetCutOff(1);
	spotLight2->SetOuterCutOff(0.90f);
	spotLight2->setActive(true);
	spotLight2->SetIntensity(20);
	AddLight(spotLight2);

	// Create Meshes
	// ------------------------------------------------
	lowRenderer::Mesh* cubeMesh = new lowRenderer::Mesh(cubeModel, wallTexture, shader);
	meshes.push_back(cubeMesh);
	lowRenderer::Mesh* portalMesh = new lowRenderer::Mesh(companionModel, companionTexture, shader);
	meshes.push_back(portalMesh);
	lowRenderer::Mesh* baronMesh = new lowRenderer::Mesh(baronModel, baronTexture, shader);
	meshes.push_back(baronMesh);
	lowRenderer::Mesh* ahriMesh = new lowRenderer::Mesh(ahriModel, ahriTexture, shader);
	meshes.push_back(ahriMesh);
	lowRenderer::Mesh* castleMesh = new lowRenderer::Mesh(castleModel, wallTexture, shader);
	meshes.push_back(castleMesh);
	lowRenderer::Mesh* keyMesh = new lowRenderer::Mesh(keyModel, keyTexture, shader);
	meshes.push_back(keyMesh);
	lowRenderer::Mesh* clankMesh = new lowRenderer::Mesh(clankModel, clankTexture, shader);
	meshes.push_back(clankMesh);
	
	// Create and add object
	// ------------------------------------------------
	lowRenderer::GameObject* cube = new lowRenderer::GameObject(cubeMesh);
	cube->name = "Cube";
	cube->position = myMaths::Float3(3.f, -1.f, 0.f);
	AddObject(cube);

	lowRenderer::GameObject* cube2 = new lowRenderer::GameObject(cubeMesh);
	cube2->name = "Cube 2";
	cube2->position = myMaths::Float3(-3.f, -1.f, 0.f);
	AddObject(cube2);

	lowRenderer::GameObject* portal = new lowRenderer::GameObject(portalMesh);
	portal->scale = myMaths::Float3(0.01f, 0.01f, 0.01f);
	portal->name = "Portal cube (not child of everything)";
	AddObject(portal);

	lowRenderer::GameObject* baron = new lowRenderer::GameObject(baronMesh);
	cube->AddChild(*baron);
	baron->position = myMaths::Float3(0.f, 0.9f, 0.f);
	baron->scale = myMaths::Float3(0.01, 0.01, 0.01);
	baron->name = "Baron";
	AddObject(baron);

	lowRenderer::GameObject* ahri = new lowRenderer::GameObject(ahriMesh);
	cube2->AddChild(*ahri);
	ahri->position = myMaths::Float3(0.f, 1.f, 0.f);
	ahri->name = "Ahri";
	AddObject(ahri);

	lowRenderer::GameObject* castle = new lowRenderer::GameObject(castleMesh);
	castle->position = myMaths::Float3(0.f, -100.f, 0.f);
	castle->name = "castle";
	AddObject(castle);

	lowRenderer::GameObject* key = new lowRenderer::GameObject(keyMesh);
	key->position = myMaths::Float3(-1.f, 1.f, -1.f);
	key->scale = myMaths::Float3(0.02f, 0.02f, 0.02f);
	key->rotation = myMaths::Float3(0.f, 0.f, 320.f);
	key->name = "key";
	AddObject(key);
	
	lowRenderer::GameObject* clank = new lowRenderer::GameObject(clankMesh);
	clank->position = myMaths::Float3(0.f, -1.f, -3.f);
	clank->scale = myMaths::Float3(0.3f, 0.3f, 0.3f);
	clank->name = "Clank (not child of everything)";
	AddObject(clank);

	lowRenderer::GameObject* everything = new lowRenderer::GameObject(nullptr);
	everything->position = myMaths::Float3(0.f, 0.f, 0.f);
	everything->AddChild(*cube);
	everything->AddChild(*cube2);
	everything->AddChild(*castle);
	everything->AddChild(*key);
	everything->name = "Everything";
	AddObject(everything);
}