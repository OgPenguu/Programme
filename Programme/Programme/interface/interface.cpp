#include "interface.h"

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "[GLFW Error] %d: %s\n", error, description);
}

namespace interfaceNS
{
	void Styles()
	{
		ImGui::StyleColorsDark();
		// ImGui::StyleColorsLight();
	}

	bool Initialize()
	{
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
			return false;

		// Decide GL+GLSL versions
	#if defined(IMGUI_IMPL_OPENGL_ES2)
		const char* glsl_version = "#version 100";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	#elif defined(IMGUI_IMPL_OPENGL_ES3)
		const char* glsl_version = "#version 300 es";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	#elif defined(__APPLE__)
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#else
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	#endif

		// Transparent and borderless
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

		// Fullscreen size
		variables::mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
		variables::width *= (int)variables::mainScale;
		variables::height *= (int)variables::mainScale;

		variables::window = glfwCreateWindow(variables::width, variables::height, "Overlay", nullptr, nullptr);
		if (!variables::window)
		{
			glfwTerminate();
			return false;
		}

		glfwSetWindowPos(variables::window, (int)variables::position.x, (int)variables::position.y);

		glfwMakeContextCurrent(variables::window);
		glfwSwapInterval(1); // VSync

		// Setup Dear ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		io.IniFilename = nullptr;

		Styles();

		ImGuiStyle& style = ImGui::GetStyle();
		style.ScaleAllSizes(variables::mainScale);
		style.FontScaleDpi = variables::mainScale;

		ImGui_ImplGlfw_InitForOpenGL(variables::window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		return true;
	}

	void Render()
	{
		while (!glfwWindowShouldClose(variables::window))
		{
			glfwPollEvents();
			if (glfwGetWindowAttrib(variables::window, GLFW_ICONIFIED) != 0)
			{
				ImGui_ImplGlfw_Sleep(10);
				continue;
			}

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			variables::screenSize = ImVec2((float)mode->width, (float)mode->height);

			if (!interfaceNS::RenderInterface())
				glfwSetWindowShouldClose(variables::window, true);

			ImGui::Render();

			int display_w, display_h;
			glfwGetFramebufferSize(variables::window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Transparent background
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(variables::window);
		}

		Shutdown();
	}

	void Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(variables::window);
		glfwTerminate();
	}
}
