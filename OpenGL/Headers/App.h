#pragma once
#include "IncludeGL.h"
#include <vector>
#include <irrKlang/irrKlang.h>
#include <chrono>

#include "GameObject.h"
#include "Camera.h"

#include "Scene.h"

namespace Core
{
	struct AppInitialiser
	{
		unsigned int widht;
		unsigned int height;
		unsigned int majorVersion;
		unsigned int minorVersion;
		const char* name;
		void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void (*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei leght, const GLchar* message, const void* userParam);
	};

	struct SpeedTestResult
	{
		int iteration = 0;
		float total = 0;
		float average = 0;
	};

	class App
	{
	public:
		GLFWwindow* window;

	private:
		int reloadCount = 0;
		int currentScene = 0;
		lowRenderer::Camera* camera;

		lowRenderer::Inputs inputs;

		std::vector<Resource::Scene*> scenes;
		std::chrono::high_resolution_clock::time_point reloadTestStart;

		bool mouseCaptured;

		void NewFrame(bool mouseCaptured);
		void EndFrame();

		Resource::ResourceManager resourcesManager;

		bool reloadTest;
		int reloadToDo = 5;
		SpeedTestResult speedTestResult;

		bool reload;

		irrklang::ISoundEngine* soundEngine;

		void StartLoadSpeedTest();
		void HandleLoadSpeedTest();

		void ImGui();

	public:
		void Init(AppInitialiser initializer);

		void Update();
		void processInput(GLFWwindow* window);

		void SetActiveScene(int id);

		void AddScene(Resource::Scene* scene);

		Resource::ResourceManager* GetRessourceManager() { return &resourcesManager; }

		void ResetCamera();

		~App();
	};
}