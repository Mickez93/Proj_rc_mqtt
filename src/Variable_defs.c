/*
 * Global_variables.c
 *
 * Created: 2022-11-30 13:40:50
 *  Author: mini0072
 */ 
#include <inttypes.h>

volatile uint8_t LADC_res = 0;
volatile uint8_t HADC_res = 0;
volatile uint8_t ADC_flg = 0;
uint16_t prev_avg[10] = {350};
uint8_t Instr_buffer[13] = {0};
volatile uint8_t char_count = 0;
volatile uint16_t timer2_counter = 0;
volatile uint8_t send_rng_flg = 0;
volatile uint16_t timeout_counter = 0;
volatile uint8_t new_command_flg = 0;
volatile uint8_t Car_reverse_flg = 0;
volatile uint8_t Car_forward_flg = 0;


	