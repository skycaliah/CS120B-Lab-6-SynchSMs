/*	Author: Skyler Saltos 
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	This lab blinks three LEDS starting at PB0,PB1,PB2 on a 1 second time interval. 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *
 * https://youtu.be/ckV6HlE7HQk
 *
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


	 


enum SM_States { SM_Start, SM_Light0, SM_Light1, SM_Light2 } SM_State;

void LightBlinkSM() {
   switch(SM_State) { // Transitions
      case SM_Start:
         PORTB = 0;
         SM_State = SM_Light0;
         break;

         case SM_Light0: 
            SM_State = SM_Light1;
         break;

      case SM_Light1: 
            SM_State = SM_Light2;
         break;

      case SM_Light2: 
            SM_State = SM_Light0;
         break;

      default:
         SM_State = SM_Start;
	 break;
   } // Transitions

   switch(SM_State) { // State actions
      case SM_Light0:
        PORTB = 0x01;
         break;

      case SM_Light1:
         PORTB = 0x02;
         break;

      case SM_Light2:
         PORTB = 0x04;
         break;

      default:
      break;

   } // State actions

}





int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;

    //set timer for 1 second
    TimerSet(1000);
    TimerOn();

    /* Insert your solution below */

    SM_State = SM_Start; // initialize state for SM

    while (1) {
	LightBlinkSM(); // call synchSM

	while(!TimerFlag); // wait 1 sec before continuing
	TimerFlag = 0;

    }
    return 1;
}
