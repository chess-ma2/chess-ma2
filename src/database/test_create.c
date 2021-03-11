/**
 * @author Anna
 * @date 10/03/2021
 * @details Tests: Creating the database and its tables + verifying password
 */

#include "create_db.h"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "SHA.h"
#include "functions_db.h"


int main(int argc, char *argv[])
{

    //_________________ Create DB and tables ____________________________
    
    creatingTables();
   // no need I've already created them
    
    //_________________ Create new player    ____________________________
    char *name = malloc(100 * sizeof(char));
    unsigned char password[64];
    char *email = malloc(100 * sizeof(char));
    size_t nb_won = 0; 
    size_t nb_lost = 0;

    printf("_________________ Test Mode _________________\n");
    printf("\033[0;35m");
    printf("Test for new player \n");
    printf("Enter your name (100 char max): \n");
    scanf("%s", name);
    printf("Enter your email (100 char max): \n");
    scanf("%s", email);
    printf("Enter your password (64 char max): \n");
    scanf("%s", password);
    printf("\033[0m");

    newPLAYER( name, password, email, nb_won, nb_lost);

    //_________________ Search if new player is present    _____________
    printf("Is player now in database? .... searching for email \n");
    
    if(email_in_DB( email) != 0)
    {
        printf("\033[0;32m");
        printf("Email has been found \n");
        printf("\033[0m");

    }
    else
    {
        printf("\033[0;31m");
        printf("Email hasn't been found \n");
        printf("\033[0m");
        free(email);
        free(name);
        return 0;
    }

    //_________________ Double sure for password    _____________________
    unsigned char password2[64];
    printf("\033[0;35m");
    printf("Re-enter your password: \n");
    scanf("%s", password2);
    printf("\033[0m");

    if(rightPassword(email, password2) == 1)
    {
        printf("\033[0;32m");
        printf("Right password \n");
        printf("\033[0m");

    }
    else
    {
        printf("\033[0;31m");
        printf("Wrong password \n");
        printf("\033[0m");
    }

    free(email);
    free(name);
    return 0;

}
