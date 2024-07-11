#include <stdint.h>
#include "uart_debug.h"
#include "uart.h"

#include "inc/tm4c123GH6pm.h"

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

 int sensor_value;
 int sw[8];
 int w[8];
 int w_sum;

int main(void)

{
    uint16_t i;

    pwm_init_motor_left();
    pwm_init_motor_right();

    init();
    UART_Init_DEBUG();
    UART_Init();

    print_DEBUG("Welcome\n");
    set_duty_cycle(30, 30);
    int sequence=0;
    char seq_send;


    while(1){
        int port_value = GPIO_PORTA_DATA_R;
        if (port_value == 127)
            sensor_value = 0;

        if(sensor_value==0){
            UART2_Transmitter('S');
            motors_move_stop();
        }


        sw[0] = left_2();
        sw[1] = left();
        sw[2] = center();
        sw[3] = right();
        sw[4] = right_2();

        w[0]=-1;
        w[1]=-1;
        w[2]=0;
        w[3]=1;
        w[4]=1;

        w_sum = w[0]*sw[0] + w[1]*sw[1] + w[2]*sw[2] + w[3]*sw[3] + w[4]*sw[4];


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
