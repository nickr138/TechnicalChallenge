// TechnicalChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>

//****************************************
// Constant definitions
//****************************************

// LED triggers after 65000 ticks
const unsigned short TRIGGER_LED = 0xFDE8;

// Number of ticks after 65000 that the LED logic can occur (30ms)
const unsigned short EN_WINDOW = 0xD8;

// Turn debugging printing on/off
const bool PRINT_DEBUG = true;

//****************************************
// Timer Class
//****************************************

// To save time, the comments for the functions have included with the definitions but not the declarations
class Timer
{
public:
	Timer();
	~Timer();
	unsigned short GetTimerTick();
	void IncrementTimerTick();

private:
	// Current tick of the 16-bit timer.
	unsigned short tickCount;
};

// Constructor
// Inputs:
//		None
// Outputs:
//		None
Timer::Timer()
{
	tickCount = 0;
}

// Destructor
// Inputs:
//		None
// Outputs:
//		None
Timer::~Timer() {}

// Get the current Timer tick count
// Inputs: 
//		None
// Outputs:
//		Current timer tick count
unsigned short Timer::GetTimerTick()
{
	// Truncation is fine
	return tickCount;
}

// Simulate the timer's clock by increasing the clock tick by 1
// Inputs: 
//		None
// Outputs:
//		None
void Timer::IncrementTimerTick()
{
	// This should handle overflow by itself
	tickCount++;
}


//****************************************
// Main program
//****************************************
int main()
{
	// Instantiate the timer
	Timer timer{};

	// Both LEDs can be represented as booleans for simplicity. I'll start them in the "off" position
	bool led1 = false;
	bool led2 = false;

	// Intermediate variable for the input isn't necessary but does help debugging
	short input;

	// Enable flag so the program knows that a tick count of 65000 has been reached
	bool en = false;

	// Infinite loop to simulate the constant output from a sensor
	while (1)
	{
		input = timer.GetTimerTick();

		// Debugging printing, also so the console can see the tick that the system is at
		if (PRINT_DEBUG)
		{
			std::printf("Tick Count: %hu\n", input);
		}

		if (input & TRIGGER_LED)
		{
			en = true;
			// Normally, the function to blink the LED 5 times would be a callback that
			// is added to the scheduler queue, but for simplicity the code will directly execute
		}

		// If needed, a 1ms delay can be added between each clock tick
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));

		timer.IncrementTimerTick();

		// If the enable flag is still set but the timer has gone past 216 ticks since it was enabled, disable it
		input = timer.GetTimerTick();
		if (en &&
			(input & EN_WINDOW) == input)
		{
			en = false;
		}
	}
}
