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

//Adding one point of victory to user
void update_victory(char * email);

//Adding one point of lose to user
void update_loss( char * email);

//Changing name of user
void update_name( char * email, char * new);

//Changing mail of user
void update_email( char * email, char * new);

//Deleting user form database
void delete_user(char * email);

#endif
