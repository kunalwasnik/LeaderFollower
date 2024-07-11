/*
 * motor_pwm.c
 *
 *  Created on: 24-Apr-2024
 *      Author: kunal
 */


// pe4 pe5

#include <stdint.h>

#include "inc/tm4c123gh6pm.h"
#include "motor_pwm.h"

void pwm_init_motor_right()
{

    SYSCTL_RCGCPWM_R |= (1<<0);

    SYSCTL_RCGC2_R |= (1<<4);
    // use system clock
    SYSCTL_RCC_R &= ~(1<<20);

    GPIO_PORTE_AFSEL_R |= ((1<<4)| (1<<5) ) ;
    GPIO_PORTE_PCTL_R |= ((1<<18) | (1<<22));

    GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINF)| (1<<MOTOR_RIGHT_PINB) ) ;
    GPIO_PORTE_DIR_R |= ((1<<MOTOR_RIGHT_PINF)| (1<<MOTOR_RIGHT_PINB) ) ;


    // disable pwm first.
    PWM0_2_CTL_R  &= ~(1<<0);
    // down count mode.
    PWM0_2_CTL_R  &= ~(1<<1); /* down counter */

    PWM0_2_LOAD_R = LOAD_VALUE_PWM;       /* set load value for 1kHz (16MHz/16000) */
    PWM0_2_CMPA_R = LOAD_VALUE_PWM-1;    // minimum.
    PWM0_2_CMPB_R = LOAD_VALUE_PWM-1;
    //PWM0_2_CMPB_R = LOAD_VALUE_PWM-1;     // minimum.



    PWM0_2_GENA_R |= ((1<<2) | (1<<3) | (1<<7));
    PWM0_2_GENB_R |= ((1<<2) | (1<<3) | (1<<11));

    PWM0_2_CTL_R |= (1<<0);
    PWM0_ENABLE_R |= ((1<<4) |(1<<5) );





}

void pwm_init_motor_left(){


       SYSCTL_RCGCPWM_R |= (1<<0);

       // enable port b
       SYSCTL_RCGC2_R |= (1<<1);
       // use system clock
       SYSCTL_RCC_R &= ~(1<<20);





       // setting PB6 , pB7 pin. for m0pwm4 , m0pwm5.

       GPIO_PORTB_AFSEL_R |= ((1<<6)| (1<<7) ) ;

       // alternate function for PB6 , m0pwm4
       GPIO_PORTB_PCTL_R |= 0x4000000;
       // alternate function for PB7 , m0pwm5
       GPIO_PORTB_PCTL_R |= 0X40000000;


       GPIO_PORTB_DEN_R &= ~((1<<MOTOR_LEFT_PINF)| (1<<MOTOR_LEFT_PINB) ) ;
       GPIO_PORTB_DIR_R |= ((1<<MOTOR_LEFT_PINF)| (1<<MOTOR_LEFT_PINB) ) ;

       //pwm parameter configuration.

       // disable pwm first.
       PWM0_0_CTL_R  &= ~(1<<0);
       // down count mode.
       PWM0_0_CTL_R  &= ~(1<<1); /* down counter */

       // load value
       PWM0_0_LOAD_R = LOAD_VALUE_PWM;       /* set load value for 1kHz (16MHz/16000) */
       PWM0_0_CMPA_R = LOAD_VALUE_PWM-1;   // 5.
       PWM0_0_CMPB_R = LOAD_VALUE_PWM-1;     // minimum.

       PWM0_0_GENA_R |= ((1<<2) | (1<<3) | (1<<7));
       PWM0_0_GENB_R |= ((1<<2) | (1<<3) | (1<<11));

       PWM0_0_CTL_R |= (1<<0);
       PWM0_ENABLE_R |= ((1<<0) |(1<<1) );


}


void motors_move_stop(){

    GPIO_PORTB_DEN_R &= ~((1<<MOTOR_LEFT_PINF)| (1<<MOTOR_LEFT_PINB) ) ;
    GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINF)| (1<<MOTOR_RIGHT_PINB) ) ;

}

void motors_move_forward(){
//    PWM0_0_CMPA_R = DUTY_CYCLE;   // 5.
//    PWM0_0_CMPB_R = LOAD_VALUE_PWM-1;     // minimum.
//
//    PWM0_2_CMPA_R=DUTY_CYCLE;
//    PWM0_2_CMPB_R=LOAD_VALUE_PWM-1;


    GPIO_PORTB_DEN_R |= (1<<MOTOR_LEFT_PINF);
    GPIO_PORTB_DEN_R &= ~(1<<MOTOR_LEFT_PINB);

    GPIO_PORTE_DEN_R |= ((1<<MOTOR_RIGHT_PINF)) ;
    GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINB)) ;

}


void motors_move_back(){


    GPIO_PORTB_DEN_R &= ~(1<<MOTOR_LEFT_PINF);
    GPIO_PORTB_DEN_R |= (1<<MOTOR_LEFT_PINB);

    GPIO_PORTE_DEN_R &= ~(1<<MOTOR_RIGHT_PINF) ;
    GPIO_PORTE_DEN_R |= (1<<MOTOR_RIGHT_PINB) ;


}



void motors_move_right(){

      GPIO_PORTB_DEN_R |= (1<<MOTOR_LEFT_PINF);
      GPIO_PORTB_DEN_R &= ~(1<<MOTOR_LEFT_PINB);

      GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINF)) ;
      GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINB)) ;

}

void motors_move_sharp_right(){

    GPIO_PORTB_DEN_R |= (1<<MOTOR_LEFT_PINF);
    GPIO_PORTB_DEN_R &= ~(1<<MOTOR_LEFT_PINB);

    GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINF)) ;
    GPIO_PORTE_DEN_R |= ((1<<MOTOR_RIGHT_PINB)) ;

}

void motors_move_left(){

    GPIO_PORTB_DEN_R &= ~(1<<MOTOR_LEFT_PINF);
    GPIO_PORTB_DEN_R &= ~(1<<MOTOR_LEFT_PINB);

    GPIO_PORTE_DEN_R |= ((1<<MOTOR_RIGHT_PINF)) ;
    GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINB)) ;

}

void motors_move_sharp_left(){

    GPIO_PORTB_DEN_R &= ~(1<<MOTOR_LEFT_PINF);
    GPIO_PORTB_DEN_R |= (1<<MOTOR_LEFT_PINB);

    GPIO_PORTE_DEN_R |= ((1<<MOTOR_RIGHT_PINF)) ;
    GPIO_PORTE_DEN_R &= ~((1<<MOTOR_RIGHT_PINB)) ;

}


void set_duty_cycle(int d1 , int d2 ){


int duty_cycle1  , duty_cycle2;
    if(d1>100)
        d1=100;
    else if(d1<=0){
        duty_cycle1=  LOAD_VALUE_PWM-1;
    }else{
        duty_cycle1 = ((100-d1)*LOAD_VALUE_PWM)/100;

    }

    if(d2>100)
        d2=100;
    else if(d2<=0){
        duty_cycle1=  LOAD_VALUE_PWM-1;
    }else{
        duty_cycle2 = ((100-d2)*LOAD_VALUE_PWM)/100;

    }





    duty_cycle1 = ((100-d1)*LOAD_VALUE_PWM)/100;
    duty_cycle2 = ((100-d2)*LOAD_VALUE_PWM)/100;


    PWM0_0_CMPA_R = duty_cycle1;


    PWM0_2_CMPA_R=duty_cycle2;


    // reverse pins.

    PWM0_0_CMPB_R = duty_cycle1;   // 5.


    PWM0_2_CMPB_R=duty_cycle2;




}
