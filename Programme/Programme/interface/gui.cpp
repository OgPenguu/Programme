#include "interface.h"

namespace interfaceNS
{
	bool RenderInterface()
	{
		static bool isOpen = true;

		ImGui::SetNextWindowSize(ImVec2((float)variables::width, (float)variables::height), ImGuiCond_Always);
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		if (ImGui::Begin("Programme", &isOpen, ImGuiWindowFlags_NoResize))
		{
			// Dragging
			{
				static bool dragging = false;
				static ImVec2 dragStartMouse;
				static ImVec2 dragStartWin;

				if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0))
				{
					dragging = true;

					dragStartMouse = globals::GetCursorPosition();

					int x, y;
					glfwGetWindowPos(variables::window, &x, &y);
					dragStartWin = ImVec2((float)x, (float)y);
				}

				if (dragging && ImGui::IsMouseDown(0))
				{
					ImVec2 cur = globals::GetCursorPosition();
					ImVec2 delta = ImVec2(cur.x - dragStartMouse.x,
						cur.y - dragStartMouse.y);

					variables::position.x = std::clamp((dragStartWin.x + delta.x), 0.0f, variables::screenSize.x - variables::width);
					variables::position.y = std::clamp((dragStartWin.y + delta.y), 0.0f, variables::screenSize.y - variables::height);
					glfwSetWindowPos(variables::window, (int)variables::position.x, (int)variables::position.y);
				}

				if (dragging && !ImGui::IsMouseDown(0))
					dragging = false;
			}

			ImGui::Text("Hello world!");

			ImGui::End();
		}

		return isOpen;
	}
}