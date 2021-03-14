#ifndef RSA_H
#define RSA_H
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

union private_key{
    double n;
    double d;
};

union private_key genpriv(double e, double m, double n);

int expmod(double m, double e, double n);

int* encodeMessage(int len, int bytes, char* message, double e, double n);
#endif
