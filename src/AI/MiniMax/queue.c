#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "queue.h"

#ifndef QUEUE_C
#define QUEUE_C
// ___ Variables for queue ____________________________
int nb_queue = 0; // nb of elements in queue

/*
 * @author Anna
 * @date 17/04/2021
 * @details Enqueue
*/
struct queue * enqueue(struct node *to_insert, struct queue *Q) {
  if (Q->Node == NULL) {
    Q->Node = to_insert;
    //printf("Node value is %i%i\n",   Q->Node->x,  Q->Node->y);
    Q->next = NULL;
    Q->last = 1;
    nb_queue++;
    return Q;
  }
  else{
  struct queue *new = malloc(sizeof(struct queue));
  new->Node = to_insert;
  new->last = 0;
  //printf("Node value is %i%i and one before was %i%i \n", new->Node->x,new->Node->y, Q->Node->x,  Q->Node->y);
  new->next = Q;
  nb_queue++;
  return new;
  }
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Dequeue
*/
struct node * dequeue(struct queue *Q) {
  if (Q->Node == NULL || nb_queue == 0 )
    return NULL;

    if (Q->last == 1) {
      struct node *data = Q->Node;
      Q->Node = NULL;
      return data;
    }

  struct queue *index = Q;
  //printf("index node is %i\n", index->Node->score);


  struct queue *before = NULL;
  while(index->next->last == 0)
  {
    before = index;
    index = index->next;
    //printf("index next node is %i\n", index->Node->score);
  }

  if (before != NULL) {
    before->next = NULL;
    before->last = 1;
  }

  struct node *data = index->next->Node;
  if (index == Q) {
    index->Node = NULL;
    index->last = 1;
  }

  nb_queue--;
  //printf("is %i%i\n", data->x,data->y);
  return data;
}

/*
 * @author Anna
 * @date 21/04/2021
 * @details Free queue
*/
void free_queue(struct queue *Q)
{
  if (Q) {
    free(Q);
    nb_queue = 0;
    Q = NULL;
  }
  printf("queue freed [ok]\n");
}

struct Piece *pieceMove_2(int x, int y, int des_x, int des_y, struct Piece *board)
{
  struct Piece piece = board[y*8+x];
  struct Piece piece_des = board[des_y*8+des_x];


  board[des_y*8 + des_x] = piece ;//move the piece
  board[y*8+ x].type = NONE;
  board[y*8+ x].color = 0;

  if( piece_des.type != NONE ) //catch an adverse piece
    {
      piece_des.type = NONE; //the adverse piece disappears
    }
  return board; //return the finally board
}


#endif
