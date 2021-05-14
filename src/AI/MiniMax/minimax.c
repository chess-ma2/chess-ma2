#include "minimax.h"
#include "MINImove.c"
#include "../../common/c/rules/plate.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef MINIMAX_C
#define MINIMAX_C

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
struct node * create_node(struct currentpiece *current_List, int i, int nb_White, struct currentpiece *current_List_black, int nb_black, int depth, struct Piece *board)
{
  // Define queue
  struct queue *Q = malloc(sizeof(struct queue));
  // Create queue
  Q->Node = NULL;
  nb_queue = 0; // nb of elements in queue

  // Define parent
  struct node *parent = malloc(sizeof(struct node));
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
  int Max = 1; // White

  // enqueue parent
  Q = enqueue(parent, Q);


  while(nb_queue != 0)
  {

    //printf("before dequeue \n");
    // Dequeue to get current node to work on
    struct node *index = dequeue(Q);

    printf("\n\n\n");
    printf("dequeue with %i x=%i and y=%i\n", index->score, index->x, index->y + 1);

    // Depth is greater by 1
    if (index->depth > depth) {
      printf("max depth \n");
      free_queue(Q);
      nb_queue=0;
      return parent;
    }

    // Index for children
    int nb_children = 0;
    struct node *children = malloc(sizeof(struct node));

    // Get Max or Min mode to go through current chess pieces
    struct currentpiece *currentL = index->currentB;
    int currentNB = index->nbBlack;
    if (index->MiniMax == 1) { // Mode Max à faire
        printf("in Max mode \n");
        currentL = index->currentW;
        currentNB = index->nbWhite;
    }

    // Go through all current chess pieces
    for (int c = 0; c < currentNB; c++) {
    //for (int c = 0; c < 3; c++) {
      //1) Get List of All possible pieces (piece + x + y)
        printf("%i out of %i\n", c, currentNB);
        struct tab * moves = malloc(sizeof(struct tab));;
          printf("____________________________________________________________________________\n");
          printf("%i%i\n", currentL[c].x,currentL[c].y);
          printf("%i\n", index->board[(currentL[c].y)*8 + currentL[c].x].color);
      switch (index->board[(currentL[c].y)*8 + currentL[c].x].type)
      {
        case PAWN:printf("found pawn \n");
            find_chess_moves_pawn(index->board, currentL[c].x, currentL[c].y, board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case BISHOP:
              printf("found bishop \n");
            find_chess_moves_bishop(index->board, currentL[c].x, currentL[c].y, board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case KING:
              printf("found king \n");
            find_chess_moves_king(index->board, currentL[c].x, currentL[c].y, board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case QUEEN:
              printf("found queen \n");
            find_chess_moves_queen(index->board, currentL[c].x, currentL[c].y, board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case KNIGHT:
              printf("found knight \n");
            find_chess_moves_knight(index->board, currentL[c].x, currentL[c].y, board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case ROOK:
              printf("found rook \n");
            find_chess_moves_rook(index->board, currentL[c].x, currentL[c].y, board[currentL[c].y*8 + currentL[c].x].color, moves);
            break;
        case NONE:
              printf("NONE \n");
              break;
        default:
            printf("error\n");
      }

      // Get possible moves
      struct Moves *pos = moves->moves;

      printf("___________________ Children debug with %i children ________________________\n", moves->numberofmoves);

      for (int i = 0; i < moves->numberofmoves; i++) {

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

        // Get position
        new->x = pos[i].x_pos;
        new->y = pos[i].y_pos;

        // Define if node is Max or Min mode
        new->MiniMax = 1;
        if (index->MiniMax == 1) {
            new->MiniMax = 0;
        }


        // Before moving board -> change lists of current chess pieces on board
        if (Max == 0) { // If max = if white
          new->nbWhite = removedpiece(currentL[c].x - 1 ,currentL[c].y - 1, new->x -1, new->y -1, new->board, new->currentW, new->nbWhite); }
        else { new->nbBlack = removedpiece(currentL[c].x - 1 ,currentL[c].y - 1, new->x -1, new->y -1, new->board, new->currentB, new->nbBlack); }

        // Change board to get board
        new->board= pieceMove_2(currentL[c].x, currentL[c].y, new->x, new->y, new->board);

        struct currentpiece current;
        current.x = new->x;
        current.y = new->y;
        current.piece = new->board[new->y*8+new->x];


        // Get score
        new->score = getScore(current);
        printf("piece moved from x=%i, y=%i to x=%i, y=%i with %i[ok]\n", currentL[c].x, currentL[c].y +1, new->x, new->y+1, new->score);
        //display_board_special(new->board);

        // Add to children
        //nb_children++;
        children = (struct node *) realloc(children, (nb_children + 1) * sizeof(struct node));
        children[nb_children] = *new;
        nb_children++;
        //printf("end new n°%i\n",i);
        // 6)

        Q = enqueue(new, Q);
        //printf("Node value is x=%iy=%i\n",   Q->Node->x,  Q->Node->y);
        }
        free(moves->moves);
        free(moves);

    }
    printf("all the children are now born \n");
    printf("____________________________________________________________________________\n");

    index->nb_children = nb_children;
    index->children = children;
          }
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
    struct node *root = malloc(sizeof(struct node));
    Tree->root = root;
    struct node *children = malloc(nb_ListW * sizeof(struct node));
    // First Depth -> all possibilities
    children = create_node(current_ListW, 0, nb_ListW, current_ListB, nb_ListB, depth, board);

    root->children = children;
    root->nb_children = nb_ListW;
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

struct finalmove * get_right_move_ia(struct Piece *board, enum turn player_turn, int nb_List, int depth)
{
    struct finalmove * final = malloc(sizeof(struct finalmove));
    //struct currentpiece *current_List = create_whiteList();
    //struct currentpiece *current_ListB = create_blackList();

    //struct tree * T = create_tree(board, player_turn, current_List, nb_List, current_ListB, 16, depth);
    //struct node * root = T->root;
    return final;
}

struct tree * update_values(struct tree * T, int color, int depth)
{
    struct node * root = T->root;
    if (color==BLACK)
    {
        get_min_from_list(root->nb_children, root->children);
    }
    else{
        get_max_from_list(root->nb_children,root->children);
    }
    return T;
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
  free(Node->children);
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
