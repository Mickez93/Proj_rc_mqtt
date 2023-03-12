/*
 * ADC_handling.c
 *
 * Created: 2022-11-29 15:55:35
 *  Author: mini0072
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Variable_defs.h"
#include "Instruction_receive.h"
#include <stdio.h>
//PORTAR I MUX REGISTER SOM SKA SÄTTAS FÖR ATT ENABLA OLIKA CHANNELS
#define ADC_C_7 0b00000111;
#define ADC_C_6 0b00000110;
#define	ADC_C_5 0b00000101;


void enable_adc(void)
{
	//Enabla ADC och ADC complete interrupt
	ADCSRA = ADCSRA | (1<<ADEN) | (1<<ADIE);
	ADMUX = 0b00000000;
	//PINNE FÖR VARNINGSLAMPA TILL UTGÅNG
	DDRD = DDRD | 0b10000000;
	//PORTA 7 6 5 sätts som input för att läsa ACD in
	//DDRA = 0b00011111;
}

void choose_adc_input(uint8_t ADC_channel)
{
	//AREF - internal Vref turned off single ended ADC 7 0 gain VCC used as reference on AREF pin
	ADMUX = ADMUX & 0b00000000;
	ADMUX = ADMUX | ADC_channel;
}

//Starta AD-omvandling
void run_conversion(void)
{
	ADCSRA = ADCSRA | (1<<ADSC);

}

void calc_avg(uint16_t Data,uint16_t *Prev_avg, uint8_t length)
{
	
	
	uint16_t avg_D_ut = 0;
	
	avg_D_ut = (Prev_avg[9]+Prev_avg[8]+Prev_avg[7]+Prev_avg[6]+Prev_avg[5]+Prev_avg[4]+Prev_avg[3]+Prev_avg[2]+Prev_avg[1]+Prev_avg[0]+Data) / 11;
		//SKIFTA POSITIONER I ARRAYEN
	for(int i = length-1 ; i > 0 ; i--)
	{
		Prev_avg[i] = Prev_avg[i-1];
	}
		
	
	
	Prev_avg[0] = avg_D_ut;
}

uint16_t Calc_range(uint16_t D_ut)
{	
	//FÖRHINDRA OVERFLOW FRÅN RANGE CALC GER MAXIMAL RANGE PÅ 97CM
	if(D_ut < 67)
	{
		D_ut = 67;
	}
	uint8_t Range_calc = ((6700/(D_ut-3))-7);
	
	return Range_calc;
};

uint16_t ADC_get_result(void)
{	
	uint16_t ADC_result = 0;
	
	LADC_res = ADCL;
	HADC_res = ADCH;
	ADC_result = (HADC_res<<8)+ LADC_res;
	return ADC_result;
}	

uint8_t Get_range(void)
{	
	uint16_t ADC_result = 0;
	uint8_t Range = 0;
	
	ADC_result = ADC_get_result();
	ADC_flg = 0;
	calc_avg(ADC_result,prev_avg,10);
	Range = Calc_range(prev_avg[0]);
	
	return Range;
}

void Range_check(uint8_t Range)
{
	
	if(Range < 12)
	{
		PORTD = PORTD | (1<<7);
		
	}
	
	else if(Range > 13)
	{	
		
		PORTD = PORTD & 0b01111111;
	}
	
	
}

void Range_ascii_send(uint8_t Range)
{
	uint8_t tiotal = 0;
	uint8_t ental = 0;
	
	while(Range >= 10)
	{
		tiotal++;
		Range = Range - 10;
	}
	ental = Range;
	
	tiotal = tiotal + 48;
	ental = ental + 48;
	//SKICKAR R som första tecken
	UART_send(82);
	UART_send(tiotal);
	UART_send(ental);
	
	
	
}


