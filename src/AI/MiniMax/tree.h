#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef TREE_H
#define TREE_H
// Include section _______________________________
#include "../../common/c/rules/check_and_pat.c"
#include "../../common/c/rules/pieces.c"
#include "../../common/c/rules/plate.c"
#include "../../common/c/game/added_functions.c"
#include "MINImove.c"
#include "queue.c"

// Structure function ____________________________

struct tree{
  struct node *root;
};


// Function section _______________________________
// Position evaluation function
int getVal(struct Piece current);

// Function: prints a tree structure (dot version)
void print_tree_dot(struct tree *Tree);

// Function: prints a tree structure (almost pretty print)
void pretty_print(struct tree *Tree, int depth);


void printdfs(struct tree *Tree);

void __print(struct node *index);


// Gets score for a chess piece on board (with coef)
int getScore(struct currentpiece current);

// Copies a board
void copyboard(struct Piece *src, struct Piece *dst);

// Creates node - bfs
struct node * create_node(struct currentpiece *current_List, int i, int nb_White, struct currentpiece *current_List_black, int nb_black, int depth, struct Piece *board);

// Creates Tree for MiniMax
struct tree * create_tree(struct Piece *board, enum turn player_turn, struct currentpiece *current_ListW, int nb_ListW, struct currentpiece *current_ListB, int nb_ListB, int depth);

// Frees node -dfs
void free_node(struct node *Node);

// Frees Tree
void free_tree(struct tree *Tree);

#endif
