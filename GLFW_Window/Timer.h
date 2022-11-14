#pragma once


class Timer
{
private:
	static double frameCount;
	static double previousTime;

public:
	static float Frames;
	static float ElapsedTime;
	static float Time;

	// Deve ser chamada apenas uma unica vez no loop principal
	static void FrameUpdate();
};