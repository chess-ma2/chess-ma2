#ifndef SHA_H
#define SHA_H
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void pre_process(long x, unsigned char message[64]);

void chunks(unsigned char message[64],unsigned long word[80]);

unsigned long* SHA_1(unsigned char msg[64]);

int main();

#endif
