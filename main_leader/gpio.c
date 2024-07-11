/*
 * gpio.c
 *
 *  Created on: 07-Apr-2024
 *      Author: karti
 */

#include "gpio.h"
#include "ir_sensor.h"

#define GPIO_PORTA_PRI 3
#define GPIO_PORTF_PRI 5

extern int readings;

void gpio_init(void)
{
    PORTA_CONFIG();
    PORTF_CONFIG();
}

void PORTA_CONFIG(void)
{
    SYSCTL_RCGC2_R |= 0x00000001; /* Enable clock to GPIO_A_ at clock gating control register */
    SYSCTL_RCGCGPIO_R |= 0x00000001; /* Enable and provide a clock to GPIO Port_A_ in Run mode */
    while ((SYSCTL_PRGPIO_R & 0x01) == 0)
    {
    }; // Wait for clock to stabilize

    GPIO_PORTA_DIR_R &= ~SENSOR_READ; /*  GPIO Direction | 0 -> INPUT | 1 -> OUTPUT */

    GPIO_PORTA_AFSEL_R |= 0x00000000; /* Disable alternate function on PORT */

    GPIO_PORTA_AMSEL_R |= 0x00000000; /* Disable analog function on PORT */

    GPIO_PORTA_PCTL_R &= ~SENSOR_READ; /* Regular digital function */
    GPIO_PORTA_DEN_R |= SENSOR_READ; /* enable the GPIO pins for digital function */

    //Enable Interrupts
    NVIC_EN0_R |= (1 << 0);  // Enable NVIC interrupt 16 (GPIO Port A)
    GPIO_PORTA_IM_R &= ~SENSOR_READ; /* Mask Register */
    GPIO_PORTA_IBE_R &= ~SENSOR_READ; /* Controlling interrupt by IEV register */
    GPIO_PORTA_IS_R &= ~SENSOR_READ; /* Enable Edge detection */
    GPIO_PORTA_IEV_R &= ~(SENSOR_READ); /* Rising edge for PA2,3,5,6*/
    GPIO_PORTA_RIS_R &= ~SENSOR_READ; /* Clearing the raw interrupt status */
    GPIO_PORTA_MIS_R &= ~SENSOR_READ;
    GPIO_PORTA_IM_R |= SENSOR_READ; /* Enable interrupt to NVIC */

    //Set priority for PORTA interrupt
    NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFFFF00) | (GPIO_PORTA_PRI << 5) << 0;
}

void PORTF_CONFIG(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20; // Enable Clock for GPIO Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0)
    {
    }; // Wait for clock to be enabled

    GPIO_PORTF_LOCK_R = 0x4C4F434B;  //Open lock for PORTF
    GPIO_PORTF_CR_R = 0x01;  //Enable configuration of PORTF

    GPIO_PORTF_DIR_R = 0x0E; /* enable the GPIO pins for the LED (PF3, 2, 1) as output */
    GPIO_PORTF_DEN_R = 0x1F; /* enable the GPIO pins for digital function */
    GPIO_PORTF_PUR_R = 0x11; /*PULL register for SW1 and SW2 */

    // Register the interrupt handler for Port F
    NVIC_EN0_R |= 0x40000000;  // Enable NVIC interrupt 30 (GPIO Port F)
    GPIO_PORTF_IM_R &= ~0x11;   // Mask interrupt for PF4 and PF0
    GPIO_PORTF_IBE_R = 0x00; //Interrupt generation controlled by GPIO event register
    GPIO_PORTF_IS_R = 0x00;     //Edge sensitive
    GPIO_PORTF_IEV_R = 0x11; //Rising edge detection since PF0 and PF4 in pull mode
    GPIO_PORTF_RIS_R = 0x00;     //Clear raw interrupt status Register
    GPIO_PORTF_MIS_R = 0x00;    //Clear Mask interrupt status Register
    GPIO_PORTF_IM_R |= 0x11;   // Unmask interrupt for PF4 and PF0

    // Set priority for Port F interrupt
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | (GPIO_PORTF_PRI << 5) << 16; // Priority 5

}


uint32_t porta_handler_value;


// cv stores current ir sensor values .
 volatile int sensor_value;


void PORTA_handler(void)
{

    //GPIO_PORTF_DATA_R = COLOR_WHITE_ON;

    porta_handler_value = ~GPIO_PORTA_DATA_R;
    GPIO_PORTA_ICR_R = SENSOR_READ;  // Clear the interrupt flag for Port A
    //print_num(porta_handler_value);
    sensor_value = (left_2() + left() + center() + right() + right_2());


}




/* Sensors : L2 Left CENTER Right R2 */
int left_2(){
    // black

    if ((porta_handler_value & (IR_SEN_PIN1)) == (IR_SEN_PIN1) ){


        return 1;

    }else{
        return 0;
    }

}

int left(){

    if ( (porta_handler_value & (IR_SEN_PIN2)) == (IR_SEN_PIN2)  ){

        return 1;

    }else{
        return 0;
    }

}

int center(){

    if ( (porta_handler_value & (IR_SEN_PIN3)) == (IR_SEN_PIN3)  ){


        return 1;

    }else{
        return 0;
    }

}

int right(){

    if ( (porta_handler_value & (IR_SEN_PIN4)) == (IR_SEN_PIN4)  ){

        return 1;

    }else{
        return 0;
    }

}

int right_2(){

    if ( (porta_handler_value & (IR_SEN_PIN5)) == (IR_SEN_PIN5)  ){

        return 1;

    }else{
        return 0;
    }

}





void PORTF_handler(void)
{
    GPIO_PORTF_ICR_R = 0x11;  // Clear the interrupt flag for PF0
    static bool test = true;
    test = !test;
//    if (test)
//        GPIO_PORTF_DATA_R = COLOR_YELLOW_ON;
//    else
//        GPIO_PORTF_DATA_R = COLOR_RED_ON;
}
