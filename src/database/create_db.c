/**
 * @author Anna
 * @date 04/03/2021
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

// Callback function
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

// Creating the database or opening it
sqlite3 * createDB()
{
    sqlite3 *db;
    int rc;

    // Create database if it doesn't already exist
    rc = sqlite3_open("chess.db", &db);

    /* Making sure there are no errors
    if(rc){
        fprintf(stderr,"Can't open database \n");
        return 0;
    } else {
        fprintf(stderr, "Database created successfully \n");
    }*/

    return db;
    // Close database after using it
    //sqlite3_close(db);

}

// Creating 2 tables: player and artificial intelligence
void creatingTables()
{
    //Getting the DB
    sqlite3 *db = createDB();
    int rc;
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
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);  
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Player table created successfully\n");
   }

   //________________________________________________________

   /* Create SQL statement to create AI table */
   sql2 = "CREATE TABLE AI("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "TYPE           TEXT    NOT NULL," \
      "GAMES_WON      REAL,"\
      "GAMES_LOST     REAL,"\
      "TIME_RUN       REAL );";

   /* Execute SQL statement */
   int rc2 = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
   if( rc2 != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "AI table created successfully\n");
   }

   //________________________________________________________

    //Close database
    sqlite3_close(db);
}

void newPLAYER(char *name, unsigned char password[64], char *email, size_t nb_won, size_t nb_lost)
{
    //Getting the DB
    sqlite3 *db = createDB();
    
    // Creating new player
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(300 * sizeof(char));
    unsigned long *res = SHA_1(password);

    //printf("password is %lx, %lx, %lx, %lx, %lx \n", res[0], res[1], res[2], res[3], res[4]);



    sprintf(sql, "INSERT INTO PLAYER (NAME,PASSWORD1,PASSWORD2,PASSWORD3,PASSWORD4,PASSWORD5,EMAIL,GAMES_WON,GAMES_LOST) VALUES ('%s', '%lx', '%lx', '%lx', '%lx', '%lx', '%s', '%zu', '%zu'); ", 
            name, res[0], res[1], res[2], res[3], res[4], email, nb_won, nb_lost);

  //  sql = "INSERT INTO PLAYER (NAME,PASSWORD1,PASSWORD2,PASSWORD3,PASSWORD4,PASSWORD5,EMAIL,GAMES_WON,GAMES_LOST) "  \
         ("VALUES (%s, %lx, %lx, %lx, %lx, %lx, %s, %zu, %zu); ", name, res[0], res[1], res[2], res[3], res[4], email, nb_won, nb_lost);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); 
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    free(res);
    free(sql);
    sqlite3_close(db);
}

void newAI(char *type, size_t nb_won, size_t nb_lost, size_t time)
{
    //Getting the DB
    sqlite3 *db = createDB();

    // Creating new artificial intelligence
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(300 * sizeof(char));

    sprintf(sql, "INSERT INTO AI (TYPE,GAMES_WON,GAMES_LOST,TIME_RUN) "  \
         "VALUES ( %s, %zu, %zu, %zu ); ", type, nb_won, nb_lost, time);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    free(sql);
    sqlite3_close(db);
}

