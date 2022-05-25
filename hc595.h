/* 
 * File:   hc595.h
 * Author: Никита
 *
 * Created on 25 мая 2022 г., 18:34
 */
#include <xc.h>
#define _XTAL_FREQ 4000000

#define SER RC5// данные
#define SRCLK RC4// загрузка битов 
#define RCLK RC3// вывод данных

#define DIG1 RC0// вывод данных

#ifndef HC595_H
#define	HC595_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
void senddata (unsigned char data, unsigned char data2, unsigned char data3);
#endif	/* HC595_H */

