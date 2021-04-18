#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MINIMAX_H
#define MINIMAX_H
// Include section _______________________________
#include "../../common/c/rules/check_and_pat.c"
#include "../../common/c/rules/pieces.c"
#include "../../common/c/rules/plate.c"
#include "../../common/c/game/added_functions.c"


/* Define section _______________________________
define pawn_table {0, 0, 0, 0, 0, 0, 0, 0, \
                    5, 5, 5, 5, 5, 5, 5, 5, \
                    1, 1, 2, 3, 3, 2, 1, 1, \
                    0.5, 0.5, 1, 2.5, 2.5, 1, 0.5, 0.5, \
                    0, 0, 0, 2, 2, 0, 0, 0, \
                    0.5, -0.5, -1, 0, 0, -1, -0.5, 0.5, \
                    0.5, 1, 1, -2, -2, 1, 1, 0.5, \
                    0, 0, 0, 0, 0, 0, 0, 0}

define rook_table {0, 0, 0, 0, 0, 0, 0, 0, \
                    0.5, 1, 1, 1, 1, 1, 1, 0.5, \
                    -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                    -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                    -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                    -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                    -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                    0, 0, 0, 0.5, 0.5, 0, 0, 0}

define bishop_table {-2, -1, -1, -1, -1, -1, -1, -2, \
                      -1, 0, 0, 0, 0, 0, 0, -1, \
                      -1, 0, 0.5, 1, 1, 0.5, 0, -1, \
                      -1, 0.5, 0.5, 1, 1, 0.5, 0.5, -1, \
                      -1, 0, 1, 1, 1, 1, 0, -1, \
                      -1, 1, 1, 1, 1, 1, 1, -1, \
                      -1, 0.5, 0, 0, 0, 0, 0.5, -1, \
                      -2, -1, -1, -1, -1, -1, -1, -2}

define knight_table { -5, -4, -3, -3, -3, -3, -4, -5  \
                      -4, -2, 0, 0, 0, 0, -2, -4, \
                      -3, 0, 1, 1.5, 1.5, 1, 0, -3, \
                      -3, 0.5, 1.5, 2, 2, 1.5, 0.5, -3, \
                      -3, 0, 1.5, 2, 2, 1.5, 0, -3, \
                      -4, -2, 0, 0.5, 0.5, 0, -2, -4, \
                      -5, -4, -3, -3, -3, -3, -4, -5 }

define queen_table { -2, -1, -1, -0.5, -0.5, -1, -1, -2, \
                     -1, 0, 0, 0, 0, 0, 0, -1, \
                     -1, 0, 0.5, 0.5, 0.5, 0.5, 0, -1, \
                     -0.5, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5, \
                     0, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5, \
                     -1, 0.5, 0.5, 0.5, 0.5, 0.5, 0, -1, \
                     -1, 0, 0.5, 0, 0, 0, 0, -1, \
                     -2, -1, -1, -0.5, -0.5, -1, -1, -2 }

define king_table { -3, -4, -4, -5, -5, -4, -4, -3, \
                    -3, -4, -4, -5, -5, -4, -4, -3, \
                    -3, -4, -4, -5, -5, -4, -4, -3, \
                    -3, -4, -4, -5, -5, -4, -4, -3, \
                    -2, -3, -3, -4, -4, -3, -3, -2, \
                    -1, -2, -2, -2, -2, -2, -2, -1, \
                    2, 2, 0, 0, 0, 0, 2, 2, \
                    2, 3, 1, 0, 0, 1, 3, 2 }*/
// Structure function ____________________________
struct node {
  int x;
  int y;
  int score;
  int nb_children;
  struct node *children;
};

struct tree{
  struct node *root;
};


// Function section _______________________________
// Position evaluation function
int getVal(struct Piece current);

// Enqueue
void enqueue(struct node *to_insert);

// Dequeue
struct node * dequeue();

// Subfunction: prints a node -dfs
void __print(struct node *Node);

// Function: prints a tree structure
void print_tree(struct tree *Tree);

//Gets score for a chess piece on board (with coef)
int getScore(struct currentpiece current);

// Creates node - bfs
struct node * create_node(struct currentpiece *current_List, int i, int depth);

// Creates Tree for MiniMax
struct tree * create_tree(struct Piece *board, enum turn player_turn, struct currentpiece *current_List, int nb_List, int depth);

// Frees node -dfs
void free_node(struct node *Node);

// Frees Tree
void free_tree(struct tree *Tree);

#endif
