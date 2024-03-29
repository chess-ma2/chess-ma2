#include "tree.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef TREE_C
#define TREE_C

/*
 * @author Anna
 * @date 12/05/2021
 * @details Copies a board
*/
void copyboard(struct Piece *src, struct Piece *dst)
{
  for (size_t i = 0; i < 64; i++) {
    (dst + i)->color = (src + i)->color;
    (dst + i)->type = (src + i)->type;
  }
}

/*
 * @author Anna
 * @date 14/05/2021
 * @details Copies a list of chess pieces
*/
void copyCurrentList(struct currentpiece *src, struct currentpiece *dst, int n)
{
  for (size_t i = 0; i < n; i++) {
    (dst + i)->x = (src + i)->x;
    (dst + i)->y = (src + i)->y;
  }
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


void __print(struct node *index)
{
  printf("Score:%i x%iy%i nb %i depth %i ", index->score, index->x, index->y, index->nb_children, index->depth);
  struct node *first = index->childn1;
  for (int i = 0; i < index->nb_children; i++)
  {
    printf("        |          ");
    __print(first);
    first = first->next;
  }

  printf("\n");
}

void printdfs(struct tree *Tree)
{
  printf("Root is x%iy%i\n", Tree->root->x, Tree->root->y);
  __print(Tree->root);
  printf("\n\n");
}

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
    printf("%i -- %i\n", index->score, index->childn1->score);
    struct node *child = index->childn1;
    for (int i = 1; i < index->nb_children; i++) {
      child = child->next;
      printf("%i -- %i\n", index->score, child->score);
      Q = enqueue(child, Q);
    }
  }
  free_queue(Q);
}


void pretty_print(struct tree *Tree, int depth)
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
    if (index == NULL) {
      free_queue(Q);
      nb_queue = 0;
      return;
    }

    if (!(index->score == 0 && index->x == 0 && index->y == 0 && index->nb_children == 0)) {
    printf("(%i)Node Score= %i x=%i y=%i has %i nb of children \n", index->depth, index->score,index->x,index->y,index->nb_children);
      }
    if (index->nb_children > 0) {

    printf("-- (Score %i x=%i y=%i)\n", index->childn1->score,index->childn1->x,index->childn1->y);

    // first child
    struct node *child = index->childn1;
    if (child->depth < depth) {
      Q = enqueue(child, Q);
    }

    // The rest
    for (int i = 1; i <= index->nb_children; i++) {
      child = child->next;
      printf("-- (Score %i x=%i y=%i)\n", child->score,child->x,child->y);

      if (child->depth < depth) {
       Q = enqueue(child, Q);
      }
    }
    printf("\n");
    }
  }
  free_queue(Q);
  nb_queue = 0;
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
struct node * create_node(struct currentpiece *current_List, int i, int nb_White, struct currentpiece *current_List_black, int nb_black, int depth, struct Piece *board)
{
  // Define queue
  struct queue *Q = malloc(sizeof(struct queue));
  // Create queue
  Q->Node = NULL;
  nb_queue = 0; // nb of elements in queue

  // Define parent
  struct node *parent = malloc(sizeof(struct node));
  parent->xbeg = -1;
  parent->ybeg = -1;
  parent->x = current_List[i].x;
  parent->y = current_List[i].y;
  parent->score = getScore(current_List[i]);
  parent->board = board;
  parent->MiniMax = 1;
  parent->currentW = malloc(nb_White *sizeof(struct currentpiece));
  copyCurrentList(current_List, parent->currentW, nb_White);
  parent->nbWhite = nb_White;
  parent->currentB  = malloc(nb_black * sizeof(struct currentpiece));
  copyCurrentList(current_List_black, parent->currentB, nb_black);
  parent->nbBlack = nb_black;
  parent->depth = 0;
  parent->childn1 = malloc(sizeof(struct node));

  // enqueue parent
  Q = enqueue(parent, Q);


