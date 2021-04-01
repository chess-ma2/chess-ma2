#include "../network/game.c"
#include "../../../common/c/data/process_board.c"
#include "../../../common/c/rules/rules.c"
#include "../../../common/c/game/version1.c"
#include <stdio.h>


void wait_game_output()
{
    char good = 1;
    while (good)
    {
        sleep(1);
        pthread_mutex_lock(&mutex_output);
        if (last_side_output == 0)
            good = 0;
        pthread_mutex_unlock(&mutex_output);
    }
}

//the given data is: x/abAB or more if we decide to transfer the entire plate

//x is the code of the data

//__//0 the linking was made and the player is black

//__//1 the linking was made the player is white

//__//3 is a move to actualise

//_____//a-first x position
//_____//b-first y position
//_____//A-new x position
//_____//B-new y position

//__//4 is a request

//_____//a-code is the code of the request 0 wants to abort as a none existing game other?

//__//5 is an answer
//______//a-code 0 for no, 1 for yes

//__//6 is the end of the game
//_____//a = 1 if someone won , otherwise it is 0
//_____//b = 1 if player that is recieving is winning, otherwise it is 0


//uncodifying data and actualising it in board

void game_process()
{
    wait_game_output();

    pthread_mutex_lock(&mutex_output);
    last_side_output = 1;

    //Start
    switch (*buf_output)
    {
        case ('0'):
            printf("The connexion was successfull ! You are playing blacks\n");
            //setting the color parameter in ../../serveur/game.c
            color=0;
            
            //a voir si il faut init un board de base ?
            print_rules();
            //struct Piece* board = init_board()
            printf("Please wait for the other player to play\n");
            
            //je dois mettre ca ???
            wait_game_output();

            //ici commencer listen pour attendre l'info quoi
            
            
        case ('1'):
            printf("The connexion was successfull ! You are playing whites\n");
            //the color parameter in ../../serveur/game.c
            color=1;
            
            print_rules();
            printf("Your turn to play !\n");
            
            pthread_mutex_unlock(&mutex_output);
            
            struct Piece* board = init_board();
        
            pthread_mutex_lock(&mutex_input);
            
            //demander a antoine pas capté
            last_side_input = 1;
            //filling the buffer with the board
            //ask antoine why 1 and 0 at the extremities?
            *buf_input = '1';
            strcpy((buf_input+1), board_to_char(board));
            *(buf_input+65) = 0;
            pthread_mutex_unlock(&mutex_input);
            
            //demander de taper l'info en utilisant les fonctions de anna? car là pas fait?
            //l'info a-t-elle été envoyée au serveur là ?
            
            break;
            
            
        case('3'):
            printf("Your turn now!\n");
            
            struct Piece* board = char_to_board((buf_output+1));
            //or just take the 4 other args if we only want to move pieces
            pthread_mutex_unlock(&mutex_output);

            display(board);

            //Todo request action and apply move
            pthread_mutex_lock(&mutex_input);
            last_side_input = 1;
            *buf_input = '2';
            strcpy((buf_input+1), board_to_char(board));
            *(buf_input+65) = 0;
            pthread_mutex_unlock(&mutex_input);
            break;

        case ('4'):
            printf("The other player has a request \n");
            
            if (*(buf_output+1)==0)
            {
                printf("The player wants to sport the game \n"):
                printf("If you agree [y], your game wont be taken into acount\n");
                printf("If you disagree [n], the player will need to continue or to abort and then, let you win \n");
                printf("Enter [y] if you want to end the game, Enter [n] otherwise\n");
                char rep[1];
                scanf(" %i",rep);
                *buf_input='5';
                if (rep=='y')
                {
                    *(buf_input+1)=1;
                }
                else
                {
                    *(buf_input+1)=0;
                }
            }
            break;
        case ('5'):
            printf("The other player has responded \n");
            if (*(buf_output+1)==1)
            {
                printf("The game was cancelled \n");
                printf("you can try to make another one to be more successfull\n");
                *buf_input=6;
                *(buf_input+1)=0;
                *(buf_input+2)=0;
            }
            else
            {
                printf("The player didn't accept to cancel the game\n");
                printf("Do you want to abort? If you abort you will be considered as the looser\n");
                printf("enter 'y' to abort, enter 'n' to continue");
                scanf(" %i",rep);
                if (rep=='y')
                {
                    *(buf_input)=6;
                    *(buf_input+1)=1;
                }
                else
                {
                    //envoyer le meme joueur vers entrer les commandes qu'il souhaite
                }
            }
            
            //if other cases of request they need to be there

        break;
    }
    }

    game_process();
}
