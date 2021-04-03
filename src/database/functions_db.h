#ifndef FUNCTIONS_DB_H
#define FUNCTIONS_DB_H
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "create_db.c"
#include "SHA.c"

// Checking if an email is already in database
int email_in_DB(char *email);

//Checking if the password is right
int rightPassword(char *email, unsigned char password[64]);

//Get Id from mail
size_t getID(char *email);

//print Name
int callback_Name(void *NotUsed, int argc, char **argv, char **azColName);

//Get name from email to print it
void printNAME(char * email);

//Get number of party won from email
size_t getWINS(char *email);

//Get number of party lost from email
size_t getLOST(char *email);

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

//Ordering players depending on their scores
void order_champ();

//Geting the rank of user from mail
size_t get_rank(char * email);

#endif
