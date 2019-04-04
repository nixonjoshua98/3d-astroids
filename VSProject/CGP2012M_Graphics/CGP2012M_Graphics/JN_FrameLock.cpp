
#include "JN_FrameLock.h"

// SDL_Delay(ms)
#include <SDL.h>

// Sleep(ms)
//#include "windows.h"

#include <iostream>


JN_FrameLock::JN_FrameLock(int fps, float& _rDelta) : rDelta(_rDelta)
{
	start = std::chrono::system_clock::now();

	// Requested delta time
	wantedDeltaTime = 1000 / fps;
}

JN_FrameLock::~JN_FrameLock()
{
	actualDeltaTime = CalculateDeltaTime();

	WaitForMs((int)std::fmax(wantedDeltaTime - actualDeltaTime, 0));

	actualDeltaTime = CalculateDeltaTime();

	if (actualDeltaTime == 0)
	{
		rDelta = 0;
		std::cout << "Warning: Delta time < 0ms" << std::endl;
	}
	else
		rDelta = actualDeltaTime / 1000;
}

int JN_FrameLock::CalculateDeltaTime()
{
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<float, std::milli> span = end - start;

	return (int)span.count();
}


void JN_FrameLock::WaitForMs(int ms)
{
	SDL_Delay(ms);
}