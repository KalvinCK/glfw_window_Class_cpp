#include "Timer.h"

#include <GLFW/glfw3.h>

double Timer::frameCount = 0.0;
double Timer::previousTime = 0.0;
float  Timer::Frames = 0.0;
float  Timer::ElapsedTime = 0.0;
float  Timer::Time = 0.0;

void Timer::FrameUpdate()
{
	static double lastTime = glfwGetTime();
	Time = static_cast<float>(glfwGetTime());

	double currentTime = glfwGetTime();
	ElapsedTime = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;

	// FPS
	frameCount++;
	if (currentTime - previousTime >= 1.0)
	{
		Frames = static_cast<float>(frameCount);
		frameCount = 0.0f;
		previousTime = currentTime;
	}
}

