/**
 * @author Anna and Marine
 * @date 05/03/2021
 * @details Updating the database and selecting data
 */
#include "create_db.c"
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

    //Hash password
    unsigned long* res = SHA_1(password);

    //Create SQL query
    sprintf(sql, "Select * from PLAYER WHERE EMAIL = '%s' AND PASSWORD1 = '%lx' AND PASSWORD2 = '%lx' AND PASSWORD3 = '%lx' AND PASSWORD4 = '%lx' AND PASSWORD5 = '%lx'",email, res[0], res[1], res[2], res[3], res[4]);

    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);
    int right = 0;

    //If such query is possible
    if(result == SQLITE_OK)
    {
      //right = 1;
      if (sqlite3_step(selectstmt) == SQLITE_ROW) // Record found
      {
        right = 1;
      }
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
    sprintf(sql, "Select ID from PLAYER where email = '%s'",email);

    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);

    //If such query is possible
    if(result == SQLITE_OK)
    {
           //Get id and return
            size_t res = (size_t) sqlite3_column_int(selectstmt, 0);
            sqlite3_finalize(selectstmt);
            sqlite3_close(db);
            free(sql);
            return res;
    }

    //Close statement
    sqlite3_finalize(selectstmt);

    //Close connection to database
    sqlite3_close(db);

    //Free query
    free(sql);

    err(1, "No id \n");
}
//print Name
int callback_Name(void *NotUsed, int argc, char **argv,
                    char **azColName)
{

    NotUsed = 0;


    for (int i = 0; i < argc; i++) {
        azColName[i] = azColName[i];
        printf("%s", argv[i] ? argv[i] : "NULL");
    }

  //  printf("\n");

    return 0;
}


//Get name from email
void printNAME(char * email)
{
    //Connection to the database
    sqlite3 *db = createDB();

    //Create SQL query
    char *sql = malloc(200 * sizeof(char));
    sprintf(sql, "Select NAME from PLAYER where email = '%s'",email);


    //struct sqlite3_stmt *selectstmt;
    char *err_msg = 0;

    //Execute query to print name
    if (sqlite3_exec(db, sql, callback_Name, 0, &err_msg) != SQLITE_OK )
    {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
    }


    //Close statement
    //sqlite3_finalize(selectstmt);

    //Close connection to database
    sqlite3_close(db);

    //Free query
    free(sql);
}

//get wins from mail
size_t getWINS(char *email)
{
    //Connection to the database
    sqlite3 *db = createDB();

    //Create SQL query
    char *sql = malloc(200 * sizeof(char));
    sprintf(sql, "Select GAMES_WON from PLAYER where EMAIL = '%s'",email);

    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);

    //If such query is possible
    if(result == SQLITE_OK)
    {
        //If such row exists
       if (sqlite3_step(selectstmt) == SQLITE_ROW)
       {
           //Get id and return
            size_t res = (size_t) sqlite3_column_double(selectstmt, 0);
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

    err(1, "no wins attached to this mail \n");
}

//get wins from mail
size_t getLOST(char *email)
{
    //Connection to the database
    sqlite3 *db = createDB();

    //Create SQL query
    char *sql = malloc(200 * sizeof(char));
    sprintf(sql, "Select GAMES_LOST from PLAYER where EMAIL = '%s'",email);

    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);

    //If such query is possible
    if(result == SQLITE_OK)
    {
        //If such row exists
       if (sqlite3_step(selectstmt) == SQLITE_ROW)
       {
           //Get id and return
            size_t res = (size_t) sqlite3_column_double(selectstmt, 0);
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

    err(1, "no losts attached to this mail \n");
}

//_________________________________________________________________________
// Updating

// 1) Updating nb games won + 1
void update_victory(char * email)
{
    //Getting the DB
    sqlite3 *db = createDB();

    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));

    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET GAMES_WON = GAMES_WON + 1\n"\
            "WHERE EMAIL = '%s';",email);

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

    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));

    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET GAMES_LOST = GAMES_LOST + 1\n"\
            "WHERE EMAIL = '%s';",email);

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

    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));

    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET NAME = '%s'\n"\
            "WHERE EMAIL = '%s';",new,email);

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

    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));

    //creating the query
    sprintf(sql, "UPDATE PLAYER\n"\
            "SET EMAIL = '%s'\n"\
            "WHERE EMAIL = '%s';",new,email);

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

    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(100 * sizeof(char));

    //creating the query
    sprintf(sql, "DELETE\n"\
            "FROM\n"\
            "   PLAYER\n"\
            "WHERE\n"\
            "   EMAIL = '%s';",email);

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

//6) Ordering db depeding on the scores
/*
void order_champ()
{
    //Getting the DB
    sqlite3 *db = createDB();

    char *zErrMsg = 0;
    char *sql = malloc(100 * sizeof(char));
    int rc;

    //creating the query
    sprintf(sql,
            "SELECT\n"\
            "   NAME\n"
            "FROM\n"\
            "   PLAYER\n"\
       "ORDER BY\n"\
            "   GAMES_WON DESC,\n"\
                "   GAMES_LOST ASC;");

    //execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "order champ error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    //closing
    free(sql);
    sqlite3_close(db);
}

//7) getting the rank of one user from email
//TO FINISH

size_t get_rank(char * email)
{
    //Getting the DB
    sqlite3 *db = createDB();
    //ordering the db depending on the scores
    order_champ();

    //Create SQL query
    char *sql = malloc(200 * sizeof(char));
    sprintf(sql, "Select * from PLAYER where email = '%s'",email);

    struct sqlite3_stmt *selectstmt;

    int result = sqlite3_prepare_v2(db, sql, -1, &selectstmt, NULL);

    //If such query is possible
    if(result == SQLITE_OK)
    {
        printf("%i\n",sqlite3_step(selectstmt));
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

    err(1, "couldn't get the rank \n");

}*/
