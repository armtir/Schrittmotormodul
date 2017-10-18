/**
 ******************************************************************************
 * @file    at_uart.h
 * @author  Armin Tirala
 * @version V1.0
 * @date    16.05.2017
 * @brief   Schrittmotorsteuerung
 * @note    Defines zu USART
 * headerfile braucht nicht ver�ndert werden.
 ******************************************************************************
 */

#ifndef _USE_LCD_H
#define _USE_LCD_H

#include "defines.h"
#include "stm32f4xx_hal.h"

extern void uart_test(void);
extern void at_uart_interpreter(uint8_t *UART_Buffer);

#endif
