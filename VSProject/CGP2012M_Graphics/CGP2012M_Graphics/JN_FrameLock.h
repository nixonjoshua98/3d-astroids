#ifndef JN_FRAME_LOCK_H
#define JN_FRAME_LOCK_H

#include <chrono>

class JN_FrameLock
{
public:
	JN_FrameLock(int fps, float& _rFps);	// Constructor
	~JN_FrameLock();					// Deconstructor, stops the clock and locks the fps

private:
	std::chrono::system_clock::time_point start;	// The time at construction

	// - - - - DELTA TIME - - - -
	float wantedDeltaTime;		// Delta time requested
	float actualDeltaTime;		// The actual delta time

	float& rDelta;		// Passed in by reference

	int CalculateDeltaTime();	// Calculate the time since construction in ms
	void WaitForMs(int ms);		// Pause execution for <ms> time
};

#endif