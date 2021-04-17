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



struct tree * create_tree(struct Piece *board, enum turn player_turn, struct Piece *current_player)
{
    //  1) Get all current chess piece for said color

    //  2) For each go through its children and create a new node
    struct tree *Tree = malloc(sizeof(struct tree));
    struct node root = malloc(sizeof(struct node));
    Tree->root = root;

    


}
