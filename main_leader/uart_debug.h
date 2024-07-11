/*
 * uart.h
 *
 *  Created on: Jan 27, 2024
 *      Author: kunal
 */

#ifndef UART_DEBUG_H_
#define UART_DEBUG_H_

int mystringcompare_DEBUG(char [] , char []);
void print_DEBUG(char []);
void error_DEBUG();
void UART0_Transmitter_DEBUG(unsigned char );



void UART_Init_DEBUG(void);
char UART_InChar_DEBUG(void);
void print_num_DEBUG(int n);
void UART_OutChar_DEBUG(char data);



#endif /* UART_DEBUG_H_ */
