/*
 *******************************************************************************
 * File:    at_uart.c
 * Author:  Armin Tirala
 * Version: V4.1
 * Date:    28.12.2017
 * IDE:     Eclipse Neon.3
 * Note:
 *******************************************************************************
 */

#include "at_uart.h"
#include "at_schrittmotor.h"
#include "at_defines.h"
#include "stdlib.h"
#include "stm32f4xx_hal.h"
#include "string.h"

void commands(int argc, char* argv[]);
void help(void);

/*
 *******************************************************************************
 * UART Interpreter
 *******************************************************************************
 */
int at_uart_interpreter(const char* UART_Buffer) {
   /*
    * ich glaube jetzt habe ich es verstanden
    * wir definieren einen konstanten char zeiger auf arrays
    * warum array? weil argv aus mehreren argumenten besteht erstes argument
    * zweites argument etc.
    */
   int argc = 0;
   int buffer_len = strlen(UART_Buffer) + 1;  // strlen(UART_Buffer)+1;
   char buf[buffer_len];
   const char* delimiter = " -";

   memcpy(buf, UART_Buffer, buffer_len);

   char* argv[10];
   char* token;

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
   uint8_t direction = 0;
   uint16_t speed = 0;
   uint8_t parameter = 0;
   uint32_t wert = 0;
   uint8_t n_step = 0;
   uint32_t pos = 0;

   while (*argv != NULL) {
      /*
       * Prüft ob String nur ein Zeichen lang ist, wenn ja handelt es sich
       * um einen Befehl. Um an das Zeichen zu kommen muss man zwei mal
       * dereferenzieren.
       * Abschließend wird per switch das Zeichen interpretiert
       *
       * Wichtig hierbei ist die Abfolge in Switch. Je nach Priorität
       * ist ein Befehl weiter oben, bzw. weiter unten eingetragen
       *
       * Das Delay in Case c ist dazu da, da sonst der nächste Befehl
       * nicht übernommen wird
       */

      if (strlen(*argv) == 1) {
         option = **argv;

         switch (option) {
            case 'h':
               help();
               break;

            case 'm':
               argv++;
               anschluss = atoi(*argv);
               break;

            case 'c':
               argv++;
               if (**argv == 'r') {
                  at_schrittmotor_param(LESEN, 0, 0);
               } else if (**argv == 'w') {
                  argv++;
                  parameter = atoi(*argv);
                  argv++;
                  wert = atoi(*argv);
                  at_schrittmotor_param(SCHREIBEN, parameter, wert);
                  HAL_Delay(50);
               } else if (**argv == '1') {
                  at_schrittmotor_param(CONFIG_1, 0, 0);
               } else if (**argv == '2') {
                  at_schrittmotor_param(CONFIG_2, 0, 0);
               } else if (**argv == '3') {
                  at_schrittmotor_param(CONFIG_3, 0, 0);
               } else if (**argv == '4') {
                  at_schrittmotor_param(CONFIG_4, 0, 0);
               }
               break;

            case 'a':
               at_schrittmotor_getstatus();
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

            case 's':
               argv++;
               if (**argv == 'h') {
                  at_schrittmotor_stop_hard();
               } else if (**argv == 's') {
                  at_schrittmotor_stop_soft();
               }
               break;

            case 'o':
               argv++;
               if (**argv == 'h') {
                  at_schrittmotor_off_hard();
               } else if (**argv == 's') {
                  at_schrittmotor_off_soft();
               }
               break;

            case 't':
               argv++;
               if (**argv == 'f') {
                  direction = FORWARD;
               } else if (**argv == 'r') {
                  direction = REVERSE;
               }
               at_schrittmotor_step(direction);
               break;

            case 'y':
               at_schrittmotor_reset();
               break;

            case 'z':
               at_schrittmotor_resetpos();
               break;

            case 'v':
               argv++;
               if (**argv == 'f') {
                  direction = FORWARD;
               } else if (**argv == 'r') {
                  direction = REVERSE;
               }
               argv++;
               n_step = atoi(*argv);

               at_schrittmotor_move(direction, n_step);
               break;

            case 'g':
               argv++;
               pos = atoi(*argv);
               at_schrittmotor_goto(pos);
               break;

            case 'd':
               argv++;
               if (**argv == 'f') {
                  direction = FORWARD;
               } else if (**argv == 'r') {
                  direction = REVERSE;
               }
               argv++;
               pos = atoi(*argv);
               at_schrittmotor_gotodir(direction, pos);
               break;

            case 'e':
               at_schrittmotor_gohome();
               break;

            case 'k':
               at_schrittmotor_gomark();
               break;

            default:
               //  LCD_INFO("Falsche Eingabe, Hilfe: -h");
               UART_INFO("Falsche Eingabe, Hilfe: -h");
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
   UART_INFO("-h\tHilfe");
   UART_INFO("-m\tModul\t<1-8>");
   UART_INFO("-c\tConfig\t<r,w,1,2> <n> <wert>");
   UART_INFO("-a\tGet Status");
   UART_INFO("-r\tRun\t<f,r> <speed>");
   UART_INFO("-s\tStop\t<h,s>");
   UART_INFO("-o\tOff\t<h,s>");
   UART_INFO("-t\tStep\t<f,r>");
   UART_INFO("-y\tReset Motor");
   UART_INFO("-z\tReset Position");
   UART_INFO("-v\tMove\t<f,r> <step>");
   UART_INFO("-g\tGoTo\t<position>");
   UART_INFO("-d\tGoTo Dir\t<f,r> <position>");
   UART_INFO("-e\tGo Home");
   UART_INFO("-k\tGo Mark");
   // UART_INFO("-u\tGo Until");
   // UART_INFO("-w\tRelease Switch");
   UART_INFO("\n");

   UART_INFO("\nModul: -m");
   UART_INFO("Einstellen des Moduls 1-8 (Bezeichnung auf PCB)");
   UART_INFO("Bsp.: Aktivieren des Moduls 7: \"-m 7\"");

   UART_INFO("\nSchrittmotorkonfiguration: -c");
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
   UART_INFO("Bsp.: Aenderung der Thresholdspannung: \"-c w 19 750\"");
   UART_INFO("\nVoreingestellte Konfigurationen:");
   UART_INFO("1:L3518 (Schrittmotor mit Gewindestange)");
   UART_INFO("2:LSP1518 (kleiner Schrittmotor)");
   UART_INFO("3:SY57STH41 (grosser Schrittmotor)");
   UART_INFO("4:17H130H (doppelseitig");
   UART_INFO("\nRun: -r");
   UART_INFO("Schrittmotor in eine konstante Bewegung zu setzen");
   UART_INFO("Bsp.: Rueckwaerts mit einem Wert von 30: \"-r r 30\"");

   UART_INFO("\nStop: -s");
   UART_INFO("Stoppen des Motors bei aktiver Thresholdspannung");
   UART_INFO("Das Stoppen des Motors erfolg \"Soft\" --> siehe Datenblatt");
   UART_INFO("Bsp.: \"-s\"");

   UART_INFO("\n Off: -o");
   UART_INFO("Ausschalten der H-Bruecke --> Schrittmotor spannungslos");
   UART_INFO("Bsp.: \"-o\"");
}
