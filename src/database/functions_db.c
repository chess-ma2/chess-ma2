/**
 * @author Anna
 * @date 05/03/2021
 * @details Updating the database and selecting data
 */
#include "create_db.h"
#include "functions_db.c"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
//Call back
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int email_in_DB(char *email)
{

}

int rightPassword(char *email, unsigned char password[64])
{

}

//Get Id from mail
size_t getID(char *email)
{
    sqlite3 *db = createDB();
}


//_________________________________________________________________________
// Updating
// 1) Updating nb games won
void updatePL_gamesW(char *name)
// 2) Updating nb games lost


// 1) Updating nb games won
// 2) Updating nb games lost
// 3) Sum of execution times
