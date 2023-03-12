/*
 * WATCHDOG.c
 *
 * Created: 2023-01-05 14:23:35
 *  Author: mini0072
 */ 
#include <avr/wdt.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void wdt_init(void)
{	
	cli();
	
	wdt_disable();
	wdt_reset();
	
	WDTCSR = (1<<WDCE) | (1<<WDE);
	//4s reset om wdt ej resettas
	WDTCSR = 0b00101000;
}