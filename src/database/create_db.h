#ifndef CREATE_DB_H
#define CREATE_DB_H
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

// Creating the database or opening it
sqlite3 * createDB();

// Creating 2 tables: player and artificial intelligence
void creatingTables();

// Adding a player into the database
void newPLAYER(char *name, unsigned char password[64], char *email, size_t nb_won, size_t nb_lost);

// Adding an AI into the database
void newAI(char *type, size_t nb_won, size_t nb_lost, size_t time);

#endif
