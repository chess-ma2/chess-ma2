#include "minimax.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// ___ Variables for queue ____________________________
struct node **queue = malloc(sizeof(struct node));
int front = 0; // 1st element
int rear = -1; // Last element
int nb_queue = 0; // nb of elements in queue

/*
 * @author Anna
 * @date 17/04/2021
 * @details Enqueue
*/
void enqueue(struct node *to_insert) {
  realloc(queue, (nb_queue + 1) * sizeof(struct node));
  queue[++rear] = to_insert;
  nb_queue++;
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Dequeue
*/
struct node * dequeue() {
   struct node *data = queue[front++];
   nb_queue--;
   return data;
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
*/
void __print(struct node *Node)
{
  printf("|%i|", Node->score);
  for (size_t i = 0; i < nb_children; i++) {
    __print(Node->children[i]);
  }
  printf("\n | \n");

}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Function: prints a tree structure
*/
void print_tree(struct tree *Tree)
{
  struct node *Root = Tree->node;
  for (size_t i = 0; i < Root->nb_children; i++) {
    __print(Root->children[i]);
  }
}

/*
 * @author Anna
 * @date 17/04/2021
 * @details Gets score for a chess piece on board (with coef)
*/

int getScore(struct currentpiece current)
{
  int piece_val = getVal(current->piece);
  int res;
  switch (current->piece->type) {
    case PAWN: res = piece_val * pawn_table[current->y*8+current->x]; break;
    case ROOK: res = piece_val * rook_table[current->y*8+current->x]; break;
    case BISHOP: res = piece_val * bishop_table[current->y*8+current->x]; break;
    case KNIGHT: res = piece_val * knight_table[current->y*8+current->x]; break;
    case QUEEN: res = piece_val * queen_table[current->y*8+current->x]; break;
    case KING: res = piece_val * king_table[current->y*8+current->x]; break;
    default: res = 0;
  }
  return res;
}

/*
 * @author Anna and Marine
 * @date 17/04/2021
 * @details Creates node - bfs
*/
struct node * create_node(struct currentpiece *current_List, int i, int depth)
{
  // Define parent
  struct node *parent = malloc(sizeof(struct node));
  parent.x = current_List[i].x;
  parent.x = current_List[i].y;
  parent.score = getScore(struct currentpiece current);
  int current_depth = -1;

  // enqueue parent
  enqueue(parent);
  while(nb_queue != 0)
  {
    struct node *index = dequeue();
    int nb_children = 0;
    struct node *children = malloc(sizeof(struct node));

    current_depth += 1; // Will see if this actually works
    if (current_depth > depth ) {
      continue;
    }
    // Get List of All possible pieces (piece + x + y)
    // for each possible piece
        // Create node
        // children[nb_children] = this node
        // Nb children += 1
        // enqueue node
    index->nb_children = nb_children;
    index->children = children;
  }

  free(queue);
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
    for (size_t i = 0; i < nb_List; i++) {
      children[i] = create_node(current_List, i, depth);
    }
    return Tree;
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
