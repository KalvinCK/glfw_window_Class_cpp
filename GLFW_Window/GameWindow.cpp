
#include "GameWindow.h"

#include "Input.h"

void Error::Test_Entity(bool Entity, const std::string& description, bool close)
{
	try
	{
		if (Entity)
			return;
		else
			throw std::invalid_argument("Error:: in ");

	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << description << std::endl;
		if (close)
		{
			exit(EXIT_FAILURE);
		}
	}
}


GLFWwindow* GameWindow::Display = nullptr;

ivec2 GameWindow::SizeWin = ivec2(1280, 720);
ivec2 GameWindow::PixelsFrameBuffer = ivec2(1280, 720);
ivec2 GameWindow::PositionWin = ivec2(50, 50);

bool GameWindow::isFocus = true;
bool GameWindow::CursorEnterWindow = true;


double GameWindow::scrool_control = 0;

GameWindow::GameWindow()
{
	Error::Test_Entity(glfwInit(), "Start GLFW");


	Title = "GLFW WINDOW";
	VersionApiGraphic = ivec2(4, 6);
	SizeWin = ivec2(1280, 720);
	PixelsFrameBuffer = ivec2(1280, 720);
	PositionWin = ivec2(50, 50);
	isFocus = true;
	cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
	monitor = glfwGetPrimaryMonitor();
}
GameWindow::~GameWindow()
{
	glfwDestroyWindow(Display);
	glfwTerminate();
}

void GameWindow::Create()
{
	PixelsFrameBuffer = SizeWin;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VersionApiGraphic.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VersionApiGraphic.y);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);


	Display = glfwCreateWindow(SizeWin.x, SizeWin.y, Title.c_str(), NULL, NULL);
	Error::Test_Entity(Display, "Init GLFW");

	glfwSetWindowPos(Display, PositionWin.x, PositionWin.y);

	// CALLBACKS window
	glfwSetWindowSizeCallback(Display, windowSizeWinCALLBACK);
	glfwSetFramebufferSizeCallback(Display, WindowFramebufferCALLBACK);
	glfwSetWindowPosCallback(Display, windowPositionWinCALLBACK);
	glfwSetWindowFocusCallback(Display, windowFocusCALLBACK);

	// CALLBACKS
	glfwSetCursorEnterCallback(Display, cursorEnterCALLBACK);

	glfwMakeContextCurrent(Display);

	glfwPollEvents();
}
bool GameWindow::Run()
{
	return (glfwWindowShouldClose(Display) == GLFW_FALSE) ? true : false;
}

void GameWindow::SwapBuffers()
{
	glfwSwapBuffers(Display);
	glfwPollEvents();
}
void GameWindow::SetVsyncMODE(VsyncMODE vsync_mode)
{
	glfwSwapInterval(!vsync_mode);
}
void GameWindow::SetWindowState(WindowState window_state)
{
	if (window_state)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(Display, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(Display, NULL, 100, 100, 1280, 720, 0);
	}
}
void GameWindow::SetTitleWindow(const std::string& title)
{
	glfwSetWindowTitle(Display, title.c_str());
}
void GameWindow::SetIconGLFW(GLFWimage& icon_img)
{
	try
	{
		if (icon_img.pixels == 0)
			throw std::invalid_argument("GLFW::ERROR... IN ICON!");
		else
			glfwSetWindowIcon(Display, 1, &icon_img);
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
}
void GameWindow::SetCursorGLFW(GLFWimage& cursor_img)
{
	cursor = glfwCreateCursor(&cursor_img, 0, 0);
	try
	{
		if (cursor == NULL)
			throw std::invalid_argument("GLFW::ERROR... IN CURSOR!");
		else
			glfwSetCursor(Display, cursor);

	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
}
// Window CALLBACKS
// ----------------------------------------------------------------------------------------
void GameWindow::windowSizeWinCALLBACK(GLFWwindow* window, int width, int height)
{
	SizeWin = ivec2(width, height);
}
void GameWindow::WindowFramebufferCALLBACK(GLFWwindow* window, int width, int height)
{
	PixelsFrameBuffer = ivec2(width, height);
}
void GameWindow::windowPositionWinCALLBACK(GLFWwindow* window, int xpos, int ypos)
{
	PositionWin = vec2(xpos, ypos);
}
void GameWindow::windowFocusCALLBACK(GLFWwindow* window, int focused)
{
	isFocus = focused;
}
void GameWindow::cursorEnterCALLBACK(GLFWwindow* window, int entered)
{
	CursorEnterWindow = entered;
}



