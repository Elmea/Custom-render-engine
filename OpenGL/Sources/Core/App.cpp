#include <iostream>
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_opengl3.h>
#include <ImGUI/imgui_impl_glfw.h>

#include "App.h"
#include "Camera.h"
#include "Debug.h"
#include "Resources.h"

using namespace Core;

void App::Init(AppInitialiser initializer)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, initializer.majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, initializer.minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


	// glfw window creation
	// --------------------
	window = glfwCreateWindow(initializer.widht, initializer.height, initializer.name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, initializer.framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(initializer.glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	camera = new lowRenderer::Camera(initializer.widht, initializer.height, 0.1f, -10.f, 10.f, -10.f, 10.f, 0.1f, 1000.f, 60.f);
	camera->setProjection(lowRenderer::ViewType::VT_PERSPECTIVE);
	camera->position = myMaths::Float3(0.f, 3.f, 10.f);

	// Setup Dear ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	soundEngine = irrklang::createIrrKlangDevice();
}

void App::ResetCamera()
{
	camera->position.x = 0.f;
	camera->position.y = 3.f;
	camera->position.z = 10.f;

	camera->rotation.x = 0.f;
	camera->rotation.y = 0.f;
	camera->rotation.z = 0.f;

	camera->setSpeed(0.1f);
}


void App::Update()
{
	SetActiveScene(0);
	Core::Debug::log.Print("Je commence dessiner :D");

	while (!glfwWindowShouldClose(window))
	{
		HandleLoadSpeedTest();

		// input
		// -----
		glfwPollEvents();
		processInput(window);
		NewFrame(mouseCaptured);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[currentScene]->CheckLoadedModel();

		camera->CalcVP();
		camera->Update(inputs);
		scenes[currentScene]->Render(camera);

		ImGui();

		EndFrame();

		if (reload)
			scenes[currentScene]->Reload(resourcesManager);
	}
}

void App::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (mouseCaptured)
		{
			mouseCaptured = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	if (mouseCaptured)
	{
		inputs.forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		inputs.backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		inputs.left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		inputs.right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		inputs.up = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		inputs.down = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

		inputs.accelerate = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
		inputs.slowDown = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;

		double newMouseX, newMouseY;
		glfwGetCursorPos(window, &newMouseX, &newMouseY);
		inputs.mouseDeltaX = newMouseX - inputs.mouseX;
		inputs.mouseDeltaY = newMouseY - inputs.mouseY;

		inputs.mouseX = newMouseX;
		inputs.mouseY = newMouseY;
	}
	else
	{
		inputs.forward = false;
		inputs.backward = false;
		inputs.left = false;
		inputs.right = false;
		inputs.up = false;
		inputs.down = false;

		inputs.mouseDeltaX = 0;
		inputs.mouseDeltaX = 0;

		inputs.mouseX = 0;
		inputs.mouseY = 0;
	}
}

App::~App()
{
	delete camera;
	glfwTerminate();
	soundEngine->drop();
}

//Get back Events and setup ImGUI frame
void App::NewFrame(bool mouseCaptured)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	if (mouseCaptured)
		ImGui::GetIO().MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	ImGui::NewFrame();
}

//Clear buffer et render ImGUI
void App::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

void App::AddScene(Resource::Scene* scene)
{
	scenes.push_back(scene);
}

void App::SetActiveScene(int id)
{
	scenes[currentScene]->Clear();
	soundEngine->stopAllSounds();
	currentScene = id;
	scenes[currentScene]->Init(resourcesManager);
	soundEngine->play2D(scenes[currentScene]->getMusicFile(), true);
}

void App::StartLoadSpeedTest()
{
	reloadTestStart = std::chrono::high_resolution_clock::now();
	reloadTest = true;
}

void App::HandleLoadSpeedTest()
{
	if (reloadTest)
	{
		if (reloadCount < reloadToDo)
		{
			reloadTest = true;
			reload = true;
			if (scenes[currentScene]->CheckLoadedModel())
				reloadCount++;
		}
		else
		{
			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> elapsedSeconds = end - reloadTestStart;
			speedTestResult.iteration = reloadCount;
			speedTestResult.total = elapsedSeconds.count();
			speedTestResult.average = speedTestResult.total / reloadCount;

			Core::Debug::log.Print("Speedtest result : reloaded %d time\ntotal : %fs\nAverage : %fs", speedTestResult.iteration, speedTestResult.total, speedTestResult.average);
			reloadTest = false;
			reload = false;
			reloadCount = 0;
		}
	}
}

void App::ImGui()
{
	if (ImGui::Begin("Camera info"))
	{
		ImGui::SliderFloat3("position", &camera->position.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("rotation", &camera->rotation.x, 0.f, 360.f);
		ImGui::SliderFloat("speed", &camera->speed, 0.f, 1.f);

		if (ImGui::Button("Reset"))
			ResetCamera();

		if (ImGui::Button("Orthographic view"))
			camera->setProjection(lowRenderer::ViewType::VT_ORTHOGRAPHIC);

		if (ImGui::Button("Perspective view"))
			camera->setProjection(lowRenderer::ViewType::VT_PERSPECTIVE);

		if (ImGui::Button("Capture mouse"))
		{
			mouseCaptured = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		if (mouseCaptured)
			ImGui::Text("Tab to un-capture");

		if (ImGui::CollapsingHeader("Control"), ImGuiTreeNodeFlags_DefaultOpen)
		{
			ImGui::Text("w : forward");
			ImGui::Text("s : backward");
			ImGui::Text("a : left");
			ImGui::Text("d : right");

			ImGui::Text("space : up");
			ImGui::Text("L shift : down");

			ImGui::Text("E : speed up");
			ImGui::Text("Q : speed down");

		}

	}
	ImGui::End();

	if (ImGui::Begin("Scenes"))
	{
		for (int id = 0; id < scenes.size(); id++)
		{
			std::string tag = "Go To " + scenes[id]->name;
			if (ImGui::Button(tag.c_str()))
			{
				ResetCamera();
				SetActiveScene(id);
			}
		}
	}
	ImGui::End();

	if (ImGui::Begin("Loading"))
	{
		ImGui::Text("Threading mode : %s", resourcesManager.getThreadingMode() == Resource::Threading::Multi ? "Multi" : "Mono");

		if (scenes[currentScene]->IsLoaded() && !reloadTest)
		{
			if (ImGui::Button("Swap Threading mode"))
				resourcesManager.swapThreading();

			if (ImGui::Button("Reload Scenes"))
				reload = true;
			else
				reload = false;

			ImGui::SliderInt("Reload test iteration", &reloadToDo, 1, 100);

			if (ImGui::Button("Start reload test"))
				StartLoadSpeedTest();
		}

		ImGui::Text("Reload test result :");
		ImGui::Text("Iteration : %d", speedTestResult.iteration);
		ImGui::Text("Total : %fs", speedTestResult.total);
		ImGui::Text("Average : %fs", speedTestResult.average);
	}
	ImGui::End();
}