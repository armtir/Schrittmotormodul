#include "at_uart.h"
#include "defines.h"
#include "stm32f4xx_hal.h"
#include "tm_stm32_lcd.h"
#include "tm_stm32_fonts.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32_usart.h"
#include "string.h"

#include "stdint.h"


void uart_test(void){
	char str[30];
	char mybuffer[100];
	uint16_t uarttest=666;

	TM_USART_Puts(USART1,"Hello world\n");


	if (TM_USART_Gets(USART1, mybuffer, sizeof(mybuffer))) {
		/* Send string back */
		TM_USART_Puts(USART1, mybuffer);
		}
	//sprintf(str, "UART    \n\nX: %d",  uarttest);

	TM_LCD_SetXY(60, 160);	
	TM_LCD_Puts(str);
			
		}


int at_uart_interpreter(uint8_t *UART_Buffer){


if (UART_Buffer[0] != '-' || UART_Buffer[1]!='m') {
	UART_ERROR();
	return 1;
}

//bitte mit zeiger machen...
anschluss = (unit8_t)UART_Buffer[2];//achtung nicht das das als Char interpretiert wird

// Befehle
	  switch(LCD_INFO(UART_Buffer[5])

	case 'p':
	    if(UART_Buffer[6]=='r'){
	    //Print config
	    }
	    if(UART_Buffer[6]=='w'){
	    //write config
	    //und initialisieren
	    }
	    else{
	    //vorprogrammiertes hernehmen
	    //und initialisieren
	    }


	   if (strcmp(UART_Buffer, "o") == 0) {
		   at_schrittmotor_run();
	       }

	   if (strcmp(UART_Buffer, "off") == 0) {
		   at_schrittmotor_stop();
	       }







void UART_ERROR(void) {



}
