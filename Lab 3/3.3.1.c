/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 5/16/2020 17:31:21 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/

unsigned char key_g; 
unsigned char period_g; 
unsigned char i; 
unsigned char H; 
unsigned char cnt;
unsigned char L; 
unsigned char X;


unsigned char getKey(){
    if (A7 == 1) {
        return 8;
    }
    else if (A6 == 1) {
        return 7;
    }
    else if (A5 == 1) {
        return 6;
    }
    else if (A4 == 1) {
        return 5;
    }
    else if (A3 == 1) {
        return 4;  
    }
    else if (A2 == 1) {
        return 3;
    }
    else if (A1 == 1) {
        return 2;
    }
    else if (A0 == 1) {
        return 1;
    }
    else if (A == 0) {
        return 0;
    }
}

unsigned char getPeriod(){
    unsigned char period;
    if (A7 == 1) {
        period = 61/20;
        return period;
    }
    else if (A6 == 1) {
        period = 54/20;
        return period;
    }
    else if (A5 == 1) {
        period = 49/20;
        return period;
    }
    else if (A4 == 1) {
        period = 46/20;
        return period;
    }
    else if (A3 == 1) {
        period = 41/20;
        return period;
    }
    else if (A2 == 1) {
        period = 36/20;
        return period;
    }
    else if (A1 == 1) {
        period = 32/20;
        return period;
    }
    else if (A0 == 1) {
        period = 31/20;
        return period;
    }
    else if (A == 0) {
        period = 0;
        return period;
    }
}
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM1_States { SM1_Init } SM1_State;

TickFct_State_machine_1() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(SM1_State) { // Transitions
      case -1:
         key_g = 0;
         SM1_State = SM1_Init;
         break;
      case SM1_Init:
         break;
      default:
         SM1_State = SM1_Init;
      } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Init:
         key_g = getKey();
         period_g = getPeriod(); 
         X = 20 - key_g;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM2_States { SM2_Init, SM2_s2, SM2_s3 } SM2_State;

TickFct_State_machine_2() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/


   switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_Init;
         break;
      case SM2_Init:
         if (period_g > 0) {
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
         else if (cnt > period_g) {
            SM2_State = SM2_Init;
         }
         break;
      case SM2_s3:
         if (i < L) {
            SM2_State = SM2_s3;
         }
         else if ((!(i<L)) && (cnt< period_g)) {
            SM2_State = SM2_s2;
            i = 0;
         }
         else if (cnt >= period_g) {
            SM2_State = SM2_Init;
         }
         break;
      default:
         SM2_State = SM2_Init;
      } // Transitions

   switch(SM2_State) { // State actions
      case SM2_Init:
         B0 = 0;
         L=H=X/2;
         cnt = 0;
         
         break;
      case SM2_s2:
         B0 = 1;
         i++;
         printf(" %d", H);
         if(cnt< period_g){
             cnt ++;
         }
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
   B = 0; //Init outputs
   TimerSet(20);
   TimerOn();
   SM1_State = -1;
   SM2_State = -1;
   while(1) {
      TickFct_State_machine_1();
      TickFct_State_machine_2();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}