/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 5/21/2020 17:49:8 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/

unsigned char H, L;
unsigned char i;
unsigned char SM2_Clk;
void TimerISR() {
   SM2_Clk = 1;
}

enum SM2_States { SM2_Init, SM2_s2, SM2_s3 } SM2_State;

TickFct_PWM() {
   switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_Init;
         break;
         case SM2_Init: 
         if (1) {
            SM2_State = SM2_s2;
            i=0;
         }
         break;
      case SM2_s2: 
         if (!(i<H)) {
            SM2_State = SM2_s3;
            i=0;
         }
         else if (i < H) {
            SM2_State = SM2_s2;
         }
         break;
      case SM2_s3: 
         if (i < L) {
            SM2_State = SM2_s3;
         }
         else if (!(i<L)) {
            SM2_State = SM2_s2;
            i = 0;
         }
         break;
      default:
         SM2_State = SM2_Init;
   } // Transitions

   switch(SM2_State) { // State actions
      case SM2_Init:
         B0 = 0;
         L=10;
         H=4;
         
         
         break;
      case SM2_s2:
         B0 = 1;
         i++;
         
         break;
      case SM2_s3:
         B0 = 0;
         i++;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodPWM = 2000;
   TimerSet(periodPWM);
   TimerOn();
   
   SM2_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_PWM();
      while(!SM2_Clk);
      SM2_Clk = 0;
   } // while (1)
} // Main