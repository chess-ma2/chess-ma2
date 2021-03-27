#ifndef RSA_H
#define RSA_H
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


union public_key{
  double n;
  double e;
  double m;
};

union private_key{
    double n;
    double d;
};

int findprimenumber(double a, double b);

union public_key genpub(); 

union private_key genpriv(double e, double m, double n);

int expmod(double m, double e, double n);

int* encodeMessage(int len, int bytes, char* message, double e, double n);

int* decodeMessage(int len, int bytes, char* message, double d, double n); 
#endif
