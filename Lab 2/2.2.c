/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 5/3/2020 17:32:55 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/

unsigned char cnt;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_s1, SM1_s2, SM1_s3, SM1_s4 } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_s1;
         break;
         case SM1_s1: 
         if (A0) {
            SM1_State = SM1_s2;
         }
         break;
      case SM1_s2: 
         if (A1) {
            SM1_State = SM1_s3;
         }
         break;
      case SM1_s3: 
         if (1) {
            SM1_State = SM1_s4;
         }
         break;
      case SM1_s4: 
         if (!A0 && !A1) {
            SM1_State = SM1_s1;
         }
         break;
      default:
         SM1_State = SM1_s1;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_s1:
         cnt = 0;
         break;
      case SM1_s2:
         cnt = cnt + 1;
         break;
      case SM1_s3:
         cnt = (360*3)/cnt;
         printf("Speed = %d kmph \n", cnt);
         B = (unsigned char) cnt;
         break;
      case SM1_s4:
         cnt = 0;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 100;
   TimerSet(periodState_machine_1);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_machine_1();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main