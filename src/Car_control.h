/*
 * Car_control.h
 *
 * Created: 2022-12-01 11:43:36
 *  Author: mini0072
 */ 


#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

void Car_init_control(void);
void Car_exectue_command(void);
void Car_decode_buffer(uint16_t *x_vlu, uint16_t *y_vlu, uint16_t h_vlu);
void Car_calculate_turn(uint16_t *x_vlu);
void Car_calculate_speed(float R_scaler,float L_scaler);
void Car_honk(uint16_t h_vlu);
void Car_shut_down(void);
void Car_forward_speed(float R_scaler,float L_scaler,uint16_t y_vlu);
void Car_reverse_speed(float R_scaler,float L_scaler,uint16_t y_vlu);
void Car_spin_left(float L_scaler);
void Car_spin_right(float R_scaler);



#endif /* CAR_CONTROL_H_ */