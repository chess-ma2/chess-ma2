#ifndef PLAYWITHROBOT_H
#define PLAYWITHROBOT_H

// Include Section
#include "../rules/pieces.c"
#include "../rules/plate.c"
#include "../rules/check_and_pat.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ANSI-color-codes.h"
#include "../../../database/create_db.c"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "../../../database/SHA.c"
#include "../../../database/functions_db.c"

// PLAYER STRUCTURE
struct Player {
    char *name;
    unsigned char password[64];
    char *email;
    size_t nb_won;
    size_t nb_lost;
    int team_color;

};

// Stalemate answer structure
struct res_stalemate{
    int answer;
    enum turn player_turn;
};

//Results update
struct Move{
    int xbeg;
    int ybeg;
    int xdes;
    int ydes;
};

int playwrobot(struct Piece *board, struct Player *player1,int type);

#endif
