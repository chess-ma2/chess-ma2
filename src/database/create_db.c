/**
 * @author Anna
 * @date 11/03/2021
 * @details Creating the database and its tables
 */
#include "create_db.h"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "SHA.h"

// Creating the database or opening it
sqlite3 * createDB()
{
    sqlite3 *db;
    int rc;

    // Create database if it doesn't already exist or open connection to db
    rc = sqlite3_open("chess.db", &db);

    // Making sure there are no errors
    if(rc){
        fprintf(stderr,"Can't open database \n");
        return 0;
    }
    return db;
}

// Creating 2 tables: player and artificial intelligence
void creatingTables()
{
    //Getting the DB
    sqlite3 *db = createDB();
    char *zErrMsg = 0;
    char *sql;
    char *sql2;

    /* Create SQL statement to create player table */
   sql = "CREATE TABLE PLAYER("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "NAME           TEXT    NOT NULL," \
      "PASSWORD1      REAL    NOT NULL," \
      "PASSWORD2      REAL    NOT NULL," \
      "PASSWORD3      REAL    NOT NULL," \
      "PASSWORD4      REAL    NOT NULL," \
      "PASSWORD5      REAL    NOT NULL," \
      "EMAIL          TEXT," \
      "GAMES_WON      REAL,"\
      "GAMES_LOST     REAL );";

   /* Execute SQL statement */
   sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
   /*if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }*/

   //________________________________________________________

   /* Create SQL statement to create AI table */
   sql2 = "CREATE TABLE AI("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "TYPE           TEXT    NOT NULL," \
      "GAMES_WON      REAL,"\
      "GAMES_LOST     REAL,"\
      "TIME_RUN       REAL );";

   /* Execute SQL statement */
   sqlite3_exec(db, sql2, NULL, 0, &zErrMsg);
   /*if( rc2 != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }*/

   //________________________________________________________

    //Close database
    sqlite3_close(db);
}

//_____________________ Adding a player into the database ___________

void newPLAYER(char *name, unsigned char password[64], char *email, size_t nb_won, size_t nb_lost)
{
    //Getting the DB
    sqlite3 *db = createDB();

    // Creating new player
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(300 * sizeof(char));
    unsigned long *res = SHA_1(password);

    // Create the query
    sprintf(sql, "INSERT INTO PLAYER (NAME,PASSWORD1,PASSWORD2,PASSWORD3,PASSWORD4,PASSWORD5,EMAIL,GAMES_WON,GAMES_LOST) VALUES ('%s', '%lx', '%lx', '%lx', '%lx', '%lx', '%s', '%zu', '%zu'); ",
            name, res[0], res[1], res[2], res[3], res[4], email, nb_won, nb_lost);

    //Execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    free(res);
    free(sql);
    sqlite3_close(db);
}

//_____________________ Adding an AI into the database ___________

void newAI(char *type, size_t nb_won, size_t nb_lost, size_t time)
{
    //Getting the DB
    sqlite3 *db = createDB();

    // Creating new artificial intelligence
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(300 * sizeof(char));

    // Create the query
    sprintf(sql, "INSERT INTO AI (TYPE,GAMES_WON,GAMES_LOST,TIME_RUN) "  \
         "VALUES ( '%s', '%zu', '%zu', '%zu' ); ", type, nb_won, nb_lost, time);

    //Execute query
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    //If error in query
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    free(sql);
    sqlite3_close(db);
}
