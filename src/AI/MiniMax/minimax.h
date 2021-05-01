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

struct Moves
{
    int x_pos;
    int y_pos;
};

struct queue {
  struct node *Node;
  struct queue *next;
};


// Function section _______________________________
// Position evaluation function
int getVal(struct Piece current);

// Enqueue
struct queue * enqueue(struct node *to_insert, struct queue *Q);

// Dequeue
struct node * dequeue(struct queue *Q);

// Free Queue
void free_queue(struct queue *Queue);

// Subfunction: prints a node -dfs
//void __print(struct node *Node);

// Function: prints a tree structure (dot version)
void print_tree_dot(struct tree *Tree);

// Function: prints a tree structure (almost pretty print)
void pretty_print(struct tree *Tree);

//Gets score for a chess piece on board (with coef)
int getScore(struct currentpiece current);

// Creates node - bfs
struct node * create_node(struct currentpiece *current_List, int i, int depth, struct Piece *board);

// Creates Tree for MiniMax
struct tree * create_tree(struct Piece *board, enum turn player_turn, struct currentpiece *current_List, int nb_List, int depth);

int get_min_from_list(int nb_children,struct node *children);

int get_max_from_list(int nb_children,struct node *children);

struct tree * update_minimax (struct tree * T, int color);

// Frees node -dfs
void free_node(struct node *Node);

// Frees Tree
void free_tree(struct tree *Tree);

#endif
