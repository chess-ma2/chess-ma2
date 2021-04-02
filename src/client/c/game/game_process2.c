#include "../network/game.c"
#include "../../../common/c/data/process_board.c"
#include "../../../common/c/rules/rules.c"
#include "../../../common/c/rules/pieces.c"
#include "../../../common/c/game/version1.c"
#include "../../../common/c/rules/check_and_pat.c"
#include <stdio.h>

//AJOUTER LE LAST SIDE INPUT

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

// Checking if coordinates are incorrect
//if incorect 1
int incorrect_coor(char x,int y)
{
    if ((x=='W' || x=='S') & y=0)
    {
        return 0;
    }
    return x < 'A' || x > 'H' || y < 1 || y > 8;
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
            pthread_mutex_unlock(&mutex_output);
            //a voir si il faut init un board de base ?
            print_rules();
            //struct Piece* board = init_board()
            printf("Please wait for the other player to play...\n");
            break;
            
            
        case ('1'):
            printf("The connexion was successfull ! You are playing whites\n");
            
            //the color parameter in ../../serveur/game.c
            color=1;
            pthread_mutex_unlock(&mutex_output);
            
            print_rules();
            printf("Your turn to play !\n");
            
            
            struct Piece* board = init_board();
            display(board);
            pthread_mutex_lock(&mutex_input);
            
            board=throw_action(board);
            
            if (board==NULL)
            {
                break;
            }
            
            last_side_input = 1;
            //filling the buffer with the board
            *buf_input = '2';
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

            board=throw_action(board);
            if (board==NULL)
            {
                break;
            }
            
            last_side_input = 1;
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
                pthread_mutex_unlock(&mutex_input);
                printf("The player wants to end the game \n"):
                printf("If you agree [y], your game wont be taken into acount\n");
                printf("If you disagree [n], the player will need to continue or to abort and then, let you win \n");
                printf("Enter [y] if you want to end the game, Enter [n] otherwise\n");
                
                pthread_mutex_lock(&mutex_input);
                last_side_input = 1;
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
                pthread_mutex_unlock(&mutex_input);
            }
            break;
            
        case ('5'):
            pthread_mutex_unlock(&mutex_input);
            printf("The other player has responded \n");
            
            last_side_input = 1;
            pthread_mutex_lock(&mutex_input);
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
                    board=throw_action(board);
                    if (board==NULL)
                    {
                        break;
                    }
                    
                    *buf_input = '2';
                    strcpy((buf_input+1), board_to_char(board));
                    *(buf_input+65) = 0;
                }
                pthread_mutex_unlock(&mutex_input);
            }
            
            //if other cases of request they need to be there
            break;
        case ('6'):
            printf("The game is over")
            if (*(buf_output+1)==1)
            {
                if (*(buf_output+2)==1)
                {
                    //call the fonctions to say you've won
                }
                else
                {
                        //call the db fonction to say lose
                }
            }
            //find a way to end the linking going on
        
        default:
            errx(1,"notworking");
    }
    }

    game_process();
}

struct Piece* throw_action(board)
{
    int ok=1;
    
    while (ok)
    {
        //begin to read coordinates
        char coor[4]=coord_entered();
        char x_char = coor[0];
        int y = (int)coor[1];
        char des_x_char = coord[2];
        int des_y = (int)coor[3];

        //withdraw
        if ( x_char == 'W' && y == 0 && des_x_char == 'W' && des_y == 0){
            last_side_input = 1;
            withdraw();
            pthread_mutex_unlock(&mutex_input);
            return NULL;
            }

        //stalemate
        if(x_char == 'S' && y == 0 && des_x_char == 'S' && des_y == 0){
            last_side_input = 1;
            stalemate();
            pthread_mutex_unlock(&mutex_input);
            return NULL;
        }
    
        //analyse basics mistakes
        int a= valid_interpret(isValidMove(x,y,des_x,des_y));
        if (a)
        {
            ok=0;
        }
        
        int x = ((int)x_char) - 64;
        if (errgestion(board,x))
        {
            ok=1;
        }
    }
    //now coordinates are recievable CHECK
    
