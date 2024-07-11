/*
 * gpio.h
 *
 *  Created on: 07-Apr-2024
 *      Author: karti
 */

#ifndef GPIO_H_
#define GPIO_H_


#include "global.h"


/*
 * FUNCTIONS DEFINATION
 */

void gpio_init(void);

void PORTA_CONFIG(void);

void PORTF_CONFIG(void);


void PORTA_handler(void);
void PORTF_handler(void);

int left();
int center();

int right();
int left_2();
int right_2();



#endif /* GPIO_H_ */
