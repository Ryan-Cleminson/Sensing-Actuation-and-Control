/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 5/3/2020 16:51:54 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/

short cnt;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_s1, SM1_s2, SM1_s3, SM1_s4, SM1_s5, SM1_s6, SM1_s7, SM1_s8, SM1_s9 } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         cnt = 9;
         SM1_State = SM1_s8;
         break;
         case SM1_s1: 
         if (A < 81 && A >60) {
            SM1_State = SM1_s2;
         }
         else if (A == 0) {
            SM1_State = SM1_s6;
         }
         else if (A < 21 && A > 0) {
            SM1_State = SM1_s5;
         }
         else if (A< 61 && A > 40) {
            SM1_State = SM1_s3;
         }
         else if (A < 41 && A >20) {
            SM1_State = SM1_s4;
         }
         else if (A <= 100 && A > 80) {
            SM1_State = SM1_s7;
         }
         break;
      case SM1_s2: 
         if (1) {
            SM1_State = SM1_s8;
         }
         break;
      case SM1_s3: 
         if (1) {
            SM1_State = SM1_s8;
         }
         break;
      case SM1_s4: 
         if (1) {
            SM1_State = SM1_s8;
         }
         break;
      case SM1_s5: 
         if (1) {
            SM1_State = SM1_s8;
         }
         break;
      case SM1_s6: 
         if (1) {
            SM1_State = SM1_s8;
         }
         break;
      case SM1_s7: 
         if (1) {
            SM1_State = SM1_s8;
         }
         break;
      case SM1_s8: 
         if (cnt  == 10) {
            SM1_State = SM1_s1;
         }
         break;
      case SM1_s9: 
         break;
      default:
         SM1_State = SM1_s8;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_s1:
         cnt = 0;
         break;
      case SM1_s2:
         B = 0x1E;
         break;
      case SM1_s3:
         B = 0x1C;
         break;
      case SM1_s4:
         B = 0x18;
         break;
      case SM1_s5:
         B = 0x90;
         break;
      case SM1_s6:
         B = 0x80;
         break;
      case SM1_s7:
         B = 0x1F;
         break;
      case SM1_s8:
         cnt = cnt + 1;
         break;
      case SM1_s9:
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 1000; // 1000 ms default
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