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
//Buffer för instruktioner till bilen
extern uint8_t Instr_buffer[13];
//Räknare för instruktioner till bilen
extern volatile uint8_t char_count;

//Räknare för timer 2 som ska skicka range 2ggr per sekund
extern volatile uint16_t timer2_counter;
//Flagga för när timer är klar och range ska skickas
extern volatile uint8_t send_rng_flg;
//Räknare på timer2 som kollar när 2 sekunder har gått sedan senaste kommandot
extern volatile uint16_t timeout_counter;
//Försöka få bilen att inte dö vid snabba kommandon, kan endast få ett nytt kommando var 0.25 s
extern volatile uint8_t new_command_flg;
//FLAGGOR FÖR ATT BLOCKERA SNABBA OMSTÄLLNINGAR
extern volatile uint8_t Car_reverse_flg;
extern volatile uint8_t Car_forward_flg;





#endif /* GLOBAL_VARIABLES_H_ */