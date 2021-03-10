/**
 * @author Anna
 * @date 07/03/2021
 * @details Generating hash table to encode future passwords
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SHA.h"

void pre_process(long x, unsigned char message[64])
{
    // Append the bit '1' by adding 0x80
    unsigned long new = 0;
    unsigned long p1 =~(~new<<8);
    for(int i = 0; i < 4; i++)
       {
          int j = 8 * i; // in bits
           // it's a multiple of 8 bits
          message[63-i]=(char)(( x & (p1<<j))>>j);

       }

}

void chunks(unsigned char message[64],unsigned long word[80])
{
   // Process the message into 512-bit chunks
   for(int i = 0; i < 16; i++)
          {
             int j = 4 * i;
             // break chunk into 16 32 bit words
             word[i]=((long)message[j])<<24 |((long)message[1+j])<<16|((long)message[2+j])<<8|((long)message[3+j])<<0;

          }

   // Message schedule: extend the sixteen 32-bit words into eighty 32-bit words
   for(int i = 16; i < 80;i++)
         {
              // XOR
              word[i]=word[i-16]^word[i-14]^word[i-8]^word[i-3];
              // Left Rotate
              unsigned long temp=word[i]<<1;
              unsigned long temp1=word[i]>>31;
              word[i]=temp|temp1;
         }
}

unsigned long* SHA_1(unsigned char msg[64] )
{
  //____________________ Init variables ____________________
  unsigned long H0 = 0x67452301;
  unsigned long H1 = 0xefcdab89;
  unsigned long H2 = 0x98badcfe;
  unsigned long H3 = 0x10325476;
  unsigned long H4 = 0xc3d2e1f0;

  //unsigned char input[64] = *msg;
  const char* input2 = (char *)msg;
  size_t ml = strlen(input2);

  //____________________ Pre-processing ____________________
  if(ml < 57) // <= 448 bits
         {
                long bits = ml * 8; // in bits
                pre_process( bits, msg);
                if(ml == 56)
                    for(size_t i = ml; i < 60; i++)
                    {
                      msg[i]=0;
                    }
                else
                   {
                    msg[ml]=128;
                    for(size_t i = ml + 1; i < 60; i++)
                    {
                      msg[i]=0;
                    }
                   }
         }

    //____________________ Message into 512-bit chunks _______
    unsigned long words[80];
    chunks(msg, words);

    //____________________ Init hash value for chunk __________
    unsigned long A = H0;
    unsigned long B = H1;
    unsigned long C = H2;
    unsigned long D = H3;
    unsigned long E = H4;

    //____________________ Main Loop __________________________

    for(int i = 0; i < 80; i++)
          {
                unsigned long k;
                unsigned long f;

                if( 0 <= i && i <= 19)
                {
                    k = 0x5a827999;
                    f = ( B & C ) | ( ~ B & D );
                }

                if( 20 <= i && i <= 39)
                {
                    k = 0x6ed9eba1;
                    f = B^C^D;
                }

                if( 40 <= i && i <= 59)
                {
                    k = 0x8f1bbcdc;
                    f = (B & C)|(B & D)|(C & D);
                }

                if( 60 <= i && i <= 79)
                {
                    k = 0xca62c1d6;
                    f = B^C^D;
                }

                // Left rotate
                unsigned long tmp1 = A<<5;
                unsigned long tmp2 = A>>27;
                unsigned long tmp3 = tmp1|tmp2;
                unsigned long tmp = tmp3 + f + E + words[i] + k;

                E = D;
                D = C;

                // Left rotate
                tmp1 = B<<30;
                tmp2 = B>>2;
                C = tmp1 | tmp2;
                B = A;
                A = tmp;

          }
          //__________________ Add to chunk's hash ___________________________
          H0 += A;
          H1 += B;
          H2 += C;
          H3 += D;
          H4 += E;

          //__________________ Produce final hash value ______________________
          unsigned long *hh = malloc(5 * sizeof(unsigned long));
          hh[0] = H0;
          hh[1] = H1;
          hh[2] = H2;
          hh[3] = H3;
          hh[4] = H4;
          // = {H0, H1, H2, H3, H4};
          return hh;

}

/* For tests

int main()
{
  unsigned char msg[64] = "passwordtest123";
  unsigned char *msg2 = (unsigned char *) msg;
  unsigned long *res = SHA_1(msg2);
  printf("%lx,%lx,%lx,%lx,%lx \n", res[0], res[1], res[2], res[3], res[4]);
  free(res);
  //printf("%hhx,%hhx,%hhx,%hhx,%hhx \n", res[0], res[1], res[2], res[3], res[4]);
  return 0;
}*/
