#include "at_uart.h"
#include "defines.h"
#include "stm32f4xx_hal.h"
#include "string.h"
#include "tm_stm32_fonts.h"
#include "tm_stm32_lcd.h"
#include "tm_stm32_usart.h"
#include "tm_stm32f4_stmpe811.h"
#include "unistd.h"

#include "stdint.h"

void test1(int argc, const char* argv[]);
void commands(int argc, char* argv[]);

/*
 *******************************************************************************
 * UART Testfunktion
 *******************************************************************************
 */
void uart_test(void) {
   char str[30];
   char mybuffer[100];
   uint16_t uarttest = 666;

   TM_USART_Puts(USART1, "Hello world\n");

   if (TM_USART_Gets(USART1, mybuffer, sizeof(mybuffer))) {
      /* Send string back */
      TM_USART_Puts(USART1, mybuffer);
   }
   // sprintf(str, "UART    \n\nX: %d",  uarttest);

   TM_LCD_SetXY(60, 160);
   TM_LCD_Puts(str);
}

/*
 *******************************************************************************
 * UART Interpreter / Parser
 *******************************************************************************
 */

/*
 * -m<int>   		 Modul 1-8
 * -p<char> 	     Parameter r:read, w:write, 1:mem1, 2:mem2
 * -r<char>=<int> 	 Run f,r = 200
 * -s				 Stop
 *
 *
 *


*/

int at_uart_interpreter(const char* UART_Buffer) {
   /*ich glaube jetzt habe ich es verstanden
    * wir definieren einen konstanten char zeiger auf arrays
    * warum array? weil argv aus mehreren argumenten besteht erstes argument
    * zweites argument etc.
    *
    * */
   int i = 0;
   int argc = 0;
   int buffer_len = strlen(UART_Buffer) + 1;  // strlen(UART_Buffer)+1;
   char buf[buffer_len];
   const char* delimiter = " -";

   memcpy(buf, UART_Buffer, buffer_len);

   char* argv[10];
   const char* token;

   // LCD_INFO("ARRAY START &argv:%d, argv:%d, *argv:%d", &argv[0], argv[0],
   // *argv[0]);

   /* erstelle argc und argv */
   /* Kopiere string */
   /* konstanter char zeiger auf adresse 0 von uart_buffer*/
   // zeile = &UART_Buffer[0];
   /* Lösche Scheiß raus */
   //	while (buf[i] < 0x20 || 0x7A > buf[i] ) {
   //		buf[i] = NULL;
   //		i++;
   //	}

   token = strtok(buf, delimiter);

   while (token != NULL && argc < 10 - 1) {
      /* das depperte argv ist also auch nur eine pointerverlinkung?*/
      /* dem argv  wird also immer die nächste adresse nach einem leerzeichen
       * gegeben*/
      argv[argc++] = token;
      token = strtok(NULL, delimiter);
      //  LCD_INFO("argv &:%d, a:%d, *:%d", &argv[argc], argv[argc],
      //  *argv[argc]);
   }
   argv[argc] = NULL;
   // test1( argc, argv );
   commands(argc, argv);

   return 0;

   /*
            result=strchr(str,'-');
             while (result!=NULL)
             {
               LCD_INFO("found at %d\n",result-str+1);
               result=strchr(result+1,'-');
             }
   */
   /* suche den ganzen string nach '-' ab */
   // while((result = strchr(result, target)) != NULL) {

   /* ermittle wo das '-' steht */
   //    LCD_INFO("Found '%c' starting at '%s'\n", target, result);
   // index = (int) (strlen(result) - strlen(kopie));
   //  ++result;

   //	switch(UART_Buffer[index + 1]) {

   //	}
   //	}

   //
   //   if (strncmp(UART_Buffer, "on", 2) == 0) {
   //      at_schrittmotor_test();
   //   }
   //
   //   if (strncmp(UART_Buffer, "off", 3) == 0) {
   //      at_schrittmotor_stop();
   //   }
}
/*
int at_uart_interpreter(uint8_t *UART_Buffer){


if (UART_Buffer[0] != '-' || UART_Buffer[1]!='m') {
        UART_ERROR();
        return 1;
}

//bitte mit zeiger machen...
anschluss = (uint8_t)UART_Buffer[2];//achtung nicht das das als Char
interpretiert wird

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


           if (strcmp(UART_Buffer, "on") == 0) {
                   at_schrittmotor_run();
               }

           if (strcmp(UART_Buffer, "off") == 0) {
                   at_schrittmotor_stop();
               }







void UART_ERROR(void) {



}

*/

void commands(int argc, char* argv[]) {
   char option = 0;
   int direction = 0;
   int speed = 0;

   while (*argv != NULL) {
      /*
       * Prüft ob String nur ein Zeichen lang ist, wenn ja handelt es sich
       * um einen Befehl. Um an das Zeichen zu kommen muss man zwei mal
       * dereferenzieren.
       * Abschließend wird per switch das Zeichen interpretiert
       */

      if (strlen(*argv) == 1) {
         option = **argv;

         switch (option) {
            case 'm':
               argv++;
               anschluss = atoi(*argv);
               break;
            case 'r':
               argv++;
               if (**argv == 'f') {
                  direction = 1;
               } else {
                  direction = 0;
               }
               argv++;
               speed = atoi(*argv);
               at_schrittmotor_run(direction, speed);
               break;
            case 's':
               at_schrittmotor_stop();
               break;
            case 'c':
               argv++;
               if (**argv == 'r') {
                  at_schrittmotor_param(LESEN);
               } else if (**argv == 'w') {
                  at_schrittmotor_param(SCHREIBEN);
               } else if (**argv == '1') {
                  at_schrittmotor_param(99);
               } else if (**argv == '2') {
                  at_schrittmotor_param(98);
               }
               break;
            default:
               LCD_INFO("Falsche Eingabe");
               // exit(EXIT_FAILURE);
               break;
         }
      }
      argv++;
   }
}
