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


TaskHandle_t task_read_uart_handler = NULL;

TaskHandle_t task_run_motors_transmit_handler = NULL;

int readings = 0;

// cv -> current_value.

char temp_str[30];
     char c = 0;
     int value=0;


void task_read_uart(void *p){
while(1){

    vTaskSuspend(NULL);

    switch(value){
    case 'F' :
        motors_move_forward();
        break;
    case 'S':
        motors_move_stop();
        break;
    case 'L':
        motors_move_left();
        break;
    case 'R':
        motors_move_right();
        break;
    default:
        motors_move_stop();

    }


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
        set_duty_cycle(30, 30);
    // configuration end.

        xTaskCreate(task_read_uart , "read_uart" ,200 ,(void*) 0 , tskIDLE_PRIORITY ,&task_read_uart_handler );

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


    //UART0_Transmitter_DEBUG(c);

}

void Uart2_Handler(void)
{

     temp_str[30];
      c = 0;



     c = UART2_DR_R; // get the received data byte


     //print_DEBUG("Recived : ");
      value = c-'0';

    // print_num_DEBUG(value);

    // send data that is received



     UART2_ICR_R &= ~(0x010); // Clear receive interrupt
    //UART2_Transmitter(c);

        BaseType_t checkIfYieldRequired;
        checkIfYieldRequired = xTaskResumeFromISR(task_read_uart_handler);
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
