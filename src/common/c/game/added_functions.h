#ifndef ADDED_FUNCTIONS_H
#define ADDED_FUNCTIONS_H

#include "version1.c"
#include "../rules/pieces.c"
#include "../rules/plate.c"
#include "../rules/check_and_pat.c"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>


/*
 * @author Anna
 * @date 20/03/2021 (finally spring)
 * @details added functions needed for the second version of the game
*/

// Structure for Lists of current pieces
struct currentpiece{
  struct Piece piece;
  int x;
  int y;
};

// Create List of white chess pieces
struct currentpiece * create_whiteList();

// Create List of black chess pieces
struct currentpiece * create_blackList();
#endif
