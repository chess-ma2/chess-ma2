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

//Étape 3: #TODO by Anna
/*
  chiffrer :

   Pour chaque caractère du message
      lettreChiffrée = lettreClaire ^ e mod n
 */

//Étape 4: #TODO by Marie
/*
 déchiffrer :

   Pour chaque caractère du message
      lettreClaire = lettreChiffrée ^ d mod n 
 */
