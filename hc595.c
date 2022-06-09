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

//-------------------отправка данных--------------------------------------------
void senddata (unsigned char data, unsigned char data2, unsigned char data3){
    unsigned char outt;
    unsigned char u = 0;
      for (cirkle=0;cirkle<2;cirkle++){//цикл добавлен так как не показывало одну цифру
//нужно разобраться почему
    for (u=0;u<3;u++){   
RCLK = 0;            
for (i=0;i<8;i++){   
    SRCLK = 0;
    __delay_us(1);
    if (outt & 0x80){//сравниваем значение с битовой маской
        SER = 1;//записываем бит в регистр
    }
    else{
        SER = 0;//записываем бит в регистр
    }
    outt=(outt<<1);//сдвигаем байт на 1
    SRCLK = 1;
    __delay_us(1);
                }  
 RCLK = 1; 
 DIG1 = 1; 
__delay_ms(5);
                    if (u == 1){
                    outt = data;
                               }
            
                    if (u == 2){
                    outt = data2;
                               }

                    if (u == 0){
                    outt = data3;
                               }
DIG1 = 0;
 }
                   }    
}

