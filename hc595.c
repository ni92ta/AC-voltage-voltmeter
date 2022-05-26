/*
 * File:   hc595.c
 * Author: Никита
 *
 * Created on 25 мая 2022 г., 18:34
 */

#define _XTAL_FREQ 4000000
#include "hc595.h"
#include <xc.h>
unsigned char i;

//unsigned char digit [11] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
//0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b00000000 
    
//};

//-------------------отправка данных--------------------------------------------
void senddata (unsigned char data, unsigned char data2, unsigned char data3){
    unsigned char outt;
    unsigned char u = 0;
    for (u=0;u<3;u++){   
RCLK = 0;            
for (i=0;i<8;i++){   
    SRCLK = 0;
    __delay_us(1);
    if (outt & 0x80){
        SER = 1;
    }
    else{
        SER = 0;
    }
    outt=(outt<<1);
    SRCLK = 1;
    __delay_us(1);
                }  
 RCLK = 1; 
 DIG1 = 1; 
__delay_ms(5);
                    if (u == 2){
                    outt = data;
                               }
            
                    if (u == 0){
                    outt = data2;
                               }

                    if (u == 1){
                    outt = data3;
                               }
DIG1 = 0;

                   }    
}

