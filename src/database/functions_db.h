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

// Checking if an email is already in database
int email_in_DB(char *email);

//Checking if the password is right
int rightPassword(char *email, unsigned char password[64]);

//Get Id from mail
size_t getID(char *email);

#endif
