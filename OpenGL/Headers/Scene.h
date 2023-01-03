#pragma once
#include <vector>
#include <ImGUI/imgui.h>
#include <chrono>

#include "Resources.h"
#include "GameObject.h"
#include "Light.h"
#include "Camera.h"


namespace Resource
{
	class Scene
	{
	protected:
		std::vector<lowRenderer::GameObject*> objects;
		std::vector<lowRenderer::Light*> lights;
		std::vector<lowRenderer::Mesh*> meshes;

		std::chrono::high_resolution_clock::time_point reloadStart;

		bool isLoaded = false;
		const char* musicFile;

		void ImGui();

	public:
		bool IsLoaded() { return isLoaded; }

		const char* getMusicFile() { return musicFile; }

		std::string name = "New Scene";

		void Render(lowRenderer::Camera* camera);

		int GetObjectCount() { return objects.size(); }
		int GetLightCount() { return lights.size(); }

		void AddObject(lowRenderer::GameObject* obj);
		void AddLight(lowRenderer::Light* obj);

		void TurnOffAllLights();

		void Clear();

		~Scene();

		
		virtual void Init(Resource::ResourceManager& resourcesManager) = 0;

		void Reload(Resource::ResourceManager& resourcesManager);

		bool CheckLoadedModel();
	};
}