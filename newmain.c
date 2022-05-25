/*
 * File:   newmain.c
 * Author: Никита
 *
 * Created on 11 мая 2022 г., 19:04
 */
#define _XTAL_FREQ 4000000
#include <xc.h>
#include "newfile.h"

#define RESie8 RC1// сброс микросхемы ИЕ8
unsigned char i;

//---------------------------Массив с цифрами-----------------------------------
unsigned char digit [11] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,//0, 1, 2, 3, 4,
0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b00000000//5, 6, 7, 8, 9  
};
//------------------------------------------------------------------------------

void main(void) {
    unsigned char l;
    unsigned char e = 0;
    unsigned char w = 0;
    unsigned char q = 0;
    PORTA = 0b00000000;
    TRISA = 0b00000110;
    PORTC = 0b00000000;
    TRISC = 0b00000000;
    ANSEL = 0b00000000;
    CM2 = 1;
    CM1 = 1;
    CM0 = 1;

    RESie8 = 1;//сброс счётчика, высоким уровнем, при включении
    while (1){
      //  DIG1 = 1;
        __delay_ms(1);
         
        RESie8 = 0;//сброс счётчика при вкл
        
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
