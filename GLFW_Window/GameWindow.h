#pragma once

#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;


enum WindowState { WINDOW_NORMAL, WINDOW_FULLSCREEN };
enum VsyncMODE { VSYNC_OFF, VSYNC_ON };


class Error
{
public:
	static void Test_Entity(bool Entity, const std::string& description, bool close = true);
};


class GameWindow
{
private:

	static double scrool_control;

	GLFWcursor* cursor;
	GLFWmonitor* monitor;




	static glm::ivec2 SizeWin;
	static glm::ivec2 PixelsFrameBuffer;
	static glm::ivec2 PositionWin;

	static bool isFocus;
	static bool CursorEnterWindow;

public:
	static GLFWwindow* Display;

	glm::ivec2 VersionApiGraphic;
	std::string Title = "";

	GameWindow();
	~GameWindow();

	void Create();
	bool Run();
	void SwapBuffers();
	void Close();

	// set details window
	// ----------------------------------------------------------------------------------------
	void SetVsyncMODE(VsyncMODE vsync_mode);
	void SetWindowState(WindowState window_state);

	void SetTitleWindow(const std::string& title);
	void SetIconGLFW(GLFWimage& icon_img);
	void SetCursorGLFW(GLFWimage& cursor_img);
	inline void setSize(glm::ivec2 size) { SizeWin = size; }

	// get 
	static inline glm::ivec2 getSize() { return SizeWin;  }
	static inline glm::ivec2 getSizeWindowPixels() { return PixelsFrameBuffer; }
	static inline glm::ivec2 getPosition() { return PositionWin; }

	static inline bool isFocused() { return isFocus; }
	static inline bool isCursorEnterWindow() { return CursorEnterWindow; }

private:
	// Window CALLBACKS
	// ----------------------------------------------------------------------------------------
	static void windowSizeWinCALLBACK(GLFWwindow* window, int width, int height);
	static void WindowFramebufferCALLBACK(GLFWwindow* window, int width, int height);
	static void windowPositionWinCALLBACK(GLFWwindow* window, int xpos, int ypos);
	static void windowFocusCALLBACK(GLFWwindow* window, int focused);

	// Inputs CALLBACKS
	// --------------------------------------------------------------------------
	static void cursorEnterCALLBACK(GLFWwindow* window, int entered);

};
inline void GameWindow::Close()
{
	glfwSetWindowShouldClose(Display, GLFW_TRUE);
};
