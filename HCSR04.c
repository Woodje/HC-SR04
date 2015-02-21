/*
 * HCSR04.c
 *
 * Created: 13-02-2015 17:55:48
 *  Author: Woodje
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "HCSR04.h"

// Initialize HCSR04.
HCSR04Init()
{
	// Enable the trigger port.
	ULTRASONICs_DDR |= 1 << ULTRASONICs_TRIGGER_PIN;
}

// Trigger HCSR04 - "Send a 10uS pulse".
void HCSR04Trigger()
{
	ULTRASONICs_PORT |= 1 << ULTRASONICs_TRIGGER_PIN;	// HIGH
	
	_delay_us(10); // Wait 10uS
	
	ULTRASONICs_PORT &= ~(1<<ULTRASONICs_TRIGGER_PIN);	// LOW
}

// Get the distance in centimeters.
uint16_t GetDistanceInCentimeters()
{
	uint32_t i, x;
	
	// Wait for the rising edge.
	for (i=0; i<ULTRASONICsTimeout; i++)
	{
		if (bit_is_clear(ULTRASONICs_PIN, ULTRASONICs_ECHO_POS))
			// Line is still low, so wait
			continue;
		else
			// High edge detected, so break.
			break;
	}
	
	if (i == ULTRASONICsTimeout)
		// Indicates a timeout.
		return -1;
	
	// High Edge Found. Setup the timer.
	TCCR1A=0X00;
	
	// Prescaler = 0.
	TCCR1B=(1<<CS10);
	
	// Initiate the counter.
	TCNT1=0x00;
	
	// Wait for the falling edge.
	for (i=0; i<ULTRASONICsTimeout; i++)
	{
		if (!bit_is_clear(ULTRASONICs_PIN, ULTRASONICs_ECHO_POS))
		{
			if(TCNT1 > 60000)
				break;
			else
				continue;
		}
		else
			break;
	}
	
	if(i==ULTRASONICsTimeout)
		//Indicates a time out. (No obstacle found)
		return -2;

	// Falling edge found. Retrieve the microseconds from the counter.
	x = TCNT1;

	// Stop the timer.
	TCCR1B=0x00;
	
	if (i > ULTRASONICsTimeout)
		//Indicates a time out. (No obstacle found)
		return -2;
	else
		return x / 58;

}