  while(nb_queue != 0)
  {

    // Dequeue to get current node to work on
    struct node *index = dequeue(Q);
    if (index == NULL) {
      free_queue(Q);
      nb_queue=0;
      return parent;
    }


    // Index for children
    int nb_children = 0;

    // Get Max or Min mode to go through current chess pieces
    struct currentpiece *currentL = index->currentB;
    int currentNB = index->nbBlack;
    if (index->MiniMax == 1) { // Max Mode (White)
        currentL = index->currentW;
        currentNB = index->nbWhite;
    }

    // Go through all current chess pieces
    for (int c = 0; c < currentNB; c++) {
      //1) Get List of All possible pieces (piece + x + y)
      struct tab * moves = malloc(sizeof(struct tab));;

      struct Piece *tmp = calloc(8*8, sizeof(struct Piece));;
      copyboard(index->board, tmp);
      switch (index->board[(currentL[c].y)*8 + currentL[c].x].type)
      {
        case PAWN:
            find_chess_moves_pawn(tmp, currentL[c].x, currentL[c].y, index->board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case BISHOP:
            find_chess_moves_bishop(tmp, currentL[c].x, currentL[c].y, index->board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case KING:
            find_chess_moves_king(tmp, currentL[c].x, currentL[c].y, index->board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case QUEEN:
            find_chess_moves_queen(tmp, currentL[c].x, currentL[c].y, index->board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case KNIGHT:
            find_chess_moves_knight(tmp, currentL[c].x, currentL[c].y, index->board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case ROOK:
            find_chess_moves_rook(tmp, currentL[c].x, currentL[c].y, index->board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case NONE:
              break;
        default:
            printf("");
      }
      free(tmp);
      // Get possible moves
      struct MovesMini *pos = moves->moves;

      int carry = 0;
      for (int i = 0; i < moves->numberofmoves; i++) {
        if (pos[i].x_pos >= 0 && pos[i].y_pos >= 0 && pos[i].x_pos < 8 && pos[i].y_pos < 8) {

        carry = 1;
        // Create new node
        struct node *new = malloc(sizeof(struct node));

        // Create board for node and its components
        new->board = calloc(8*8, sizeof(struct Piece));;
        copyboard(index->board, new->board);

        new->currentW = malloc(index->nbWhite *sizeof(struct currentpiece));
        copyCurrentList(index->currentW, new->currentW, index->nbWhite);
        new->nbWhite = index->nbWhite;
        new->currentB  = malloc(nb_black * sizeof(struct currentpiece));
        copyCurrentList(index->currentB, new->currentB, index->nbBlack);
        new->nbBlack = nb_black;
        new->depth = index->depth + 1;
        new->childn1 = malloc(sizeof(struct node));
        new->next = malloc(sizeof(struct node));

        // Get position
        new->ybeg = currentL[c].y;
        new->xbeg = currentL[c].x;
        new->x = pos[i].x_pos;
        new->y = pos[i].y_pos;

        // Define if node is Max or Min mode
        new->MiniMax = 1;
        if (index->MiniMax == 1) {
            new->MiniMax = 0;
        }


        // Before moving board -> change lists of current chess pieces on board
        if (index->MiniMax == 1) { // If max = if white
          new->nbBlack = removedpiece(currentL[c].x ,currentL[c].y, new->x, new->y, new->board, new->currentW, new->currentB, new->nbWhite,  new->nbBlack); }
        else { new->nbWhite = removedpiece(currentL[c].x ,currentL[c].y, new->x, new->y, new->board, new->currentB, new->currentW, new->nbBlack, new->nbWhite); }

        // Change board to get board
        new->board= pieceMove_2(currentL[c].x, currentL[c].y, new->x, new->y, new->board);
        struct currentpiece current;
        current.x = new->x;
        current.y = new->y;
        current.piece = new->board[new->y*8+new->x];


        // Get score
        new->score = getScore(current);
        // Add to children-
        if (nb_children == 0) {
          index->childn1 = new;
        }
        else{
          struct node *get_index = index->childn1;
          for (int j = 1; j < nb_children ; j++) {
            get_index = get_index->next;
          }
          get_index->next = new;
        }

        nb_children++;

        // 6)
        if (new->depth < depth) {
         Q = enqueue(new, Q);
        }

        }
      }
      if (moves) {
        free(moves);
      }
    }
    index->nb_children = nb_children;
          }
      if (Q)
      {free_queue(Q);}
      nb_queue=0;
      return parent;
}

/*
 * @author Anna and Marine
 * @date start 15/04/2021
 * @details Creates Tree for MiniMax
*/

struct tree * create_tree(struct Piece *board, enum turn player_turn, struct currentpiece *current_ListW, int nb_ListW, struct currentpiece *current_ListB, int nb_ListB, int depth)
{
    //  1) Get all current chess piece for said color -> current_List
    //  2) For each go through its children and create a new node
    struct tree *Tree = malloc(sizeof(struct tree));
    Tree->root = malloc(sizeof(struct node));
    // First Depth -> all possibilities
    Tree->root = create_node(current_ListW, 0, nb_ListW, current_ListB, nb_ListB, depth, board);
    return Tree;
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Frees node
*/

void free_node(struct node *Node)
{
if (Node) {
  free(Node->board);
  free(Node->currentW);
  free(Node->currentB);
  if (Node->nb_children > 0) {
    struct node *child =Node->childn1;
    for (size_t i = 1; i < Node->nb_children; i++) {
      child = child->next;
      free(child);
    }
  }
  free(Node);
}

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
}

#endif
