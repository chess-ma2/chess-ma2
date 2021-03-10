/**
 * @author Anna and Marine
 * @date 05/03/2021
 * @details Updating the database and selecting data
 */
#include "create_db.h"
#include "functions_db.h"
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
    //Connection to the database
    sqlite3 *db = createDB();

    char *sql = malloc(200 * sizeof(char));
    int inMail = 0;

    //Create SQL query
     sprintf(sql, "Select * from PLAYER where email = %s",email);
    
    struct sqlite3_stmt *selectstmt;
    
    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    
    //If such query is possible
    if(result == SQLITE_OK)
    {
        //value = if such record is found
        if(sqlite3_step(selectstmt) == SQLITE_ROW)
            inMail = 1;
    }
    
    //Close statement
    sqlite3_finalize(selectstmt);
    
    //Close connection to database
    sqlite3_close(db);

    //Free query
    free(sql);
    
    return inMail;
}

int rightPassword(char *email, unsigned char password[64])
{
    //Connection to the database
    sqlite3 *db = createDB();

    char *sql = malloc(300 * sizeof(char));
  
    //Create SQL query
     sprintf(sql, "Select PASSWORD1,PASSWORD2,PASSWORD3,PASSWORD4,PASSWORD5 from PLAYER where email = %s",email);

    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    unsigned long* res = SHA_1(password);
    int right = 1;

    //If such query is possible
    if(result == SQLITE_OK)
    {
            unsigned long pass1 = (unsigned long) sqlite3_column_text(selectstmt, 0);
            if(pass1 != res[0])
                right = 0;                

            unsigned long pass2 = (unsigned long) sqlite3_column_text(selectstmt, 1);
            if(pass2 != res[1])
                right = 0;

            unsigned long pass3 = (unsigned long) sqlite3_column_text(selectstmt, 2);
            if(pass3 != res[2])
                right = 0;

            unsigned long pass4 = (unsigned long) sqlite3_column_text(selectstmt, 3);
            if(pass4 != res[3])
                right = 0;

            unsigned long pass5 = (unsigned long) sqlite3_column_text(selectstmt, 4);
            if(pass5 != res[4])
                right = 0;

    }

    sqlite3_finalize(selectstmt);
    sqlite3_close(db);
    free(sql);
    return right;

}

//Get Id from mail
size_t getID(char *email)
{
    sqlite3 *db = createDB();

    char *sql = malloc(200 * sizeof(char));
     sprintf(sql, "Select * from PLAYER where email = %s",email);
    
    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    
    if(result == SQLITE_OK)
    {
       if (sqlite3_step(selectstmt) == SQLITE_ROW)
       {
            size_t res = (size_t) sqlite3_column_int(selectstmt, 0);
            sqlite3_finalize(selectstmt);
            sqlite3_close(db);
            free(sql);
            return res;
       }
    }
    sqlite3_finalize(selectstmt);
    sqlite3_close(db);
    free(sql);
    err(1, "No id \n");
}


//_________________________________________________________________________
/* Updating
// 1) Updating nb games won + 1
void updatePL_gamesW(char *email)
{
    sqlite3 *db = createDB();



}

// 2) Updating nb games lost


// 1) Updating nb games won
// 2) Updating nb games lost
// 3) Sum of execution times
 */
