/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 5/7/2020 16:11:0 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/

unsigned char mtn;

int Duration(A1, A2, A3) {

 

    unsigned char duration;
    if (A1) {
        duration = 25;
    }
    if (A2) {
        duration = 50;
    }
    if (A3) {
        duration = 75;
    }
    else {
        duration = 15;
    }

 

    return duration;

 

}
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum DM1_States { DM1_s1, DM1_s2, DM1_s3 } DM1_State;

TickFct_DetectMotion() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/


   switch(DM1_State) { // Transitions
      case -1:
         DM1_State = DM1_s1;
         break;
      case DM1_s1:
         if (!A0) {
            DM1_State = DM1_s1;
         }
         else if (A0) {
            DM1_State = DM1_s3;
         }
         break;
      case DM1_s2:
         if (A0) {
            DM1_State = DM1_s2;
         }
         else if (!A0) {
            DM1_State = DM1_s1;
         }
         break;
      case DM1_s3:
         if (!A0) {
            DM1_State = DM1_s1;
         }
         else if (A0) {
            DM1_State = DM1_s2;
         }
         break;
      default:
         DM1_State = DM1_s1;
      } // Transitions

   switch(DM1_State) { // State actions
      case DM1_s1:
         mtn =0;
         break;
      case DM1_s2:
         mtn = 1;
         break;
      case DM1_s3:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum BL1_States { BL1_s1, BL1_s2 } BL1_State;

TickFct_BlinkLed() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(BL1_State) { // Transitions
      case -1:
         BL1_State = BL1_s1;
         break;
      case BL1_s1:
         if (!mtn) {
            BL1_State = BL1_s1;
         }
         else if (mtn) {
            BL1_State = BL1_s2;
         }
         break;
      case BL1_s2:
         if (1) {
            BL1_State = BL1_s1;
         }
         break;
      default:
         BL1_State = BL1_s1;
      } // Transitions

   switch(BL1_State) { // State actions
      case BL1_s1:
         B0 = 0;
         break;
      case BL1_s2:
         B0 = 1;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum IL1_States { IL1_s1, IL1_s2, IL1_s3 } IL1_State;

TickFct_IlluminateLamp() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
unsigned char cnt;
   switch(IL1_State) { // Transitions
      case -1:
         IL1_State = IL1_s1;
         break;
      case IL1_s1:
         if (!mtn) {
            IL1_State = IL1_s1;
         }
         else if (mtn) {
            IL1_State = IL1_s2;
         }
         break;
      case IL1_s2:
         if (!mtn) {
            IL1_State = IL1_s3;
            cnt = 0;
         }
         else if (mtn) {
            IL1_State = IL1_s2;
         }
         break;
      case IL1_s3:
         if ((!mtn && cnt < Duration(A1,A2,A3))) {
            IL1_State = IL1_s3;
         }
         else if (mtn) {
            IL1_State = IL1_s2;
         }
         else if ((!mtn && !cnt<Duration(A1,A2,A3))) {
            IL1_State = IL1_s1;
         }
         break;
      default:
         IL1_State = IL1_s1;
      } // Transitions

   switch(IL1_State) { // State actions
      case IL1_s1:
         B1 = 0;
         break;
      case IL1_s2:
         B1 = 1;
         break;
      case IL1_s3:
         cnt++;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}
int main() {
   B = 0; //Init outputs
   TimerSet(200);
   TimerOn();
   DM1_State = -1;
   BL1_State = -1;
   IL1_State = -1;
   while(1) {
      TickFct_DetectMotion();
      TickFct_BlinkLed();
      TickFct_IlluminateLamp();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}