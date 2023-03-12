/*
 * Instruction_receive.c
 *
 * Created: 2022-12-05 15:03:01
 *  Author: mini0072
 */ 
#include <inttypes.h>
#include "Variable_defs.h"
#include <stdio.h>
#include <avr/io.h>

#define F_CPU 8000000UL
#define USART_BAUDRATE 250000
#define BAUD_PRESCALE (((( F_CPU / 16) + (USART_BAUDRATE / 2)) / (USART_BAUDRATE)) - 1)


void Uart_rx_buffer(uint8_t UART_RX)
{	
	if(char_count == 0 && ((UART_RX == 88) || (UART_RX == 89) || (UART_RX == 72)))
	{
		Instr_buffer[0] = UART_RX;
		char_count++;
	}
	else if(char_count >= 1)
	{
		switch(Instr_buffer[0])
		{
			case 'Y':
				Instr_buffer[char_count] = UART_RX;
			break;
			case 'X':
				Instr_buffer[char_count+2] = UART_RX;
			
			
			break;
			case 'H':
				Instr_buffer[char_count+4] = UART_RX;
				
			break;
		}
		char_count++;
	}
	
	if(char_count >= 3)
	{
		char_count = 0;
		
	}
	
	
}

void UART_send(uint8_t Range)
{

	while(!(UCSR0A & (1<<UDRE0)) )
	{
	}
	UDR0 = Range;
	
}

void UART_init(void)
{
	UBRR0 = BAUD_PRESCALE; //Baud 250000
	UCSR0B = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
	
}



