/*
 * Car_control.c
 *
 * Created: 2022-12-01 11:43:54
 *  Author: mini0072
 */ 
#include <avr/io.h>
#include "Instruction_receive.h"
#include <stdio.h>
#include "Variable_defs.h"


#define X_VLU_MID 540

void Car_init_control(void)
{	
	//init utgång på portarna som används för att styra back/fram på motorerna
	DDRC = DDRC | 0b00000011;
	//PORT0 ANVÄNDS FÖR MOTOR 2 som är kopplad till OC1A PORT1 ANVÄNDS FÖR MOTOR 1 som är kopplad till OC1B
	PORTC = PORTC & 0b11111100;
}

void Car_shut_down(void)
{	//LADDAR INSTRUKTIONSBUFFERTEN SÅ ATT BILEN STANNAR NÄSTA GÅNG INSTRUKTIONER KÖRS
	Instr_buffer[1] = 0x1;
	Instr_buffer[2] = 0xFE;
	Instr_buffer[3] = 0x1;
	Instr_buffer[4] = 0xFE;
	Instr_buffer[5] = 0;
	Instr_buffer[6] = 0;
}

void Car_decode_buffer(uint16_t *x_vlu, uint16_t *y_vlu, uint16_t *h_vlu)
{
	*y_vlu = (Instr_buffer[1]<<8) + Instr_buffer[2];
	//SKYDDA MOT STRÖMSPIKAR GENOM ATT INTE KÖRA FULL FART FRAM/BAK EFTER EN TIDIGARE HÖG FART FRAM/BAK FLAGGOR RESETTAS I TIMER2
	if(*y_vlu>950)
	{	
		if(Car_forward_flg == 1)
		{
			*y_vlu = 540;
			
		}
		Car_reverse_flg = 1;
	}
	else if (*y_vlu < 100)
	{	
		if(Car_reverse_flg == 1)
		{
			*y_vlu = 470;
			
		}
		Car_forward_flg = 1;
	}
	*x_vlu = (Instr_buffer[3]<<8)+ Instr_buffer[4];
	*h_vlu = (Instr_buffer[5]<<8)+ Instr_buffer[6];
}

void Car_calculate_turn(uint16_t *x_vlu, float* L_scaler, float* R_scaler)
{	
	
	if(*x_vlu > 470 && *x_vlu < 520)
	{
		*R_scaler = 1;
		*L_scaler = 1;
	}
	else if((525 + *x_vlu) <= 1025 && *x_vlu > 0)
	{	
		//SCALER MELLAN 0-1 beroende på indata
		*L_scaler = 0.0021 * *x_vlu;
		*R_scaler = 1;
		
	}
	else if((*x_vlu + 510) >= 1030 && *x_vlu <= 1024)
	{
		//SCALER MELLAN 0-1 beroende på indata
		*R_scaler = -0.0019 * (*x_vlu - 520) + 1;
		*L_scaler = 1;
	}
	
	
	
	
}

void Car_spin_left(float L_scaler)
{
	
	OCR1B =(-6400*L_scaler)+ 8200;
	OCR1A = OCR1B;
	//VÄNSTER MOTOR INVERTERAS FÖR ATT BACKA HÖGER MOTOR KÖRS FRAMÅT
	TCCR1A = TCCR1A | (1<<COM1B0);
	PORTC = PORTC | 0b00000010;
	//HÖGER MOTOR KÖRS FRAMÅT
	TCCR1A = TCCR1A & 0b10111111;
	PORTC = PORTC & 0b11111110;
}

void Car_spin_right(float R_scaler)
{
	OCR1B =(-6400*R_scaler)+ 8200;
	OCR1A = OCR1B;
	//HÖGER MOTOR INVERTERAS FÖR ATT BACKA VÄNSTER MOTOR KÖRS FRAMÅT
	TCCR1A = TCCR1A | (1<<COM1A0);
	PORTC = PORTC | 0b00000001;
	//HÖGER MOTOR KÖRS FRAMÅT
	TCCR1A = TCCR1A & 0b11101111;
	PORTC = PORTC & 0b11111101;
}

void Car_reverse_speed(float R_scaler,float L_scaler,uint16_t y_vlu)
{
	uint16_t OC_temp = 0;
	//MAXIMAL FART BAKÅT GES AV MAXIMAL INPUT 1024 ger 0% duty cycle ut pga inverterad och 546 ger 64% duty cycle
	OC_temp = (6.68*(y_vlu-510)) + 1800;
	
	
	OCR1A = OC_temp;
	OCR1B = OC_temp;
	OCR1A =  R_scaler * OCR1A;
	OCR1B = OCR1B * L_scaler;
	//BAKÅT
	//INVERTERA PWM
	
	TCCR1A = TCCR1A |(1<<COM1A0) | (1<<COM1B0);
	PORTC = PORTC | 0b00000011;
	
}

void Car_forward_speed(float R_scaler,float L_scaler,uint16_t y_vlu)
{
	uint16_t OC_temp = 0;
	//535 ger 1800 vilket är min duty cycle för att köra och 15 ger 100% duty cycle
	OC_temp = (-6.15*(y_vlu)) + 5092;
	
	OCR1A = OC_temp;
	OCR1B = OC_temp;
	OCR1A =  R_scaler * OCR1A;
	OCR1B = OCR1B * L_scaler;
	//FRAMÅT
	TCCR1A = TCCR1A & 0b10101111;
	PORTC = PORTC & 0b11111100;
	
}



void Car_calculate_speed(float R_scaler,float L_scaler,uint16_t y_vlu)
{	
	//Kontrollerar framåt/bakåt/stå still eller om bilen ska svänga på stället
	if(y_vlu > 515 && y_vlu < 1030)
	{
		Car_reverse_speed(R_scaler,L_scaler,y_vlu);
	}
	else if(y_vlu > 0 && y_vlu < 480)
	{		
		Car_forward_speed(R_scaler,L_scaler,y_vlu);	
	}
	else if(L_scaler != 1)
	{
		Car_spin_left(L_scaler);
	}
	else if(R_scaler != 1)
	{
		Car_spin_right(R_scaler);
	}
	else
	{
		OCR1A = 0;
		OCR1B = 0;
		TCCR1A = TCCR1A & 0b10101111;
		PORTC = PORTC & 0b11111100;
	}
	
	
}

void Car_honk(uint16_t h_vlu)
{
	if(h_vlu == 1)
	{
		TCCR0B = TCCR0B | (1<<CS02);
	}
	else
	{
		TCCR0B = TCCR0B & 0b11111000;
	}
}

void Car_exectue_command(void)
{
	uint16_t x_vlu = 0;
	uint16_t y_vlu = 0;
	uint16_t h_vlu = 0;
	float L_scaler = 1;
	float R_scaler = 1;
	Car_decode_buffer(&x_vlu,&y_vlu,&h_vlu);
	Car_calculate_turn(&x_vlu,&L_scaler,&R_scaler);
	Car_calculate_speed(R_scaler,L_scaler,y_vlu);
	Car_honk(h_vlu);
	
	
	
}








