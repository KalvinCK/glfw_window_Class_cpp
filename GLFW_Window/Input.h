#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Keys.h"

enum CusorState { CURSOR_NORMAL, CURSOR_HIDDEN };
enum Scrool { SCROOL_BACK = 0, SCROOL_FRONT = 1, SCROOL_STOPPED = 2 };


class Input
{
private:
	static bool keys[GLFW_KEY_LAST];
	static bool ctrl[GLFW_KEY_LAST];

	static bool mouse_btns[MOUSE_MAX_BUTTON];
	static bool mouse_ctrl[MOUSE_MAX_BUTTON];

	static glm::dvec2 CursorPosition;
	static CusorState CursorState;

	static double scrool_control;
public:
	Input();

	// chame uma vez dentro de algum loop

	void SetCursoState(CusorState cursor_state);

	// get values
	inline glm::dvec2 getCursorPosition() { return CursorPosition; }
	inline bool getCursorState() { return CursorState; }

	Scrool getScroolState();
	
	// keys 
	static bool IsKeyDown(KeysKeyboardCode key);
	static bool IsKeyUp(KeysKeyboardCode key);
	static bool IsKeyPress(KeysKeyboardCode key);

	// mouse
	// ----------------------------------------------------------------------------------------
	static bool IsMouseDown(MouseButtons button);
	static bool IsMouseUp(MouseButtons button);
	static bool IsMousePress(MouseButtons button);

private:
	// Inputs CALLBACKS
	// --------------------------------------------------------------------------
	static void keyKeyboardCALLBACK(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseButtonCALLBACK(GLFWwindow* window, int button, int action, int mods);
	static void cursorPositionCALLBACK(GLFWwindow* window, double xpos, double ypos);
	static void scrollCALLBACK(GLFWwindow* window, double xoffset, double yoffset);

};

// window mouse button
// ----------------------------------------------------------------------------------------
inline bool Input::IsMouseDown(MouseButtons button)
{
	return mouse_btns[button];
}
inline bool Input::IsMouseUp(MouseButtons button)
{
	return !(mouse_btns[button]);
}

// window keyboard Keys
// ----------------------------------------------------------------------------------------
inline bool Input::IsKeyDown(KeysKeyboardCode key)
{
	return keys[key];
}
inline bool Input::IsKeyUp(KeysKeyboardCode key)
{
	return !(keys[key]);
}

