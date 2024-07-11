/*
 * blink.c
 *
 *  Created on: Jan 27, 2024
 *      Author: kunal
 */
#include <stdio.h>
#include <stdint.h>

#include "inc/tm4c123GH6pm.h"

//PD6 - Rx and PD7 - Tx

void UART_Init(void)
{

          SYSCTL_RCGCUART_R |= (1<<2);            /* activate UART2 */
          SYSCTL_RCGCGPIO_R |= (1<<3);            /* activate port d */
          delayMs(10);



          UART2_CTL_R = 0;      /* disable UART */

          UART2_CC_R = 0;
          UART2_IBRD_R = 8;        /* IBRD = int(16,000,000 / (16 * 115,200)) = int(8.680) */
          UART2_FBRD_R = 44;       /* FBRD = round(0.5104 * 64 ) = 44 */
                                   /* 8 bit word length (no parity bits, one stop bit, FIFOs) */
          UART2_LCRH_R = (UART_LCRH_WLEN_8);
          UART2_CTL_R =0x301;       /* enable UART */


          GPIO_PORTD_LOCK_R = 0x4C4F434B;
          GPIO_PORTD_CR_R |=  ((1<<6) | (1<<7)) ;
          GPIO_PORTD_AFSEL_R |= ((1<<6) | (1<<7)) ;           /* enable alt funct on PD6,PD7 */
          GPIO_PORTD_DEN_R |= ((1<<6) | (1<<7));                /* enable digital I/O on pd6-pd7 */
          GPIO_PORTD_PCTL_R |= 0x11000000; /* configure PD6-7 as UART */
          GPIO_PORTD_AMSEL_R &= ~((1<<6) | (1<<7)) ;          /* disable analog functionality on Pd6 , pd7 */

          // interrupts
          UART2_IM_R=(1<<4); //enable UART Rx interrupt
          UART2_ICR_R &= ~(0x010); // Clear receive interrupt

          NVIC_EN1_R |= (1<<1);
          //NVIC_SYS_PRI1_R |= (4<<5)<<8;


          //
}

/* UART_InChar
* Wait for new serial port input
* Input: none
* Output: ASCII code for key typed
*/
char UART_InChar(void)
{
      while( (UART2_FR_R & UART_FR_RXFE) != 0)
          ;
      return((char)(UART2_DR_R & 0xFF));
}



void UART2_Transmitter(unsigned char data)
{
    while((UART2_FR_R & UART_FR_TXFF) != 0); /* wait until Tx buffer not full */
    UART2_DR_R = data;                  /* before giving it another byte */
}








/* UART_OutChar
* Output 8-bit to serial port
* Input: letter is an 8-bit ASCII character to be transferred
* Output: none
*/
void UART_OutChar(char data)
{
      while((UART2_FR_R & UART_FR_TXFF) != 0)
          ;
      UART2_DR_R = data;
}



void error(){
    char *errormsg = "\n\rcommand help\n\r";
    while( *errormsg)
            UART_OutChar(*errormsg++);

}

void print(char word[]){
    int i=0;
    while(word[i]!='\0'){
        UART_OutChar(word[i++]);
    }



}
void print_num(int n){

char a[20];
sprintf(a,"%d\n\0" , n);
print(a);


}

int mystringcompare(char a[] , char b[]){

// flag 0 means equal.
int i=0 , j=0;
int flag=0;
int max=0;

while(a[i]!='\0'){
    i++;
}
max = i;
i=0;
while(b[i]!='\0'){
    i++;
}

if(i>max) max =i;

i=0;

while(a[i]!='\0' && b[i]!='\0'){
    if(a[i]!=b[i])
        return 1;
    i++;


}

if(i!=max) return 1;

return 0;
}


