#include "RIMS.h"

void main()
{
   unsigned char sum;
   while (1) {
      sum = A0 + A1 + A2 + A3 + A4 + A5;
      sum = 6 - sum;
      if (A7 & A6){
          B = (sum << 5) + 1;
      }
      else {
          B = (sum << 5);
      }
   }
}
