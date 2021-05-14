#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

struct node {
  int x;
  int y;
  int score;
  int nb_children;
  int depth;
  struct Piece *board;
  int MiniMax; // 0 is Mini and 1 is Maxi(white)
  struct currentpiece *currentW;
  int nbWhite;
  struct currentpiece *currentB;
  int nbBlack;
  struct node *children;
};


struct queue {
  struct node *Node;
  struct queue *next;
  int last; // 0 False and 1 if true
};

// Enqueue
struct queue * enqueue(struct node *to_insert, struct queue *Q);

// Dequeue
struct node * dequeue(struct queue *Q);

// Free Queue
void free_queue(struct queue *Queue);

struct Piece *pieceMove_2(int x, int y, int des_x, int des_y, struct Piece *board);

#endif
