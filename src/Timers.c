/*
 * Timer1.c
 *
 * Created: 2022-11-29 12:57:31
 *  Author: mini0072
 */ 
#include <avr/io.h>

void enable_timer1(void)
{	
	//Sätt port för OCR1A och OCR1B som används för PWM till utgångar
	DDRD = DDRD | 0b00110000;
	//STÄLLER IN FÖR FAST PWM MED ICR1 som TOP-VÄRDE för räknaren OCH OCR1A som compare-värde.
	//SÄTTER PINNE på comparematch när den räknar uppåt och clearar pinne på comparematch när den räknar nedåt
	//15.7Khz
	ICR1 = 5000; //1.6kHz
	//ICKEINVERTERAD SOM START, INVERTERAS FÖR BACK
	TCCR1A = (1<<COM1A1)|(1<<COM1B1)| (1<<WGM11); //|(1<<COM1A0) |(1<<COM1B0);
	TCCR1B = (1<<CS10)| (1<<WGM12)| (1<<WGM13);
	//STYR PULSLÄNGD HÖRE VÄRDE GER KORTARE PULSER
	//Styr pinne OC1A
	OCR1A = 0;
	//STYR PINNE OC1B
	OCR1B = 0;
	
	//PWM 50% 2500
	//MINIMI FÖR ATT DRIVA FRAMÅT 36% PWM
	
}

void enable_timer0(void)
{	
	DDRB = DDRB | (1<<PORTB3);
	//CTC TOGGLE COMPARE MATCH
	TCCR0A = 0b01000010;
	//KLOCKA ÄR AV, SLÅS PÅ IFALL KOMMANDO KOMMER FÖR TUTA
	TCCR0B = 0b00000000;
	
	OCR0A = 0x50;
}

void enable_timer2(void)
{	
	//CTC med interrupt för adc-hantering
	TCCR2A = TCCR2A | (1<<WGM21);
	TCCR2B = TCCR2B | (1<<CS22);
	OCR2A = 0xF0;
	TIMSK2 = TIMSK2 | (1<<OCIE2A);
}