/**
 * @author Marine
 * @date 01/03/2021
 * @details Main file.c of common part
 */

//Safety loop guard
#ifndef COMMON_MAINC
#define COMMON_MAINC

//Rules part
#include "rules/rules.c"

/**
 * @author Marine
 * @date 01/03/2021
 * @details Main function of common part
 */
int main(int argc, char ** argv)
{

    return rules();
}

//End safety loop
#endif