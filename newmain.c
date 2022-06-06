/*
 * File:   newmain.c
 * Author: Никита
 *
 * Created on 11 мая 2022 г., 19:04
 */

 
#define _XTAL_FREQ 2000000
#include <xc.h>
#include "newfile.h"
#include "hc595.h"
#include "stdio.h"


//#define DIG2 RC1// вывод данных
//#define DIG3 RC2// вывод данных
#define RESie8 RC1// сброс ИЕ8

unsigned char adc_data_raw;//переменная для хранения результата измерений АЦП
unsigned int ch;
unsigned char adc_data;
unsigned char adc_data1;
unsigned char adc_data2;
unsigned char adc_data3;
//---------------------------Массив с цифрами-----------------------------------
unsigned char digit [11] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 
0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 
0b00000000    
};
//-------------------------Обработчик прерываний--------------------------------
void __interrupt() timer0(void)
{
    if (TMR0IF) {//Флаг переполнения таймера0
         RC2=1;
        __delay_us(200);
        RC2=0;

        
        TMR0IF=0;//сброс флага прерывания таймера0       
}
if(INTF) {//флаг переполнения внешнего прерывания INT
T0IE=1;//запускаем таймер   
TMR0 = 0b00010100;//устанавливаем начальное значение таймера (20)
INTF = 0;//сброс флага прерывания INT
}
}
//------------------------------------------------------------------------------
void main(void) {
    IOCA = 0b00000100;//0bxxxxx1xx включаем прерывание по INT (ножка 11) 
    INTCON = 0b00010000;//0b1xxxxxxx включаем глобальные прерывания,
    //0bxx1xxxxx прерывание по переполнению таймера0
    //0bxxx1xxxx и внешнее прерывание на RA2 11 ножка
    OPTION_REG = 0b00000101;//0bx1xxxxxx прерывание на 
    //INT по спадающему фронту; предделитель таймера на 64
    
    //unsigned char l;
    //unsigned char e = 0;
    //unsigned char w = 0;
    //unsigned char q = 0;
    
    PORTA = 0b00000000;
    TRISA = 0b00000101;//входы RA0, RA2 ножки 13, 11
    PORTC = 0b00000000;
    TRISC = 0b00000000;
    //WPUA = 0b00000010;//подтяжка к плюсу

     ADFM = 0;//выравнивание результата АЦП 0 - по левому краю
     VCFG = 0;//опорное 1 - Vref; 0- Vdd 
ADCS2 = 1;//частота преобразования АЦП Fosc/16
ADCS1 = 1;//частота преобразования АЦП Fosc/16
ADCS0 = 0;// -//-
ADON = 1;//включить модуль АЦП 
    ANSEL = 0b00000001;//включаем аналоговый вход на ножке RA0 13 ножка

   // CM2 = 1;//включение /выключение компаратора
   // CM1 = 1;
  //  CM0 = 1;
    RESie8 = 1;//сброс счётчика CD4017
    while (1){
       //__delay_ms(1);
        RESie8 = 0;//разрешение счёта счётчика CD4017
        GO=1;//запуск АЦП
        __delay_us(15);//пауза для стабилизации АЦП
        //adc_data_raw = (unsigned int)ADRESH;//считываем значение регистра АЦП
CHS2 = 0;//канал измерения напряжения RA0 pin13
CHS1 = 0;//канал измерения напряжения RA0 pin13
CHS0 = 0;//канал измерения напряжения RA0 pin13 
adc_data_raw = (unsigned int)ADRESL;//считываем значение регистра АЦП
adc_data_raw = (unsigned int)ADRESH;//считываем значение регистра АЦП
ch =(unsigned int) ((adc_data_raw*2));
// adc_data =((unsigned char)(ch));//(ch/100)
// adc_data1 =((unsigned char)((ch)%10));//((ch/10)%10))
 adc_data2 =((unsigned char)((ch/10)%10));//(ch%10)
 senddata (digit [1], digit [1], digit [1]);//вывод
 //значения на LED индикатор 
 //__delay_ms(500);
    }
}
