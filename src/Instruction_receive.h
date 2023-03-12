/*
 * Instruction_receive.h
 *
 * Created: 2022-12-05 15:05:02
 *  Author: mini0072
 */ 


#ifndef INSTRUCTION_RECEIVE_H_
#define INSTRUCTION_RECEIVE_H_

void Uart_rx_buffer(uint8_t UART_RX);

void Uart_reset_buffer(void);

void UART_send(uint8_t Range);

void UART_init(void);



#endif /* INSTRUCTION_RECEIVE_H_ */