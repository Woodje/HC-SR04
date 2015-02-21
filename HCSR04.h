/*
 * HCSR04.h
 *
 * Created: 13-02-2015 17:48:30
 *  Author: Woodje
 */ 

#ifndef HCSR04_H_
#define HCSR04_H_

#define	ULTRASONICs_TRIGGER_PIN	PINB6
#define ULTRASONICs_TRIGGER_POS	6

#define	ULTRASONICs_ECHO_PIN	PINB7
#define ULTRASONICs_ECHO_POS	7

#define ULTRASONICs_DDR			DDRB
#define ULTRASONICs_PORT		PORTB
#define	ULTRASONICs_PIN			PINB

#define ULTRASONICsTimeout		600000

// Initialize HCSR04.
void HCSR04Init();

// Trigger HCSR04 - "Send a 10uS pulse".
void HCSR04Trigger();

// Get the distance in centimeters.
uint16_t GetDistanceInCentimeters();

#endif /* HCSR04_H_ */