/*	Author: Skyler Saltos 
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	This lab has three LEDs blinking in sequence and the user presses
 *	a button to stop the LED in the middle and then press the button again
 *	to continue the game. 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *
 *	https://youtu.be/LFuM4lQRtp0
 *
 *
 *
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_States {SM_Start,SM_Light0, SM_Light1to2, SM_Light2, SM_ButtonPressed, SM_WaitNext, SM_Light1to0 } SM_State;

void ThreeBlinkGame(){

	unsigned char A0 = PINA & 0x01; //isolate PA0 into variable for use in function

   switch(SM_State) { // Transitions
      case SM_Start:
         PORTB = 0;
         SM_State = SM_Light0;
         break;

         case SM_Light0: 
         if (A0) {
            SM_State = SM_Light1to2;
         }
         else if (!A0) {
            SM_State = SM_ButtonPressed;
         }
         break;

      case SM_Light1to2: 
         if (A0) {
            SM_State = SM_Light2;
         }
         else if (!A0) {
            SM_State = SM_ButtonPressed;
         }
         break;

      case SM_Light2: 
         if (!A0) {
            SM_State = SM_ButtonPressed;
         }
         else if (A0) {
            SM_State = SM_Light1to0;
         }
         break;

      case SM_ButtonPressed: 
         if (!A0) {
            SM_State = SM_ButtonPressed;
         }
         else if (A0) {
            SM_State = SM_WaitNext;
         }
         break;

      case SM_WaitNext: 
         if (A0) {
            SM_State = SM_WaitNext;
         }
         else if (!A0) {
            SM_State = SM_Light0;
         }
         break;

      case SM_Light1to0: 
         if (A0) {
            SM_State = SM_Light0;
         }
         else if (!A0) {
            SM_State = SM_ButtonPressed;
         }
         break;

      default:
         SM_State = SM_Start;
   } // Transitions

   switch(SM_State) { // State actions
      case SM_Light0:
         PORTB = 0x01;
         break;

      case SM_Light1to2:
         PORTB = 0x02;
         break;

      case SM_Light2:
         PORTB = 0x04;
         break;

      case SM_ButtonPressed:
         break;

      case SM_WaitNext:
         break;

      case SM_Light1to0:
         PORTB = 0x02;
         break;

      default: 
      break;
   } // State actions

}
	 





int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;

    DDRA = 0x00;
    PORTA = 0xFF;

    //set timer for 1 second
    TimerSet(300);
    TimerOn();

    /* Insert your solution below */

    SM_State = SM_Start; // initialize state for SM

    while (1) {
	ThreeBlinkGame(); // call synchSM

	while(!TimerFlag); // wait 300 ms before continuing
	TimerFlag = 0;

    }
    return 1;
}
