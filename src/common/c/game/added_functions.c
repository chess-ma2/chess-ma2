#ifndef ADDED_FUNCTIONS_C
#define ADDED_FUNCTIONS_C

#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "added_functions.h"

/*
 * @author Anna
 * @date 16/04/2021
 * @details Create List of white chess pieces
*/
struct currentpiece * create_whiteList()
{
  struct currentpiece *white = malloc(16 *sizeof(struct currentpiece));
  for (size_t i = 0; i < 8; i++) {
    white[i] = {{PAWN, WHITE}, i, 6};
  }
  white[8] = {{ROOK, WHITE}, 0, 7};
  white[9] = {{ROOK, WHITE}, 7, 7};
  white[10] = {{KNIGHT, WHITE}, 1, 7};
  white[11] = {{KNIGHT, WHITE}, 6, 7};
  white[12] = {{BISHOP, WHITE}, 2, 7};
  white[13] = {{BISHOP, WHITE}, 5, 7};
  white[14] = {{QUEEN, WHITE}, 3, 7};
  white[15] = {{KING, WHITE}, 4, 7};
  return white;
}

/*
 * @author Anna
 * @date 16/04/2021
 * @details Create List of black chess pieces
*/
struct currentpiece * create_blackList()
{
  struct currentpiece *black = malloc(16 *sizeof(struct currentpiece));
  for (size_t i = 0; i < 8; i++) {
    black[i] = {{PAWN, BLACK}, i, 1};
  }
  black[8] = {{ROOK, BLACK}, 0, 0};
  black[9] = {{ROOK, BLACK}, 7, 0};
  black[10] = {{KNIGHT, BLACK}, 1, 0};
  black[11] = {{KNIGHT, BLACK}, 6, 0};
  black[12] = {{BISHOP, BLACK}, 2, 0};
  black[13] = {{BISHOP, BLACK}, 5, 0};
  black[14] = {{QUEEN, BLACK}, 3, 0};
  black[15] = {{KING, BLACK}, 4, 0};
  return black;
}

int removedpiece(int x, int y, int des_x, int des_y, struct Piece *board, struct currentpiece *List, int nb_el)
{
  if (board[des_y*8+des_x].type != NONE]) { // If there's a piece where we're going at
    int found = 1; // found = 0 if piece in List
    int i = 0; // index

    while( i < nb_el && found == 1)
    { if (List[i].piece.type == board[des_y*8+des_x].type && List[i].x == des_x && List[i].y == des_y) {
        // Found so make this piece last in list before making it NULL
        for (size_t j = i; j < nb_el - 1; j++) {
          struct currentpiece tmp = List[j];
          List[j] = List[j + 1]
        }
        List[nb_el - 1] = NULL;
        nb_el -= 1;
        found = 0;
      }
      i += 1;
    }                                 }

  // Change in List current coordinates of piece now it's being moved
  int i = 0; // index
  int found = 1; // found in List
  while (i < nb_el && found == 1) {
    if (List[i].piece.type == board[y*8+x].type && List[i].x == x && List[i].y == y) { // found in List
      List[i].x = des_x;
      List[i].y = des_y; // Change coordinates
      found = 0; // found
    }
    i += 1;
  }
  return nb_el;
}

#endif
