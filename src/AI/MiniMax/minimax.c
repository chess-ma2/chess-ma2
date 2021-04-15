#include "minimax.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Position evaluation function
int getVal(struct Piece current)
{
  int res = 0; // Default is NULL
  if(current.color == BLACK) // Piece is black
  {
      switch(current.type) // Set value from type
      {
          case PAWN:
              res = -10;
              break;
          case ROOK:
              res = -50;
              break;
          case BISHOP:
              res = -30;
              break;
          case KNIGHT:
              res = -30;
              break;
          case QUEEN:
              res = -90;
              break;
          case KING:
              res = -900;
              break;
          default: res = 0;
      } }
  else // Piece is white 
  {   switch(current.type)
      {
        case PAWN:
            res = 10;
            break;
        case ROOK:
            res = 50;
            break;
        case BISHOP:
            res = 30;
            break;
        case KNIGHT:
            res = 30;
            break;
        case QUEEN:
            res = 90;
            break;
        case KING:
            res = 900;
            break;
        default: res = 0;
      }
  }
  return res;
}
