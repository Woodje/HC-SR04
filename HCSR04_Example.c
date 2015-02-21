/*
 * HCSR04_Example.c
 *
 * Created: 13-02-2015 18:28:02
 *  Author: Woodje
 */

#include "HCSR04.h"

int main(void)
{
	// Initialize HCSR04.
	HCSR04Init();

	while(1)
	{
		// Trigger HCSR04 - "Send a 10uS pulse".
		void HCSR04Trigger();
		
		// Get the distance in centimeters.
		int distance = GetDistanceInCentimeters();
	}
}