#ifndef FUNCTIONS_DB_H
#define FUNCTIONS_DB_H
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "create_db.h"
#include "SHA.h"

static int callback(void *data, int argc, char **argv, char **azColName);

int email_in_DB(char *email);

int rightPassword(char *email, unsigned char password[64]);

size_t getID(char *email);

#endif
