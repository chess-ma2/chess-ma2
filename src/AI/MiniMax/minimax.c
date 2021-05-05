#include "minimax.h"
#include "MINImove.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MINIMAX_C
#define MINIMAX_C

// ___ Variables for queue ____________________________
int nb_queue = 0; // nb of elements in queue

/*
 * @author Anna
 * @date 17/04/2021
 * @details Enqueue
*/
struct queue * enqueue(struct node *to_insert, struct queue *Q) {
  if (Q->Node == NULL) {
    //printf("first in queue \n");
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
  if (Q->Node == NULL) { // No element
    free(Q);
    return;
  }

  struct queue *index = Q;
  while(index->next != NULL) // Get last
  { struct queue *del = index;
    free(del);
    index = index->next;
  }
  nb_queue = 0;
  free(index);
}

/*
 * @author Anna
 * @date 14/04/2021
 * @details Get Value for chess piece
*/

int getVal(struct Piece current)
{
  int res = 0; // Default is NULL
  if(current.color == BLACK) // Piece is black
  {
      switch(current.type) // Set value from type
      {
          case PAWN: res = -10; break;
          case ROOK: res = -50; break;
          case BISHOP: res = -30; break;
          case KNIGHT: res = -30; break;
          case QUEEN: res = -90; break;
          case KING: res = -900; break;
          default: res = 0;
      } }
  else // Piece is white
  {   switch(current.type)
      {
        case PAWN: res = 10; break;
        case ROOK: res = 50; break;
        case BISHOP: res = 30; break;
        case KNIGHT: res = 30; break;
        case QUEEN: res = 90; break;
        case KING: res = 900; break;
        default: res = 0;
      }
  }
  return res;
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Subfunction: prints a node -dfs

void __print(struct node *Node)
{
  printf("|%i|", Node->score);
  for (int i = 0; i < Node->nb_children; i++) {
    __print(&Node->children[i]);
  }
  printf("\n | \n");

}


 * @author Anna
 * @date 17/04/2021
 * @details Function: prints a tree structure

void print_tree(struct tree *Tree)
{
  struct node *Root = Tree->root;
  for (int i = 0; i < Root->nb_children; i++) {
    __print(&Root->children[i]);
  }
}
*/

void print_tree_dot(struct tree *Tree)
{
  // Define queue
  struct queue *Q = malloc(sizeof(struct queue));
  Q->Node = NULL;
  nb_queue = 0; // nb of elements in queue

  // enqueue root
  Q = enqueue(Tree->root, Q);

  while(nb_queue != 0)
  {
    struct node *index = dequeue(Q);
    printf("%i ", index->score);
    for (int i = 0; i < index->nb_children; i++) {
      printf("%i -- %i\n", index->score, index->children[i].score);
      Q = enqueue(&index->children[i], Q);
    }
  }
  free_queue(Q);
}

void pretty_print(struct tree *Tree)
{
  // Define queue
  struct queue *Q = malloc(sizeof(struct queue));
  Q->Node = NULL;
  nb_queue = 0; // nb of elements in queue

  // enqueue root
  Q = enqueue(Tree->root, Q);
  printf("Tree : \n");
  while(nb_queue != 0)
  {
    struct node *index = dequeue(Q);
    //printf("\n");
    for (int i = 0; i < index->nb_children; i++) {
      printf("-- %i", index->children[i].score);
      Q = enqueue(&index->children[i], Q);
    }
    printf("\n");
  }
  free_queue(Q);
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Gets score for a chess piece on board (with coef)
*/

int getScore(struct currentpiece current)
{

double pawn_table[64]={0, 0, 0, 0, 0, 0, 0, 0, \
                      5, 5, 5, 5, 5, 5, 5, 5, \
                      1, 1, 2, 3, 3, 2, 1, 1, \
                      0.5, 0.5, 1, 2.5, 2.5, 1, 0.5, 0.5, \
                      0, 0, 0, 2, 2, 0, 0, 0, \
                      0.5, -0.5, -1, 0, 0, -1, -0.5, 0.5, \
                      0.5, 1, 1, -2, -2, 1, 1, 0.5, \
                      0, 0, 0, 0, 0, 0, 0, 0};

double rook_table[64]={0, 0, 0, 0, 0, 0, 0, 0, \
                      0.5, 1, 1, 1, 1, 1, 1, 0.5, \
                      -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                      -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                      -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                      -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                      -0.5, 0, 0, 0, 0, 0, 0, -0.5, \
                      0, 0, 0, 0.5, 0.5, 0, 0, 0};

double bishop_table[64]={-2, -1, -1, -1, -1, -1, -1, -2, \
                      -1, 0, 0, 0, 0, 0, 0, -1, \
                      -1, 0, 0.5, 1, 1, 0.5, 0, -1, \
                      -1, 0.5, 0.5, 1, 1, 0.5, 0.5, -1, \
                      -1, 0, 1, 1, 1, 1, 0, -1, \
                      -1, 1, 1, 1, 1, 1, 1, -1, \
                      -1, 0.5, 0, 0, 0, 0, 0.5, -1, \
                      -2, -1, -1, -1, -1, -1, -1, -2};

double knight_table[64]={ -5, -4, -3, -3, -3, -3, -4, -5  \
                      -4, -2, 0, 0, 0, 0, -2, -4, \
                      -3, 0, 1, 1.5, 1.5, 1, 0, -3, \
                      -3, 0.5, 1.5, 2, 2, 1.5, 0.5, -3, \
                      -3, 0, 1.5, 2, 2, 1.5, 0, -3, \
                      -4, -2, 0, 0.5, 0.5, 0, -2, -4, \
                      -5, -4, -3, -3, -3, -3, -4, -5 };

double queen_table[64]={ -2, -1, -1, -0.5, -0.5, -1, -1, -2, \
                     -1, 0, 0, 0, 0, 0, 0, -1, \
                     -1, 0, 0.5, 0.5, 0.5, 0.5, 0, -1, \
                     -0.5, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5, \
                     0, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5, \
                     -1, 0.5, 0.5, 0.5, 0.5, 0.5, 0, -1, \
                     -1, 0, 0.5, 0, 0, 0, 0, -1, \
                     -2, -1, -1, -0.5, -0.5, -1, -1, -2 };

double king_table[64]={ -3, -4, -4, -5, -5, -4, -4, -3, \
                    -3, -4, -4, -5, -5, -4, -4, -3, \
                    -3, -4, -4, -5, -5, -4, -4, -3, \
                    -3, -4, -4, -5, -5, -4, -4, -3, \
                    -2, -3, -3, -4, -4, -3, -3, -2, \
                    -1, -2, -2, -2, -2, -2, -2, -1, \
                    2, 2, 0, 0, 0, 0, 2, 2, \
                    2, 3, 1, 0, 0, 1, 3, 2 };


  int piece_val = getVal(current.piece);
  int res;
  switch (current.piece.type) {
    case PAWN: res = (int) piece_val * pawn_table[(current.y)*8+current.x]; break;
    case ROOK: res = (int) piece_val * rook_table[(current.y)*8+current.x]; break;
    case BISHOP: res = (int) piece_val * bishop_table[(current.y)*8+current.x]; break;
    case KNIGHT: res = (int) piece_val * knight_table[(current.y)*8+current.x]; break;
    case QUEEN: res = (int) piece_val * queen_table[(current.y)*8+current.x]; break;
    case KING: res = (int) piece_val * king_table[(current.y)*8+current.x]; break;
    default: res = 0;
  }
  return res;
}

/*
 * @author Anna and Marine
 * @date 17/04/2021
 * @details Creates node - bfs
*/
struct node * create_node(struct currentpiece *current_List, int i, int depth, struct Piece *board)
{
  // Define queue
  struct queue *Q = malloc(sizeof(struct queue));
  Q->Node = NULL;
  nb_queue = 0; // nb of elements in queue

  // Define parent
  struct node *parent = malloc(sizeof(struct node));
  parent->x = current_List[i].x;
  parent->y = current_List[i].y;
  parent->score = getScore(current_List[i]);
  int current_depth = -1;

  // enqueue parent
  Q = enqueue(parent, Q);
  while(nb_queue != 0)
  {

    //printf("before dequeue \n");
    struct node *index = dequeue(Q);
    printf("dequeue with %i x=%i and y=%i\n", index->score, index->x, index->y);

    current_depth += 1; // Works

    int nb_children = 0;
    struct node *children = malloc(sizeof(struct node));

    // 1) Get List of All possible pieces (piece + x + y)

      struct tab * moves = malloc(sizeof(struct tab));
      printf("%i %i\n",index->x,index->y);
      printf("work %u\n",board[(index->y)*8 + index->x].type);
          switch (board[(index->y)*8 + index->x].type)
          {
            case PAWN:
<<<<<<< HEAD
                moves = find_chess_moves_pawn(board, index->x , index->y, board[index->y*8 + index->x].color);
=======
                  printf("found pawn \n");
                moves = find_chess_moves_pawn(board, index->x, index->y, board[index->y*8 + index->x].color);
>>>>>>> c58516363344cfd23917eb05ff7e659c5cbc34c4
                break;
            case BISHOP:
                  printf("found bishop \n");
                moves = find_chess_moves_bishop(board, index->x, index->y, board[index->y*8 + index->x].color);
                break;
            case KING:
                  printf("found king \n");
                moves = find_chess_moves_king(board, index->x, index->y, board[index->y*8 + index->x].color);
                break;
            case QUEEN:
                  printf("found queen \n");
                moves = find_chess_moves_queen(board, index->x, index->y, board[index->y*8 + index->x].color);
                break;
            case KNIGHT:
                  printf("found knight \n");
                moves = find_chess_moves_knight(board, index->x, index->y, board[index->y*8 + index->x].color);
                break;
            case ROOK:
                  printf("found rook \n");
                moves = find_chess_moves_rook(board, index->x, index->y, board[index->y*8 + index->x].color);
                break;
            case NONE:
                  printf("NONE \n");
                  break;
            default:
                printf("error\n");
          }

          struct Moves *pos = moves->moves;
      
          for (size_t i = 0; i < moves->numberofmoves; i++) {
            // 3)
            struct node *new = malloc(sizeof(struct node));
            new->x = pos[i].x_pos;
            new->y = pos[i].y_pos;
            //printf("new move is x=%i, y=%i \n", new->x, new->y);
            struct currentpiece current;
            current.piece = board[pos[i].y_pos*8+pos[i].x_pos];
            current.x = new->x;
            current.y = new->y;
            new->score = getScore(current);
            // 4) and 5)
            children[nb_children++] = *new;
            // 6)
            Q = enqueue(new, Q);
            }
          index->nb_children = nb_children;
          index->children = children;

          if (current_depth == depth ) {
            //printf("max depth \n");
            free(moves);
            free_queue(Q);
            break; }

          }
      return parent;
}

/*
 * @author Anna and Marine
 * @date start 15/04/2021
 * @details Creates Tree for MiniMax
*/

struct tree * create_tree(struct Piece *board, enum turn player_turn, struct currentpiece *current_List, int nb_List, int depth)
{
    //  1) Get all current chess piece for said color -> current_List
    //  2) For each go through its children and create a new node
    struct tree *Tree = malloc(sizeof(struct tree));
    struct node *root = malloc(sizeof(struct node));
    Tree->root = root;
    struct node *children = malloc(nb_List * sizeof(struct node));
    // First Depth -> all possibilities
    for (int i = 0; i < nb_List; i++) {
      children[i] = *create_node(current_List, i, depth, board);
    }
    root->children = children;
    root->nb_children = nb_List;
    printf("Tree created [ok] \n");
    return Tree;
}

int get_min_from_list(int nb_children,struct node *children)
{
    int min = children[nb_children-1].score;
    nb_children--;
    while (nb_children>=0)
    {
        if (children[nb_children].score < min)
        {
            min = children[nb_children].score;
        }
        nb_children--;
    }
    return min;
}

int get_max_from_list(int nb_children,struct node *children)
{
    int max = children[nb_children-1].score;
    nb_children--;
    while (nb_children>=0)
    {
        if (children[nb_children].score > max)
        {
            max = children[nb_children].score;
        }
        nb_children--;
    }
    return max;
}

struct tree * update_minimax (struct tree * T, int color)
{
    int coef = 1;
    if (color == BLACK)
    {
        coef =-1;
    }
    return T;
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Frees node -dfs
*/

void free_node(struct node *Node)
{
  if (Node->children) {
    free_node(Node->children);
    Node->children = NULL;
  }

  free(Node);
  Node = NULL;
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Frees Tree
*/

void free_tree(struct tree *Tree)
{
  if (Tree->root) {
    free_node(Tree->root);
  }
  free(Tree);
  Tree = NULL;
}

#endif
