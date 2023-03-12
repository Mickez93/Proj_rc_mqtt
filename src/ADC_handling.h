/*
 * ADC_handling.h
 *
 * Created: 2022-11-29 15:56:06
 *  Author: mini0072
 */ 


#ifndef ADC_HANDLING_H_
#define ADC_HANDLING_H_


void enable_adc(void);
void choose_adc_input(uint8_t ADC_channel);
void run_conversion(void);
uint8_t Calc_range(uint16_t D_ut);
void calc_avg(uint16_t Data,uint16_t *Prev_avg, uint8_t length);
uint16_t ADC_get_result(void);
uint8_t Get_range(void);
void Range_check(uint8_t Range);
void Range_ascii_send(uint8_t Range);








#endif /* ADC_HANDLING_H_ */