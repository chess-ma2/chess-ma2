/**
 * @author Marie
 * @date Start 15/04/2021
 * @details Contain functions for the AI
 */

#ifndef SEARCH_AND_PLAY_H
#define SEARCH_AND_PLAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.c>
#include <string.h>
#include "../tree/mcts.h"

void select_action(MCTS_Node node);

MCTS_Node select(MCTS_Node node);

void roll_out(MCTS_Node node);

void update_value(MCTS_Node node, float value); 

#endif
