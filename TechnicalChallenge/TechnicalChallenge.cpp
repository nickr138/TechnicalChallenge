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

// 1/10th of a second, in ticks (Assuming 21.6kHz clock)
const unsigned int TICKS_100MS = 2160;

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
	unsigned short input;

	// Enable flag so the program knows that a tick count of 65000 has been reached
	bool en = false;

	// Infinite loop to simulate the constant output from a sensor
	while (1)
	{
		input = timer.GetTimerTick();

		if (input == TRIGGER_LED)
		{
			en = true;

			// Normally, the function to blink the LED 5 times would be a callback that
			// is added to the scheduler queue, but for simplicity the code will directly execute
			if (en)
			{
				// Toggle the first LED
				led1 = !led1;
				// And turn on the second
				led2 = true;
				
				// Incrementing a new tick variable to time 1/10th of a second
				unsigned short newTimerTick = 0;

				// Keep track of how many times the 2nd LED has triggered
				// It's already been turned on, so start at 1
				unsigned int led2ToggleCnt = 1;

				// In this part I'll use a second while loop to simulate the "callback" executing in
				// another thread, complete with the timer continuing to increment
				while (1)
				{
					// Check to see if 1/0th of a second (2,160 ticks) have passed since LED2 was toggled
					if (newTimerTick == TICKS_100MS)
					{
						// 1/10th of a second has passed, so LED2 should be toggled
						led2 = !led2;

						// The count of LED2 toggles needs to be updated too
						led2ToggleCnt++;

						// reset the new timer back to 0
						newTimerTick = 0;

						// If LED2 has been toggled 10 times (On 5 times, off 5 times) then this "callback" has completed
						// and LED2 should remain off until the next time this "callback" is called
						if (led2ToggleCnt == 10)
						{
							break;
						}
					}

					// Print out the LED information to the console
					if (PRINT_DEBUG)
					{
						std::printf("LED1:%d, LED2:%d, TickCount: %hu", led1, led2, input);
						std::printf("\n");
					}

					// Increment the timer as if this weren't it's own seperate loop
					timer.IncrementTimerTick();
					newTimerTick++;
					input = timer.GetTimerTick();
					if (en && (input & EN_WINDOW) == input)
					{
						en = false;
					}
				}

			}
		}

		// Debugging printing, also so the console can see the tick that the system is at
		if (PRINT_DEBUG)
		{
			std::printf("LED1:%d, LED2:%d, TickCount: %hu", led1, led2, input);
			std::printf("\n");
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
