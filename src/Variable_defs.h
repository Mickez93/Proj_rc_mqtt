/*
 * Global_variables.h
 *
 * Created: 2022-11-30 13:41:05
 *  Author: mini0072
 */ 


#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_
//ADC hantering
extern volatile uint8_t LADC_res;
extern volatile uint8_t HADC_res;
extern volatile uint8_t ADC_flg;
//Moving avg array
extern uint16_t prev_avg[10];
//Buffer f�r instruktioner till bilen
extern uint8_t Instr_buffer[13];
//R�knare f�r instruktioner till bilen
extern volatile uint8_t char_count;

//R�knare f�r timer 2 som ska skicka range 2ggr per sekund
extern volatile uint16_t timer2_counter;
//Flagga f�r n�r timer �r klar och range ska skickas
extern volatile uint8_t send_rng_flg;
//R�knare p� timer2 som kollar n�r 2 sekunder har g�tt sedan senaste kommandot
extern volatile uint16_t timeout_counter;
//F�rs�ka f� bilen att inte d� vid snabba kommandon, kan endast f� ett nytt kommando var 0.25 s
extern volatile uint8_t new_command_flg;
//FLAGGOR F�R ATT BLOCKERA SNABBA OMST�LLNINGAR
extern volatile uint8_t Car_reverse_flg;
extern volatile uint8_t Car_forward_flg;





#endif /* GLOBAL_VARIABLES_H_ */