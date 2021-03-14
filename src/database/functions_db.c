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

// Checking if an email is already in database
int email_in_DB(char *email)
{
    //Connection to the database
    sqlite3 *db = createDB();

    char *sql = malloc(200 * sizeof(char));
    int inMail = 0;

    //Create SQL query
     sprintf(sql, "Select * from PLAYER where email = '%s'",email);
    
    struct sqlite3_stmt *selectstmt;
    
    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    
    //If such query is possible
    if(result == SQLITE_OK)
    {
        //if such record is found
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

//Checking if the password is right
int rightPassword(char *email, unsigned char password[64])
{
    //Connection to the database
    sqlite3 *db = createDB();

    char *sql = malloc(300 * sizeof(char));
  
    //Create SQL query
     sprintf(sql, "Select PASSWORD1,PASSWORD2,PASSWORD3,PASSWORD4,PASSWORD5 from PLAYER where email = %s",email);

    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    
    //Hash password 
    unsigned long* res = SHA_1(password);
    int right = 1;

    //If such query is possible
    if(result == SQLITE_OK)
    {
            //Checking if a hash isn't correct
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

    //Close statement
    sqlite3_finalize(selectstmt);

    //Close connection to database
    sqlite3_close(db);

    //Free query
    free(sql);

    return right;

}

//Get Id from mail
size_t getID(char *email)
{
    //Connection to the database
    sqlite3 *db = createDB();

    //Create SQL query
    char *sql = malloc(200 * sizeof(char));
    sprintf(sql, "Select * from PLAYER where email = '%s'",email);
    
    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    
    //If such query is possible
    if(result == SQLITE_OK)
    {
        //If such row exists
       if (sqlite3_step(selectstmt) == SQLITE_ROW)
       {
           //Get id and return
            size_t res = (size_t) sqlite3_column_int(selectstmt, 0);
            sqlite3_finalize(selectstmt);
            sqlite3_close(db);
            free(sql);
            return res;
       }
    }

    //Close statement
    sqlite3_finalize(selectstmt);

    //Close connection to database
    sqlite3_close(db);

    //Free query
    free(sql);

    err(1, "No id \n");
}


//_________________________________________________________________________
// Updating

// 1) Updating nb games won + 1
void update_victory(char * email)
{
    //Getting the DB
    sqlite3 *db = createDB();
    //Getting the right id
    size_t id= getID(email);
    
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));
    
    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET GAMES_WON = GAMES_WON + 1\n"\
            "WHERE ID = '%zu';",id);
    
    //execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "victory update error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    //closing
    free(sql);
    sqlite3_close(db);
 }

// 2) Updating nb games lost + 1
void update_loss( char * email)
{
    //Getting the DB
    sqlite3 *db = createDB();
    //Getting the right id
    size_t id= getID(email);
    
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));
    
    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET GAMES_LOST = GAMES_LOST + 1\n"\
            "WHERE ID = '%zu';",id);
    
    //execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "loss update error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    //closing
    free(sql);
    sqlite3_close(db);
}

// 3) Updating new name of user x
void update_name( char * email, char * new)
{
    //Getting the DB
    sqlite3 *db = createDB();
    //Getting the right id
    size_t id= getID(email);
    
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));
    
    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET NAME = '%s'\n"\
            "WHERE ID = '%zu';",new,id);
    
    //execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "update name error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    //closing
    free(sql);
    sqlite3_close(db);
}

//4) Updating new email of user x
void update_email( char * email, char * new)
{
    //Getting the DB
    sqlite3 *db = createDB();
    //Getting the right id
    size_t id= getID(email);
    
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));
    
    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET EMAIL = '%s'\n"\
            "WHERE ID = '%zu';",new,id);
    
    //execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "update email error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    //closing
    free(sql);
    sqlite3_close(db);
}

//5) Deleting a line in DB
void delete_user(char * email)
{
    //Getting the DB
    sqlite3 *db = createDB();
    //Getting the right id
    size_t id= getID(email);
    
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));
    
    //creating the query
    sprintf(sql, "DELETE\n"\
            "FROM\n"\
            "   PLAYER\n"\
            "WHERE\n"\
            "   ID = '%zu';",id);
    
    //execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "delete user error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    
    //closing
    free(sql);
    sqlite3_close(db);
}
/*
// ?) Sum of execution times
 */
