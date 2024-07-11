//*****************************************************************************
//
// freertos_demo.c - Simple FreeRTOS example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************
#include "inc/tm4c123GH6pm.h"

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "motor_pwm.h"
#include "init.h"
#include "uart_debug.h"
#include "uart.h"


TaskHandle_t task_compute_sensor_handler = NULL;

TaskHandle_t task_run_motors_transmit_handler = NULL;

int readings = 0;

// cv -> current_value.

 int sensor_value;
 int sw[8];
 int w[8];
 int w_sum;
 uint32_t porta_handler_value;
 int port_value;
int temp;
void task_computer_sensor(void *p){

    while(1){






        vTaskSuspend(NULL);

        sw[0] = left_2();
        sw[1] = left();
        sw[2] = center();
        sw[3] = right();
        sw[4] = right_2();


        w[0] = -1;
        w[1] = -1;
        w[2] = 0;
        w[3] = 1;
        w[4] = 1;

        w_sum = w[0] * sw[0] + w[1] * sw[1] + w[2] * sw[2] + w[3] * sw[3]
                + w[4] * sw[4];



    }

}

void task_run_motors_transmit(void *p){
while(1){

    int port_value = GPIO_PORTA_DATA_R;
       if (port_value == 127)
           sensor_value = 0;

       if(sensor_value==0){
           UART2_Transmitter('S');
           motors_move_stop();
       }

           if(sw[0]==0 && sw[1]==0 && sw[2]==0 && sw[3]==0 && sw[4]==0 ){

               UART2_Transmitter('S');
               motors_move_stop();

           }
           else if(sw[0]==1 && sw[1]==1 && sw[2]==1 && sw[3]==1 && sw[4]==1 ){
             GPIO_PORTF_DATA_R=0x08;
             UART2_Transmitter('S');
             motors_move_stop();

           }
           else if(w_sum==0){
               GPIO_PORTF_DATA_R=0x04;
               UART2_Transmitter('F');
               motors_move_forward();

           }
           else if(w_sum>0){
               GPIO_PORTF_DATA_R=0x08;
               UART2_Transmitter('R');

               motors_move_right();

           }
           else if(w_sum<0){
               GPIO_PORTF_DATA_R=0x08;

               UART2_Transmitter('L');
               motors_move_left();

           }
           delayMs(1);



}

}
int main(void)
{

    // configuration start.
        pwm_init_motor_left();
        pwm_init_motor_right();

        init();
        UART_Init_DEBUG();
        UART_Init();
        set_duty_cycle(35, 35);
    // configuration end.

        xTaskCreate(task_computer_sensor , "read_sensor" ,200 ,(void*) 0 ,0 ,&task_compute_sensor_handler );
        xTaskCreate(task_run_motors_transmit , "run motors" ,200 ,(void*) 0 ,0 ,&task_run_motors_transmit_handler );
        vTaskStartScheduler();
}


void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}



void delayMs(int n)
{

    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 1500; j++)
        {
        } /* do nothing for 1 ms */
}

void myUartHandler_DEBUG(void)
{
    char temp_str[30];

    UART0_ICR_R &= ~(0x010); // Clear receive interrupt
    unsigned char c = 0;
    c = UART0_DR_R; // get the received data byte

    // send data that is received
    UART0_Transmitter_DEBUG(c);

}
void Uart2_Handler(void)
{

    char temp_str[30];
    char c = 0;

    UART2_ICR_R &= ~(0x010); // Clear receive interrupt

    c = UART2_DR_R; // get the received data byte
    // send data that is received

    /*     if(c=='4'){
     GPIO_PORTF_DATA_R = 0x02;
     print_DEBUG("detected.");
     }

     if(c=='7')
     GPIO_PORTF_DATA_R = 0x04;


     UART2_Transmitter(c);
     */

}


void PORTA_handler(void)
{

    //GPIO_PORTF_DATA_R = COLOR_WHITE_ON;

    porta_handler_value = ~GPIO_PORTA_DATA_R;
    GPIO_PORTA_ICR_R = SENSOR_READ;  // Clear the interrupt flag for Port A
    //print_num(porta_handler_value);
   // GPIO_PORTA_DATA_R = 0xFF;

    BaseType_t checkIfYieldRequired;
    checkIfYieldRequired = xTaskResumeFromISR(task_compute_sensor_handler);
    portYIELD_FROM_ISR(checkIfYieldRequired);

}

int ir_turn_read_only_value;

void enable_global_interrupts(void)
{
  //  __asm("CPSIE I");
    portENABLE_INTERRUPTS();
}

void disable_global_interrupts(void)
{
  //  __asm("CPSID  I");
    portDISABLE_INTERRUPTS()
}

void init(void)
{
    gpio_init();
    enable_global_interrupts();

}
