/*
 *******************************************************************************
 * File:    at_uart.h
 * Author:  Armin Tirala
 * Version: V4.1
 * Date:    28.12.2017
 * IDE:     Eclipse Neon.3
 * Note:
 * Defines zu USART
 * headerfile braucht nicht veraendert werden.
 *******************************************************************************
 */

#ifndef AT_UART_H
#define AT_UART_H

#include "at_defines.h"
#include "stm32f4xx_hal.h"

extern uint8_t anschluss;
extern int at_uart_interpreter(const char* UART_Buffer);

#endif
