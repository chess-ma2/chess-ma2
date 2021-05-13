#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef QUEUE_H
#define QUEUE_H

struct queue {
  struct node *Node;
  struct queue *next;
};

// Enqueue
struct queue * enqueue(struct node *to_insert, struct queue *Q);

// Dequeue
struct node * dequeue(struct queue *Q);

// Free Queue
void free_queue(struct queue *Queue);

struct Piece *pieceMove_2(int x, int y, int des_x, int des_y, struct Piece *board);

#endif
