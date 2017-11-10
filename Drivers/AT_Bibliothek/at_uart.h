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

extern uint8_t anschluss;

extern void uart_test(void);
extern int at_uart_interpreter(const char* UART_Buffer);

#endif
