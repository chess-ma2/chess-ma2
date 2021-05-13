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
#include "MINImove.c"
#include "queue.c"

// Structure function ____________________________
struct node {
  int x;
  int y;
  int score;
  int nb_children;
  struct Piece *board;
  int MiniMax; // 0 is Mini and 1 is Maxi(white)
  struct currentpiece *currentW;
  int nbWhite;
  struct currentpiece *currentB;
  int nbBlack;
  struct node *children;
};

struct tree{
  struct node *root;
};

struct finalmove{
    int x;
    int y;
    int xdes;
    int ydes;
};


// Function section _______________________________
// Position evaluation function
int getVal(struct Piece current);

// Subfunction: prints a node -dfs
//void __print(struct node *Node);

// Function: prints a tree structure (dot version)
void print_tree_dot(struct tree *Tree);

// Function: prints a tree structure (almost pretty print)
void pretty_print(struct tree *Tree);

// Gets score for a chess piece on board (with coef)
int getScore(struct currentpiece current);

// Copies a board
void copyboard(struct Piece *src, struct Piece *dst);

// Creates node - bfs
struct node * create_node(struct currentpiece *current_List, int i, int nb_White, struct currentpiece *current_List_black, int nb_black, int depth, struct Piece *board);

// Creates Tree for MiniMax
struct tree * create_tree(struct Piece *board, enum turn player_turn, struct currentpiece *current_ListW, int nb_ListW, struct currentpiece *current_ListB, int nb_ListB, int depth);

int get_min_from_list(int nb_children,struct node *children);

int get_max_from_list(int nb_children,struct node *children);

struct finalmove * get_right_move_ia(struct Piece *board, enum turn player_turn, int nb_List, int depth);

struct tree * update_value (struct tree * T, int color, int depth);

// Frees node -dfs
void free_node(struct node *Node);

// Frees Tree
void free_tree(struct tree *Tree);

#endif
