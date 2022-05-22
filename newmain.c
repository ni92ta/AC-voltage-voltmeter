/*
 * File:   newmain.c
 * Author: Никита
 *
 * Created on 11 мая 2022 г., 19:04
 */


#define _XTAL_FREQ 4000000
#include <xc.h>
#include "newfile.h"

#define SER RC5// данные
#define SRCLK RC4// загрузка битов 
#define RCLK RC3// вывод данных

#define DIG1 RC0// вывод данных
//#define DIG2 RC1// вывод данных
//#define DIG3 RC2// вывод данных

#define RESie8 RC1// сброс ИЕ8
unsigned char i;

unsigned char digit [11] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b00000000 
    
};

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
//------------------------------------------------------------------------------

void main(void) {
    unsigned char l;
    unsigned char e = 0;
    unsigned char w = 0;
    unsigned char q = 0;
    PORTA = 0b00000000;
    TRISA = 0b00000000;
    PORTC = 0b00000000;
    TRISC = 0b00000000;
    ANSEL = 0b00000000;
    CM2 = 1;
    CM1 = 1;
    CM0 = 1;

    RESie8 = 1;
    while (1){
      //  DIG1 = 1;
        __delay_ms(1);
         
        RESie8 = 0;
        
        for (l=0;l<999;l++){
            senddata (digit [q], digit [w], digit [e]);
            e++;
            if (e == 9){
                e = 0;
                w++;
            }
                        if (w == 9){
                w = 0;
                q++;
            }
            
                                    if (q == 9){
                q = 0;
               // q++;
            }
            
           senddata (digit [q], digit [w], digit [e]); 
                           }
   
       
      // senddata (digit [10], digit [2], digit [3]);  
        
        
         //   __delay_ms(1000);
            /*
    senddata (digit [1]); 
            __delay_ms(1000);
    senddata (digit [2]); 
    //DIG1 = 0;
     //DIG2 = 1;
            __delay_ms(1000);
    senddata (digit [3]); 
            __delay_ms(1000);
    senddata (digit [4]); 
            __delay_ms(1000);
    senddata (digit [5]);
        DIG2 = 0;
     DIG3 = 1;
            __delay_ms(1000);
    senddata (digit [6]); 
            __delay_ms(1000);
    senddata (digit [7]); 
            __delay_ms(1000);
    senddata (digit [8]); 
            __delay_ms(1000);
    senddata (digit [9]);
    DIG3 = 0;
              */
    }
}
