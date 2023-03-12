/*
 * Projekt.c
 *
 * Created: 2022-11-29 09:53:56
 * Author : mini0072
 */ 
#define F_CPU 8000000UL


//INCLUDES

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "Timers.h"
#include <avr/interrupt.h>
#include "ADC_handling.h"
#include "Variable_defs.h"
#include "Car_control.h"
#include "Instruction_receive.h"
#include "WATCHDOG.h"
#include <avr/wdt.h>




//UART TILL PRINTF





//MAIN

int main(void)
{	
	uint8_t Range = 0;
	
	wdt_init(); 
	
	
	
	
	
	//INITS
	UART_init();
	enable_adc();
	enable_timer1();
	enable_timer0();
	enable_timer2();
	Car_init_control();
	
	
	sei();
	//Väljer korrekt adc input och kör en första konvertering
	choose_adc_input(7);
	run_conversion();
    
	while (1) 
    {	
		//Stänger av motorerna om nytt kommando ej inkommit på 2s
		
		if(timeout_counter >= 5000)
		{
			Car_shut_down();
		}
		
		
		//Utför instruktioner som inkommit via UART som ligger i buffert instr_buffer
		Car_exectue_command();
		
		//Om AD omvandling är klar beräknas ny range
		if(ADC_flg == 1)
		{
			Range = Get_range();
			Range_check(Range);
			PORTA = PORTA ^ 0b00000001;	
		}
		//Om tid 0.25s har gått så ska Range skickas till ESP och flagga släckas
		if(send_rng_flg == 1)
		{	
			Range_ascii_send(Range);
			send_rng_flg = 0;
		}
		wdt_reset(); 
	}
	
	 
}





//INTERRUPTRUTINER
ISR(ADC_vect)
{		
	ADC_flg	= 1;	
}

ISR(USART0_RX_vect)
{	
	uint8_t UART_RX = 0;
	
	
	UART_RX = UDR0;
		
	Uart_rx_buffer(UART_RX);
	//Nollställ 2-sekundersräknare 
	timeout_counter = 0;
	
}

ISR(TIMER2_COMPA_vect)
{	
	//Starta adc-omvandling
	run_conversion();
	//Kolla om 0.5s har gått
	if (timer2_counter >= 500)
	{	
		//ÅTERSTÄLLER FLAGGOR FÖR FULL FART FRAM/BAK EFTER EN TIDIGARE FULL FART FRAM/BAK
		Car_reverse_flg = 0;
		Car_forward_flg = 0;
		//FLAGGA FÖR ATT SKICKA RANGE TILL ESP
		send_rng_flg = 1;
		timer2_counter = 0;
	}
	
	

	
	//Inkrementera 0.5s counter
	timer2_counter++;
	//Kolla om 2s har gått
	if(timeout_counter <= 5000)
	{
		timeout_counter++;
	}
	
	
}


