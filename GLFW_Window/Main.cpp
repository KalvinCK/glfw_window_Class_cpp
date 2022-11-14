
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <stb_image.h>

#include "GameWindow.h"
#include "Input.h"
#include "Timer.h"

int main()
{
	GameWindow* window = new GameWindow();
	window->setSize(glm::ivec2(1600, 900));
	window->Title = "GLFW Window";
	window->Create();


	GLFWimage icon;
	int channels;
	icon.pixels = stbi_load("glfw.png", &icon.width, &icon.height, &channels, 0);
	window->SetIconGLFW(icon);
	stbi_image_free(icon.pixels);

	GLFWimage cursor;
	cursor.pixels = stbi_load("cursor_blue.png", &cursor.width, &cursor.height, &channels, 0);
	window->SetCursorGLFW(cursor);
	stbi_image_free(cursor.pixels);

	Input* input = new Input();


	bool vsync = false, fullscreen = false, mouse_hiden = false;

	while (window->Run())
	{
		// update times
		Timer::FrameUpdate();


		if (input->IsKeyPress(KEY_ESCAPE))
			window->Close();

		if (input->IsKeyPress(KEY_F))
		{
			fullscreen = fullscreen ? false : true;
			window->SetWindowState(fullscreen ? WINDOW_FULLSCREEN : WINDOW_NORMAL);
		}

		if (input->IsKeyPress(KEY_V))
		{
			vsync = vsync ? false : true;
			window->SetVsyncMODE(vsync ? VSYNC_ON : VSYNC_OFF);
		}
		if (input->IsKeyPress(KEY_H))
		{
			mouse_hiden = mouse_hiden ? false : true;
			input->SetCursoState(mouse_hiden ? CURSOR_HIDDEN : CURSOR_NORMAL );
		}



		window->SwapBuffers();
	}
}