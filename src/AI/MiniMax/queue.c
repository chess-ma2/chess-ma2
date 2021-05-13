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
    Q->next = NULL;
    nb_queue++;
    return Q;
  }
  else{
  struct queue *new = malloc(sizeof(struct queue));
  new->Node = to_insert;
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
  printf("nb rn is %i \n",nb_queue );
  if (Q->Node == NULL)
    return NULL;

  struct queue *index = Q;
  struct queue *before = NULL;
  while(index->next != NULL)
  {
    before = index;
    index = index->next;
  }

  if (before != NULL) {
    before->next = NULL;
  }

  struct node *data = index->Node;
  if (index == Q) {
    index->Node = NULL;
  }
  nb_queue--;
  return data;
}

/*
 * @author Anna
 * @date 21/04/2021
 * @details Free queue
*/
void free_queue(struct queue *Q)
{
  printf(" 2 \n");
  if (Q->Node == NULL) { // No element
    free(Q);
    printf("before 3 \n");
    return;
  }

  struct queue *index = Q;
  while(index->next != NULL) // Get last
  { struct queue *del = index;
    printf("before 2 \n");
    free(del);
    printf("before 2 \n");
    index = index->next;
    printf("after 2 \n");
  }

  nb_queue = 0;
  free(index);
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