    //test check mate TODO
    //test promotion TODO
    //test rock TODO
    
    //usual game
    board = pieceMove(x-1 , y-1, des_x-1, des_y-1, board);
    printf("you move was just approved\n");
    
    display(board);
    
    return board;
}

//when the party is on, when the player receives an message
//the player needs to play back so we
int errgestion(struct Piece* board,int x)
{
    
    if((color==1 && board[(y-1)*8+(x+1)].color == BLACK && board[(y-1)*8+(x+1)].type != NONE) ||
          (color==0 && board[(y-1)*8+(x+1)].color == WHITE && board[(y-1)*8+(x+1)].type != NONE))
       {
         printf(URED "\n That isn't your chess piece to move. \n" reset);
           return 1;
       }
    return 0;
    
}

//TO DO stalemate
void stalemate()
{
    //TODO VERIFY IF PORSSIBLE
    *buf_input = '6';
    *(buf_output+1) = '0';
    *(buf_output+2) = '0';
    //+ajouter le fait d'arreter l communication et dire que cette personne perd
}
//TO DO withdraw
void withdraw()
{
    *buf_input = '6';
    *(buf_output+1) = '1';
    *(buf_output+2) = '1';
    //+ajouter le fait d'arreter l communication et dire que cette personne perd
}

//asks for the coordonates
char coord_entered()
{
    //variables
    char ret[0];
    int xi=0;
    char x_char = 'A';
    int y = 0;
    int des_x = 0;
    char des_x_char = 'A';
    int des_y = 0;
    
    printf(" it's your turn! \n\n");
    //______________________________________________________________________________________________________

    //Get original coordinates
    printf("Please enter the original coordinates of the chess piece you want to move (ex: A3) : \n");
    scanf(" %c%d", &x_char, &y);
    //x = ((int)x_char) - 65;
    xi = ((int)x_char) - 64;
    
    while(incorrect_coor(x_char,y))
    {
      printf(URED "Oops... you haven't entered correct coordinates please try again \n" reset);
      printf("Please enter the original coordinates of the chess piece you want to move (ex: A3) : \n");
      scanf(" %c%d\n", &x_char, &y);
    }

    //Get new coordinates
    printf("Please enter the new coordinates of the chess piece you want to move (ex: B1) : \n");
    scanf(" %c%d", &des_x_char, &des_y);
    //des_x = ((int)des_x_char) - 65;
    des_x = ((int)des_x_char) - 64;
    
    while(incorrect_coor(des_x_char,des_y))
    {
      printf(URED "Oops... you haven't entered correct destination coordinates please try again \n" reset);
      printf("Please enter the destination coordinates of the chess piece you want to move to (ex: A3) : \n");
      scanf(" %c%d\n", &x_char, &y);
    }
    
    ret[0]=x;
    ret[1]=(char)y;
    ret[2]=x_dest;
    ret[3]=(char)y_dest;
    
    return ret;
}

//interpet is valid move

int valid_interpret(int a)
{
    //Making sure the move is valid
    switch (a)
    {
        case 0:
            printf("the movement is impossible\n");
            return requestaction(board);
            break;
        case 1:
            printf("coordinates are valid!");
            break;
        case 2:
            printf("coordinates out of range! make sure you enter it well please...\n");
            return requestaction(board);
            break;
        case 3:
            printf("the destination you've selected already has one of your piece ! \n");
            return requestaction(board);
            break;
        case 4:
            printf("the piece you've selected is not existing, it is a empty part of the board\n");
            return requestaction(board);
            break;
        default:
            errx(1,"error while checking args");
            
    }
}

//to function that detects every particularity possible promotion rock check mate


