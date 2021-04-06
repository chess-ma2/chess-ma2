/**
 * @author Marine
 * @date 01/03/2021
 * @details Main file.c of common part
 */

//Safety loop guard
#ifndef COMMON_MAIN_C
#define COMMON_MAIN_C

//Rules part
#include "rules/rules.c"
#include "rules/pieces.h"
#include "rules/plate.h"
#include "data/process_board.c"
#include "launching/launching.c"

/**
 * @author Marine
 * @date 01/03/2021
 * @details Main function of common part
 */
int main(int argc, char ** argv)
{
    return launching();
}

//End safety loop
#endif
