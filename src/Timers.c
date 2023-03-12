/*
 * Timer1.c
 *
 * Created: 2022-11-29 12:57:31
 *  Author: mini0072
 */ 
#include <avr/io.h>

void enable_timer1(void)
{	
	//S�tt port f�r OCR1A och OCR1B som anv�nds f�r PWM till utg�ngar
	DDRD = DDRD | 0b00110000;
	//ST�LLER IN F�R FAST PWM MED ICR1 som TOP-V�RDE f�r r�knaren OCH OCR1A som compare-v�rde.
	//S�TTER PINNE p� comparematch n�r den r�knar upp�t och clearar pinne p� comparematch n�r den r�knar ned�t
	//15.7Khz
	ICR1 = 5000; //1.6kHz
	//ICKEINVERTERAD SOM START, INVERTERAS F�R BACK
	TCCR1A = (1<<COM1A1)|(1<<COM1B1)| (1<<WGM11); //|(1<<COM1A0) |(1<<COM1B0);
	TCCR1B = (1<<CS10)| (1<<WGM12)| (1<<WGM13);
	//STYR PULSL�NGD H�RE V�RDE GER KORTARE PULSER
	//Styr pinne OC1A
	OCR1A = 0;
	//STYR PINNE OC1B
	OCR1B = 0;
	
	//PWM 50% 2500
	//MINIMI F�R ATT DRIVA FRAM�T 36% PWM
	
}

void enable_timer0(void)
{	
	DDRB = DDRB | (1<<PORTB3);
	//CTC TOGGLE COMPARE MATCH
	TCCR0A = 0b01000010;
	//KLOCKA �R AV, SL�S P� IFALL KOMMANDO KOMMER F�R TUTA
	TCCR0B = 0b00000000;
	
	OCR0A = 0x50;
}

void enable_timer2(void)
{	
	//CTC med interrupt f�r adc-hantering
	TCCR2A = TCCR2A | (1<<WGM21);
	TCCR2B = TCCR2B | (1<<CS22);
	OCR2A = 0xF0;
	TIMSK2 = TIMSK2 | (1<<OCIE2A);
}