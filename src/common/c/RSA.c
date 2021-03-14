/**
 * @author Marie and Anna
 * @date 14/03/2021
 * @details Encryption Algorithm of RSA
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "RSA.h"

// Étape 1: #TODO by Marie
/*
    cléPublique(p, q) :
 Choisir aléatoirement p et q, deux nombres premiers distincts
   n = p * q
   m = (p - 1) * (q - 1)
   Choisir e strictement inférieur à m et premier avec lui

   Retourner couple (n, e)
   */

// Étape 2: #TODO by Anna
/*
  cléPrivée(e, m, n) :

   Algorithme d'Euclide étendu pour calculer d (l'inverse de la multiplication
   de e mod m)

   Retourner couple (n, d)
 */



union private_key genpriv(double e, double m, double n)
{
    double x = e;
    double y = m;
    double q, tmp;
    double d = 1;
    double y0 = 0;

    while (y != 0){
        q = x / y;
        
        tmp = x % y;
        x = y;
        y = tmp;


        tmp = x;
        x = d - q * x;
        d = tmp;

        tmp = y;
        y = y0 -q * y;
        y0 = tmp;
    }

    if( d < 0 )
        d += m;

    union private_key res;
    res.n = n;
    res.d = d;
    return res;

}

//Étape 3: #TODO by Anna
/*
  chiffrer :

   Pour chaque caractère du message
      lettreChiffrée = lettreClaire ^ e mod n
 */

int expmod(double m, double e, double n)
{
    int res = 1;
    long long e2 =(long long) e; //to avoid overflow
    long long m2 = (long long) m; //to avoid overflow
    while(e2 > 0)
    {
        if(e2 & 1)
            res = (res * m2) % n;
        e2 = e2 >> 1;
        m2 = (m2 * m2) % n;
    }
    return res;
}

int* encodeMessage(int len, int bytes, char* message, double e, double n)
{
    int *encodedMessage = malloc((len / bytes) * sizeof(int));
    int x;
    for(i = 0; i < len; i+= bytes)
    {
        x = 0;
        for(int j = 0; j < bytes; j++)
        {
            x += message[ i + j ] * (1 << (7 * j));
        }
        encodedMessage[i / bytes] = expmod( x, e, n);
    }
    return encodedMessage;
}

//Étape 4: #TODO by Marie
/*
 déchiffrer :

   Pour chaque caractère du message
      lettreClaire = lettreChiffrée ^ d mod n 
 */
