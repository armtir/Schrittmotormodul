#include "at_uart.h"
#include "defines.h"
#include "stm32f4xx_hal.h"
#include "string.h"
#include "tm_stm32_fonts.h"
#include "tm_stm32_lcd.h"
#include "tm_stm32_usart.h"
#include "tm_stm32f4_stmpe811.h"
//#include "unistd.h"

#include "stdint.h"

void commands(int argc, char* argv[]);
void help(void);

/*
 *******************************************************************************
 * UART Interpreter
 *******************************************************************************
 */

/*
 * -m <int>            Modul 1-8
 * -c <char>           Parameter r:read, w:write, 1:mem1, 2:mem2
 * -r <char> <int>     Run f:forward, r:return, speed
 * -s                  Stop
 * -o                  Off
 * -h                  Help
 *
 *


*/

int at_uart_interpreter(const char* UART_Buffer) {
   /*
    * ich glaube jetzt habe ich es verstanden
    * wir definieren einen konstanten char zeiger auf arrays
    * warum array? weil argv aus mehreren argumenten besteht erstes argument
    * zweites argument etc.
    */
   int i = 0;
   int argc = 0;
   int buffer_len = strlen(UART_Buffer) + 1;  // strlen(UART_Buffer)+1;
   char buf[buffer_len];
   const char* delimiter = " -";

   memcpy(buf, UART_Buffer, buffer_len);

   char* argv[10];
   const char* token;

   token = strtok(buf, delimiter);

   while (token != NULL && argc < 10 - 1) {
      /*
       * das depperte argv ist also auch nur eine pointerverlinkung?
       * dem argv  wird also immer die nächste adresse nach einem leerzeichen
       * gegeben
       */
      argv[argc++] = token;
      token = strtok(NULL, delimiter);
   }
   argv[argc] = NULL;

   commands(argc, argv);

   return 0;
}

/*
 *******************************************************************************
 * Verarbeitung der eingehenden Befehle
 *******************************************************************************
 */
void commands(int argc, char* argv[]) {
   char option = 0;
   int direction = 0;
   int speed = 0;
   int parameter = 0;
   int wert = 0;

   while (*argv != NULL) {
      /*
       * Prüft ob String nur ein Zeichen lang ist, wenn ja handelt es sich
       * um einen Befehl. Um an das Zeichen zu kommen muss man zwei mal
       * dereferenzieren.
       * Abschließend wird per switch das Zeichen interpretiert
       *
       * Wichtig hierbei ist die Abfolge in Switch. Je nach Priorität
       * ist ein Befehl weiter oben, bzw. weiter unten eingetragen
       */

      if (strlen(*argv) == 1) {
         option = **argv;

         switch (option) {
            case 'm':
               argv++;
               anschluss = atoi(*argv);
               break;

            case 'o':
               at_schrittmotor_off();
               break;

            case 's':
               at_schrittmotor_stop();
               break;

            case 'c':
               argv++;
               if (**argv == 'r') {
                  at_schrittmotor_param(LESEN,0,0);
               } else if (**argv == 'w') {
                  argv++;
                  parameter = atoi(*argv);
                  argv++;
                  wert = atoi(*argv);
                  at_schrittmotor_param(SCHREIBEN, parameter, wert);
               } else if (**argv == '1') {
                  at_schrittmotor_param(CONFIG_1,0,0);
               } else if (**argv == '2') {
                  at_schrittmotor_param(CONFIG_2,0,0);
               }
               break;

            case 'r':
               argv++;
               if (**argv == 'f') {
                  direction = FORWARD;
               } else if (**argv == 'r') {
                  direction = REVERSE;
               }
               argv++;
               speed = atoi(*argv);
               at_schrittmotor_run(direction, speed);
               break;

            case 'h':
               help();
               break;

            default:
               LCD_INFO("Falsche Eingabe, Hilfe: -h");
               TM_USART_Puts(USART1, "Falsche Eingabe, Hilfe: -h\n");
               break;
         }
      }
      argv++;
   }
}

/*
 *******************************************************************************
 * UART Hilfe Ausgabe
 *******************************************************************************
 */
void help(void) {
   UART_INFO("Hilfe:\n");
   UART_INFO("Kommandos:");
   UART_INFO("-m\tModul\t-m <1-8>");
   UART_INFO("-c\tConfig\t-c <r,w,1,2> <n> <wert>");
   UART_INFO("-r\tRun\t-r <f,r> <speed>");
   UART_INFO("-s\tStop");
   UART_INFO("-o\tOff");
   UART_INFO("\n\n");


   UART_INFO("Schrittmotorkonfiguration (-c)");
   UART_INFO("n   Type       Range Unit");
   UART_INFO("1 : ABS_POS     <int>");
   UART_INFO("2 : EL_POS:     <int>");
   UART_INFO("3 : MARK:       <int>");
   UART_INFO("5 : ACC:        <15-59590>steps/s");
   UART_INFO("6 : DEC:        <15-59590>steps/s");
   UART_INFO("7 : MAX_SPEED:  <15-15610>steps/s");
   UART_INFO("8 : MIN_SPEED:  <15-15610>steps/s");
   UART_INFO("21: FS_SPD:     <7-15625>steps/s");
   UART_INFO("9 : TVAL_HOLD:  <31-4000>mA");
   UART_INFO("10: TVAL_RUN:   <31-4000>mA");
   UART_INFO("11: TVAL_ACC:   <31-4000>mA");
   UART_INFO("12: TVAL_DEC:   <31-4000>mA");
   UART_INFO("14: T_FAST:     <2^n-32>us");
   UART_INFO("15: TON_MIN:    <1-64>us");
   UART_INFO("16: TOFF_MIN:   <1-64>us");
   UART_INFO("19: OCD_TH:     <375^n-6000>mA");
   UART_INFO("22: STEP_MODE:  <1,2,4,8,16>");
   UART_INFO("23: ALARM_EN:   <Binary>");
   UART_INFO("24: CONFIG:     <Binary>");





}

/*
 *******************************************************************************
 * UART Testfunktion (to be deleted)
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
