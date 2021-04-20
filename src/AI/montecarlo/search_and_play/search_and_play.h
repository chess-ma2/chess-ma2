/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain bases, informations and structures for MCTS
 */

#ifndef MCTS_H
#define MCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../tree/mcts.h"

void select_action(MCTS_Node node);

MCTS_Node select(MCTS_Node node);

void roll_out(MCTS_Node node);

void update_value(int value); 

#endif
