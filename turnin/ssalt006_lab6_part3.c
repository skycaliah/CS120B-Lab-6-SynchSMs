/*	Author: Skyler Saltos 
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	This lab has 4 leds connected to PORTB that light up its lower 4 binary value
 *	and is incremented or decremented by 2 buttons to a max value 9 and min value 0 
 *	through 2 puttons connected to PINA 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *
 *	https://youtu.be/Xbfk9y9W9lI
 *
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif




unsigned char i; // variable for incrementing and decrementing every 1000ms

enum SM2_States {SM2_Start, SM2_Increment, SM2_Decrement, SM2_ReadyButton, SM2_Reset, SM2_DecrementHold, SM2_IncrementHold } SM2_State;

void LEDCounter() {

	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;

   switch(SM2_State) { // Transitions
      case SM2_Start:
         PORTB = 0x07;
         SM2_State = SM2_ReadyButton;
         break;

         case SM2_Increment: 
         if (!A0 && !A1) {
            SM2_State = SM2_Reset;
         }
         else if (!A0 && A1) {
            SM2_State = SM2_IncrementHold;
            i = 0;
         }
         else if (A0 && A1) {
            SM2_State = SM2_ReadyButton;
         }
         break; 

      case SM2_Decrement: 
         if (!A0 && !A1) {
            SM2_State = SM2_Reset;
         }
         else if (A0 && A1) {
            SM2_State = SM2_ReadyButton;
         }
         else if (A0 && !A1) {
            SM2_State = SM2_DecrementHold;
            i = 0;
         }
         break;

      case SM2_ReadyButton: 
         if (A0 && A1) {
            SM2_State = SM2_ReadyButton;
         }
         else if (!A0 && A1) {
            SM2_State = SM2_Increment;
         }
         else if (A0 && !A1) {
            SM2_State = SM2_Decrement;
         }
         else if (!A0 && !A1) {
            SM2_State = SM2_Reset;
         }
         break;

      case SM2_Reset: 
         if (A0 && A1) {
            SM2_State = SM2_ReadyButton;
         }
         else {
            SM2_State = SM2_Reset;
         }
         break;

      case SM2_DecrementHold: 
         if (A0 && !A1) {
            SM2_State = SM2_DecrementHold;
         }
         else if (!A0 && !A1) {
            SM2_State = SM2_Reset;
         }
         else if (A0 && A1) {
            SM2_State = SM2_ReadyButton;
         }
         break;

      case SM2_IncrementHold: 
         if (!A0 && A1) {
            SM2_State = SM2_IncrementHold;
         }
         else if (!A0 && !A1) {
            SM2_State = SM2_Reset;
         }
         else if (A0 && A1) {
            SM2_State = SM2_ReadyButton;
         }
         break;

      default:
         SM2_State = SM2_Start;
   } // Transitions

   switch(SM2_State) { // State actions
      case SM2_Increment:
	 if( PORTB < 0x09){
	
		 PORTB = PORTB + 0x01;
	 }
         
         break;

      case SM2_Decrement:
	 if( PORTB > 0x00 ){
		 PORTB = PORTB - 0x01;
         }
         break;

      case SM2_ReadyButton:
         break;

      case SM2_Reset:
         PORTB = 0x00;
         break;

      case SM2_DecrementHold:
         if ( PORTB >= 0x01 &&  i ==10 ){
         PORTB = PORTB - 0x01;
         i = 0;
         }
         
         else if ( PORTB == 0x00){ 
          i = 0;
         }
         
         else{
         ++i;
         }
         
         break;

      case SM2_IncrementHold:
         if ( PORTB < 0x09 && i  ==  10 ){
         PORTB = PORTB + 0x01;
         i = 0;
         }
         
         else if ( PORTB >= 0x09){ 
          i = 0;
         }
         
         else{
         ++i;
         }
         
         break;

      default: // ADD default behaviour below
      break;
   } // State actions

}//end function for LEDCounter 




int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;

    DDRA = 0x00;
    PORTA = 0xFF;

    //set timer for 1 second
    TimerSet(100);
    TimerOn();

    /* Insert your solution below */

    SM2_State = SM2_Start; // initialize state for SM

    while (1) {
	LEDCounter(); // call synchSM

	while(!TimerFlag); // wait 100 ms before continuing
	TimerFlag = 0;

    }
    return 1;
}
