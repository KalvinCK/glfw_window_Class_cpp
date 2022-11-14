#include "Input.h"

#include "GameWindow.h"

bool Input::keys[KEY_LAST] = { 0 };
bool Input::ctrl[KEY_LAST] = { 0 };

bool Input::mouse_btns[MOUSE_MAX_BUTTON] = { 0 };
bool Input::mouse_ctrl[MOUSE_MAX_BUTTON] = { 0 };


glm::dvec2 Input::CursorPosition = glm::dvec2(0.0);
CusorState Input::CursorState = CURSOR_NORMAL;
double Input::scrool_control = 0;




Input::Input()
{

	try
	{
		if (GameWindow::Display == NULL)
			throw std::invalid_argument("Error::Input : Create is the window first! ");

	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	// CALLBACKS INPUTS
	glfwSetKeyCallback(GameWindow::Display, keyKeyboardCALLBACK);
	glfwSetMouseButtonCallback(GameWindow::Display, mouseButtonCALLBACK);
	glfwSetCursorPosCallback(GameWindow::Display, cursorPositionCALLBACK);
	glfwSetScrollCallback(GameWindow::Display, scrollCALLBACK);

	CursorPosition = dvec2((double)(GameWindow::getSize().x / 2.0), (double)(GameWindow::getSize().y / 2.0));

	// atctive keys in windows
	glfwSetInputMode(GameWindow::Display, GLFW_STICKY_KEYS, GL_TRUE);
}
Scrool Input::getScroolState()
{

	auto scrl = static_cast<int>(scrool_control);
	scrool_control = 0.0;

	if (scrl != 0)
	{
		if (scrl < 0)
		{
			return SCROOL_BACK;
		}
		else if (scrl > 0)
		{
			return SCROOL_FRONT;
		}
	}
	else
	{
		return SCROOL_STOPPED;
	}
}
void Input::SetCursoState(CusorState cursor_state)
{
	CursorState = cursor_state;

	if (CursorState == CURSOR_NORMAL)
	{
		glfwSetInputMode(GameWindow::Display, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}
	else
	{
		glfwSetInputMode(GameWindow::Display, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(GameWindow::Display, &CursorPosition.x, &CursorPosition.y);
		glfwSetCursorPos(GameWindow::Display, GameWindow::getSize().x / 2.0, GameWindow::getSize().y / 2.0);
	}
}

// window keyboard Keys
// ----------------------------------------------------------------------------------------
bool Input::IsKeyPress(KeysKeyboardCode key)
{
	if (ctrl[key])
	{
		if (IsKeyDown(key))
		{
			ctrl[key] = false;
			return true;
		}
	}
	else if (IsKeyUp(key))
	{
		ctrl[key] = true;
	}

	return false;
}

// window mouse button
// ----------------------------------------------------------------------------------------
bool Input::IsMousePress(MouseButtons button)
{
	if (mouse_ctrl[button])
	{
		if (IsMouseDown(button))
		{
			mouse_ctrl[button] = false;
			return true;
		}
	}
	else if (IsMouseUp(button))
	{
		mouse_ctrl[button] = true;
	}

	return false;
}

// Inputs CALLBACKS
// --------------------------------------------------------------------------
void Input::keyKeyboardCALLBACK(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		keys[key] = true;
		break;

	case GLFW_RELEASE:
		keys[key] = false;
		break;
	}
}
void Input::mouseButtonCALLBACK(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		mouse_btns[button] = true;
		break;

	case GLFW_RELEASE:
		mouse_btns[button] = false;
		break;
	}
}
void Input::cursorPositionCALLBACK(GLFWwindow* window, double xpos, double ypos)
{
	if (CursorState == CURSOR_NORMAL)
	{
		CursorPosition = dvec2(xpos, ypos);
	}
}
void Input::scrollCALLBACK(GLFWwindow* window, double xoffset, double yoffset)
{
	scrool_control = yoffset;
}