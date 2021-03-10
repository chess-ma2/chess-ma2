#ifndef CREATE_DB_H
#define CREATE_DB_H
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>


static int callback(void *NotUsed, int argc, char **argv, char **azColName);

sqlite3 * createDB();

void creatingTables();

void newPLAYER(char *name, unsigned char password[64], char *email, size_t nb_won, size_t nb_lost);

void newAI(char *type, size_t nb_won, size_t nb_lost, size_t time);

#endif
