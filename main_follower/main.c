#include <stdint.h>
#include "uart_debug.h"
#include "uart.h"

#include "inc/tm4c123gh6pm.h"

#include "motor_pwm.h"
#include "init.h"

int ir_turn_read_only_value;

void enable_global_interrupts(void)
{
    __asm("CPSIE I");
}

void disable_global_interrupts(void)
{
    __asm("CPSID  I");
}

void init(void)
{
    gpio_init();
    enable_global_interrupts();

}

int readings = 0;

// cv -> current_value.

extern int sensor_value;

int main(void)

{
    uint16_t i;


    pwm_init_motor_left();
    pwm_init_motor_right();


    init();
    UART_Init_DEBUG();
    UART_Init();

    print_DEBUG("Receiver");
    set_duty_cycle(30, 30);

    while (1)
    {




    }

    return 0;
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

    char temp_str[30];
     char c = 0;



     c = UART2_DR_R; // get the received data byte
     print_DEBUG("Recived : ");
     int value = c-'0';

     print_num_DEBUG(value);

    // send data that is received

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

     UART2_ICR_R &= ~(0x010); // Clear receive interrupt
    //UART2_Transmitter(c);


}
