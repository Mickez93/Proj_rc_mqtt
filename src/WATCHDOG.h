/*
 * WATCHDOG.h
 *
 * Created: 2023-01-05 14:23:49
 *  Author: mini0072
 */ 


#ifndef WATCHDOG_H_
#define WATCHDOG_H_

void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));



#endif /* WATCHDOG_H_ */