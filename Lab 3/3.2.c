/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 5/12/2020 15:40:59 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/

unsigned char btn_g;
const unsigned char seq[3] = {5, 4, 3};
unsigned char i;
unsigned char btn;

unsigned char DB_GetBtn(){

    switch((A&0x3E)>>1){
        case 0x00: btn=0; break;
        case 0x01: btn=1; break;
        case 0x02: btn=2; break;
        case 0x04: btn=3; break;
        case 0x08: btn=4; break;
        case 0x10: btn=5; break;
        default: btn = 0; break;
    }
    return btn;
}
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum DB_States { DB_s0 } DB_State;

TickFct_DetectButton() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(DB_State) { // Transitions
      case -1:
         DB_State = DB_s0;
         break;
      case DB_s0:
         if (1) {
            DB_State = DB_s0;
         }
         break;
      default:
         DB_State = DB_s0;
      } // Transitions

   switch(DB_State) { // State actions
      case DB_s0:
         btn_g = DB_GetBtn();
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum DS_States { DS_Init, DS_Start, DS_Wait, DS_Match, DS_Check, DS_Fail } DS_State;

TickFct_DetectSequence() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/

   switch(DS_State) { // Transitions
      case -1:
         DS_State = DS_Init;
         break;
      case DS_Init:
         if (1) {
            DS_State = DS_Start;
         }
         break;
      case DS_Start:
         if (btn_g == 0) {
            DS_State = DS_Wait;
         }
         break;
      case DS_Wait:
         if (btn_g == 0) {
            DS_State = DS_Wait;
         }
         else if (!(btn_g == 0)) {
            DS_State = DS_Check;
         }
         break;
      case DS_Match:
         if (((btn_g)==0) && !(i==2)) {
            DS_State = DS_Wait;
            i++;
         }
         else if ((btn_g == 0) && (i==2)) {
            DS_State = DS_Start;
            B1=!B1;
         }
         else if (!(btn_g == 0)) {
            DS_State = DS_Match;
         }
         break;
      case DS_Check:
         if (btn==seq[i]) {
            DS_State = DS_Match;
         }
         else {
            DS_State = DS_Fail;
         }
         break;
      case DS_Fail:
         if (btn_g == 0) {
            DS_State = DS_Start;
         }
         else if (!(btn_g == 0)) {
            DS_State = DS_Fail;
         }
         break;
      default:
         DS_State = DS_Init;
      } // Transitions

   switch(DS_State) { // State actions
      case DS_Init:
         B1 = 0;
         break;
      case DS_Start:
         i=0;
         break;
      case DS_Wait:
         break;
      case DS_Match:
         printf("btn %d seq %d", btn, seq[i]);
         break;
      case DS_Check:
         break;
      case DS_Fail:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}
int main() {
   B = 0; //Init outputs
   TimerSet(100);
   TimerOn();
   DB_State = -1;
   DS_State = -1;
   while(1) {
      TickFct_DetectButton();
      TickFct_DetectSequence();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}