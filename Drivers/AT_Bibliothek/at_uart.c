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



	void test1( int argc, const char* argv[] );
	void test2( int argc, const char* argv[] );

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





int at_uart_interpreter(char* UART_Buffer) {

	/*ich glaube jetzt habe ich es verstanden
	 * wir definieren einen konstanten char zeiger auf arrays
	 * warum array? weil argv aus mehreren argumenten besteht erstes argument
	 * zweites argument etc.
	 *
	 * */
	 const char* argv[5];

	 //char * const argv[MAX_BUFFER];
	int   argc;

/* erstelle argc und argv */
	/* Kopiere string */
	/* konstanter char zeiger auf adresse 0 von uart_buffer*/
	const char* zeile = &UART_Buffer[0];

	argc = 0;
	char* Token = strtok( zeile, " " );

	while( Token != NULL && argc < MAX_BUFFER - 1) {
	    argv[argc++] = Token;
	    Token = strtok( NULL, " " );
	  }
	  argv[argc] = NULL;
	 // test1( argc, argv );
	test2( argc, argv );





	   //      memset(argv, 0, MAX_BUFFER);

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
	//while((result = strchr(result, target)) != NULL) {

	/* ermittle wo das '-' steht */
	//    LCD_INFO("Found '%c' starting at '%s'\n", target, result);
		//index = (int) (strlen(result) - strlen(kopie));
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


void test1( int argc, const char* argv[] )
{
  while( *argv != NULL ) {

    LCD_INFO( "*%s*\n", *argv );
    argv++;
  }
}

void test2( int argc,  const char* argv[] )
{
  //for( int i = 0; i < argc; ++i ) {
	//  LCD_INFO("argc:%d", argc);

	if( argv[1] != NULL ) {
  	  LCD_INFO( "*%s*\n", argv[1]);
	}
  //}
	  // LCD_INFO("Falsche Eingabe1");
	  // LCD_INFO("String: %s",*argv);

  int option = 0;
      int area = -1, perimeter = -1, breadth = -1, length =-1;

      //Specifying the expected options
      //The two options l and b expect numbers as argument


   while( *argv != NULL ) {
   	   LCD_INFO("Falsche Eingabe1");

      while ((option = getopt(argc, argv,"apl:b:")) != -1) {
   	   LCD_INFO("Falsche Eingabe2");

          switch (option) {
               case 'a' : area = 0;
                   break;
               case 'p' : perimeter = 0;
                   break;
               case 'l' : length = atoi(optarg);
                   break;
               case 'b' : breadth = atoi(optarg);
                   break;
               default:
            	   LCD_INFO("Falsche Eingabe3");
                  // exit(EXIT_FAILURE);
            	   break;
          }
      }
    argv++;
   }

      if (length == -1 || breadth ==-1) {

         // exit(EXIT_FAILURE);
      }

      // Calculate the area
      if (area == 0) {
          area = length * breadth;
          LCD_INFO("Area: %d\n",area);
      }

      // Calculate the perimeter
      if (perimeter == 0) {
          perimeter = 2 * (length + breadth);
          LCD_INFO("Perimeter: %d\n",perimeter);
      }

}













