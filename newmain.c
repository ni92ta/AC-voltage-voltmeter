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
unsigned char intex;

//---------------------------Массив с цифрами-----------------------------------
unsigned char digit [11] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,//0, 1, 2, 3, 4,
0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b00000000//5, 6, 7, 8, 9  
};
//-------------------Обработчик внешнего прерывания INT-------------------------
void __interrupt() INT(void) 
{
    //RC2 = 1;
    
  if(INTF) {
  if (intex == 0){
    RC2 = 1;
    intex = 1;
  }    
  else{
   RC2 = 0; 
   intex = 0;
  }
  }
  INTF = 0;
}
//------------------------------------------------------------------------------
void main(void) {
    IOCA = 0b00000100;//включаем прерывание на RA2 ножка 11 
    INTCON = 0b10110000;//0b1xxxxxxx включаем глобальные прерывания,0bxx1xxxxx прерывание по переполнению таймера
    //0bxxx1xxxx и внешнее прерывание на RA2 11 ножка
    OPTION_REG |= (1<<INTEDG) | (1<<PS2) | (1<<PS1) | (1<<PS0);//прерывание на 
    //INT по переднему фронту; предделитель таймера на 256
    unsigned char l;
    unsigned char e = 0;
    unsigned char w = 0;
    unsigned char q = 0;
    PORTA = 0b00000000;
    TRISA = 0b00000110;
    PORTC = 0b00000000;
    TRISC = 0b00000000;
    ANSEL = 0b00000000;
    CM2 = 1;//включение /выключение компаратора
    CM1 = 1;
    CM0 = 1;

    RESie8 = 1;//сброс счётчика, высоким уровнем, при включении
    while (1){
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
            }
            
           senddata (digit [q], digit [w], digit [e]); 
                           }
    }
}
