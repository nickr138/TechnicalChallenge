// TechnicalChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//****************************************
// Constant definitions
//****************************************
const unsigned short TRIGGER_LED = 0xFDE8;


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
	Timer timer;

	// Both LEDs can be represented as booleans for simplicity. I'll start them in the "off" position
	bool led1 = false;
	bool led2 = false;

	// Intermediate variable for the input isn't necessary but does help debugging
	short input;

	// Infinite loop to simulate the constant output from a sensor
	while (1)
	{
		input = timer.GetTimerTick();
		if (input & TRIGGER_LED)
		{
			// Normally, the function to blink the LED 5 times would be a callback that
			// is added to the scheduler queue, but for simplicity it will just be 
		}
	}
}
