/*
 * @author Marine
 * @date 20/05/2021
 * @details the play with network gtk program
*/

#ifndef PLAYNETWORK_C
#define PLAYNETWORK_C

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "playnetwork.h"

#include "../client/c/network/game.c"
#include "../common/c/data/process_board.c"
#include "../common/c/rules/pieces.c"
#include "../common/c/game/version1.c"
#include "../common/c/rules/check_and_pat.c"
#include "../client/c/game/game_process2.h"
#include "../client/c/network/network.c"


//variable to use
struct construction constr;
GtkEntry * Ori_Coord;
GtkEntry * New_Coord;
char * o;
char * n;
//GtkLabel *rules;
GtkLabel *info;
int clicked_for_change =0;

void change_clicked(GtkButton *button, gpointer user_data)
{
    clicked_for_change = 1;
}
void game_process_robot();

void sendto_network(struct to_play * playing,GtkEntry * Ori, GtkEntry * New)
{
    //initialize data
    //constr = playing->constr;
    /*Ori_Coord = Ori;
    New_Coord= New;*/
    //o = (char *) gtk_entry_get_text(Ori_Coord);
    //n = (char *) gtk_entry_get_text(New_Coord);
    //rules = playing->Rules;
    //info = playing->Info;
    //update_board(constr);
    
    //(info,"waiting for connexion...");
    start_network();
    game_process_robot();
}
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
    if ((x=='W' || x=='S') && y==0)
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

void game_process_robot()
{
    wait_game_output();

    pthread_mutex_lock(&mutex_output);
    last_side_output = 1;

    //Start
    switch (*buf_output)
    {
        case ('0'):
            
            
            //setting the parameters in ../../serveur/game.c
            king_x_me=4;
            king_y_me=0;
            king_x_other=4;
            king_y_other=7;
            color=0;
            
            pthread_mutex_unlock(&mutex_output);
            //a voir si il faut init un board de base ?
            
            //struct Piece* board = init_board()
            board = char_to_board((buf_output+1));
            //remplacer
            gtk_label_set_text(info,"The connexion was successfull ! You are playing blacks");
            
            update_board(constr);
            pthread_mutex_lock(&mutex_input);
            //****
            
            gtk_label_set_text(info,"It is now your turn\n");
            while(1)
            {
                if(clicked_for_change)
                {
                    board = throw_action(board);
                    clicked_for_change= 0;
                    continue;
                }
            }
            
            if (board==NULL)
            {
                break;
            }
            
            //****
            constr.board = board;
            update_board(constr);
            
            last_side_input = 1;
            //filling the buffer with the board
            *buf_input = '3';
            strcpy((buf_input+1), board_to_char(board));
            *(buf_input+65) = 0;
            pthread_mutex_unlock(&mutex_input);
            break;
            
            
        case ('1'):
            
            //the parameters in ../../serveur/game.c
            king_x_me=4;
            king_y_me=7;
            king_x_other=4;
            king_y_other=0;
            color=1;
            
            pthread_mutex_unlock(&mutex_output);
            
            //****
            
            gtk_label_set_text(info,"The connexion was successfull ! You are playing whites, it is your turn to play");
        
            board = init_board();
            
            //****
            constr.board = board;
            update_board(constr);
            
            pthread_mutex_lock(&mutex_input);
            
            last_side_input = 1;
            
            while(1)
            {
                if(clicked_for_change)
                {
                    board = throw_action(board);
                    clicked_for_change= 0;
                    continue;
                }
            }
            
            if (board==NULL)
            {
                break;
            }
            
            //****
            constr.board = board;
            update_board(constr);
            
            //filling the buffer with the board
            *buf_input = '0';
            strcpy((buf_input+1), board_to_char(board));
            *(buf_input+65) = 0;
            pthread_mutex_unlock(&mutex_input);
            
            //demander de taper l'info en utilisant les fonctions de anna? car là pas fait?
            //l'info a-t-elle été envoyée au serveur là ?
            
            break;
            
            
        case('3'):
            //****
            gtk_label_set_text(info,"Your turn now");
            
            board = char_to_board((buf_output+1));
            
            //if the king of the other player changed, then we change it there to
            change_king_other(buf_output+65);
            //or just take the 4 other args if we only want to move pieces
            pthread_mutex_unlock(&mutex_output);
            
            update_board(constr);
            
            pthread_mutex_lock(&mutex_input);
            last_side_input = 1;
            
            while(1)
            {
                if(clicked_for_change)
                {
                    board = throw_action(board);
                    clicked_for_change= 0;
                    continue;
                }
            }
            
            if (board==NULL)
            {
                break;
            }
            
            constr.board = board;
            display_board_special(board);
            
            if (winner==1)
            {
                gtk_label_set_text(info,"Your turn now");
                *buf_input = '6';
                *(buf_input+1)='1';
                *(buf_input+2)='0';
            }
            else
            {
                *buf_input = '3';
                strcpy((buf_input+1), board_to_char(board));
                *(buf_input+65) = 0;
            }
            pthread_mutex_unlock(&mutex_input);
            break;

        case ('4'):
            //**** AFFICHER UNE FENETRE DE DEMANDE
            printf(BLU"The other player has a request \n"reset);
            
            pthread_mutex_unlock(&mutex_output);
            //****
                printf("The player wants to end the game \n");
                printf("If you agree [a], your game doesn't go anywhere so you will both win\n");
                printf("If you disagree [d], the player will need to continue or to abort and then, let you win \n");
                printf("Enter [a] if you want to end the game, Enter [d] otherwise\n");
            //****
                
                pthread_mutex_lock(&mutex_input);
                last_side_input = 1;
            
            //****
                char * rep = malloc(sizeof(char));
                scanf(" %c",rep);
            //****
            
                *buf_input='5';
                if (*rep=='a')
                {
                    *(buf_input+1)='1';
                }
                else
                {
                    *(buf_input+1)='0';
                }
            //****
            gtk_label_set_text(info,"thank you for your answer it was sended...");
            free(rep);
            pthread_mutex_unlock(&mutex_input);
            
            break;
            
        case ('5'):
            pthread_mutex_unlock(&mutex_output);
            
            //****
            gtk_label_set_text(info,"the other player has answered");
            
            last_side_input = 1;
            pthread_mutex_lock(&mutex_input);
            if (*(buf_output+1)=='1')
            {
                //****
                printf(GRN"The game was finshed by resignation \n"reset);
                printf(MAG"you can try to make another one to be more successfull\n"reset);
                //****
                
                *buf_input='6';
                *(buf_input+1)='1';
                *(buf_input+2)='1';
                winner=1;
            }
            else
            {
                //****
                printf(RED"The player didn't accept to cancel the game\n"reset);
                printf("Do you want to abort? If you abort you will be considered as the looser\n");
                printf("enter 'y' to abort, enter 'n' to continue\n");
                //****
                //****
                char * rep = malloc(sizeof(char));
                scanf(" %c",rep);
                //****
                
                if (*rep=='y')
                {
                    *(buf_input)='6';
                    *(buf_input+1)='1';
                    *(buf_input+2)='1';
                    looser=1;
                }
                else
                {
                    while(1)
                    {
                        if(clicked_for_change)
                        {
                            board = throw_action(board);
                            clicked_for_change= 0;
                            continue;
                        }
                    }
                    if (board==NULL)
                    {
                        break;
                    }
                    if (winner==1)
                    {
                        *buf_input = '6';
                        *(buf_input+1)='1';
                        *(buf_input+2)='0';
                    }
                    else
                    {
                        *buf_input = '3';
                        strcpy((buf_input+1), board_to_char(board));
                        *(buf_input+65) = 0;
                    }
                }
                free(rep);
            }
            pthread_mutex_unlock(&mutex_input);
            
        
            
            //if other cases of request they need to be there
            break;
        case ('6'):
            pthread_mutex_unlock(&mutex_output);
            
            //****
            printf(RED"The game is over\n"reset);
            
            if (*(buf_output+1)=='1')
            {
                if (*(buf_output+2)=='1')
                {
                    //****
                    printf(GRN"YOU ARE THE WINNER!\n"reset);
                    winner=1;
                }
                else
                {
                    //****
                    printf(RED"SORRY YOU HAVE LOST\n"reset);
                    looser=1;
                }
            }
            return;
        
        default:
            pthread_mutex_unlock(&mutex_output);
            break;
    }

    game_process_robot();
}


//when the party is on, when the player receives an message
//the player needs to play back so we
int errgestion(struct Piece* board,int x,int y)
{
    
    if(board[(y-1)*8+(x+1)].color != color && board[(y-1)*8+(x+1)].type != NONE)
       {
           //****
           gtk_label_set_text(info,"this isn't your chess piece to move");
           return 1;
       }
    return 0;
    
}

//handelling stalemate case
void stalemate2()
{
    //TODO VERIFY IF PORSSIBLE
    
    gtk_label_set_text(info,"your request was just sended to your opponent");
    *buf_input = '4';
    *(buf_output+1) = '0';
    //*(buf_output+2) = '0';
    //winner=1;
    //+ajouter le fait d'arreter l communication et dire que cette personne perd
}
//hadeling withdraw case
void withdraw2()
{
    *buf_input = '6';
    *(buf_output+1) = '1';
    *(buf_output+2) = '1';
    looser = 1;
    //+ajouter le fait d'arreter l communication et dire que cette personne perd
}

//same principle as withdraw but just it is detected to be an impossible function
void pat2()
{
    *buf_input = '6';
    *(buf_output+1) = '1';
    *(buf_output+2) = '1';
    winner=1;
}


//interpet is valid move, saying what is the issue depending on the output of ISVALID
int valid_interpret(int a)
{
    //change every afficahge
    //Making sure the move is valid
    switch (a)
    {
        case 0:
            gtk_label_set_text(info,"This move isn't possible for that chess piece, please check the rules.");
            break;
        case 2:
            gtk_label_set_text(info,"This move isn't possible because one or some coordinates are out of bounds");
            break;
        case 3:
            gtk_label_set_text(info,"This move isn't possible because the chess piece on the destination coordinates is already yours!");
            break;
        case 4:
            gtk_label_set_text(info,"This move isn't possible because there aren't any chess pieces to move!");
            break;
        case 1:
            break;
        default:
            gtk_label_set_text(info,"undifined erro\n");
            a=-1;
            break;
            
    }
    return a;
}

//when the other king has moved, changing it's coordinates
void change_king_other(char * buf)
{
    if (buf[0]==1)
    {
        king_x_other=buf[1];
        king_y_other=buf[2];
    }
    return;
}

//to play the main part of the game, using marie's rules, converting it to the network format
struct Piece * throw_action(struct Piece * board)
{
    int ok=1;
    char x_char='A';
    int x=0;
    int y=0;
    char des_x_char='A';
    int des_x=0;
    int des_y=0;
           
    // this part it checking if the basic coordinates are valid to play
    while (ok)
    {
        //begin to read coordinates
        int a=0;
        
        
        //_____________________________________________________________
        //entering the coordinates_____________________________________
        //_____________________________________________________________
        //printf(" it's your turn! \n\n");
        //______________________________________________________________________________________________________

        //Get original coordinates
        
        gtk_label_set_text(info,"Please enter the original coordinates of the chess piece you want to move (ex: A3) :");
        //ici recupérer les infos
        //
        o = (char *) gtk_entry_get_text(Ori_Coord);
        n = (char *) gtk_entry_get_text(New_Coord);

        x_char = o[0];
        y = o[1];

        des_x_char = n[0];
        des_y = n[1];
        
        while(incorrect_coor(des_x_char,des_y) || incorrect_coor(x_char,y))
        {
            gtk_label_set_text(info,"Oops... you haven't entered correct coordinates please try again \n");
            while(1)
            {
                if(clicked_for_change)
                {
                    board = throw_action(board);
                    clicked_for_change= 0;
                    continue;
                }
            }
            
        }
        //________________________________________________
        //end of entering the cordinates__________________
        //________________________________________________
        
        //modifying the char coordinates to int
        x= (int)x_char -64;
        des_x= (int)des_x_char -64;
        
        //________________________________________________
        //analysing basic possible output_________________
        //________________________________________________
        
        //analysing the withdraw option
        if ( x_char == 'W' && y == 0 && des_x_char == 'W' && des_y == 0)
        {
            last_side_input = 1;
            withdraw2();
            pthread_mutex_unlock(&mutex_input);
            return NULL;
        }

        //analysing the stale mate option
        if(x_char == 'S' && y == 0 && des_x_char == 'S' && des_y == 0)
        {
            last_side_input = 1;
            stalemate2();
            pthread_mutex_unlock(&mutex_input);
            return NULL;
        }
           
        //analysing basics mistakes with isValidMove
        a= valid_interpret(isValidMove(x-1,y-1,des_x-1,des_y-1,board));
        if (a==1 || board[(y-1)*8+(x+1)].color != color)
        {
            gtk_label_set_text(info,"Your move was validated");
            ok=0;
        }
        
        // Impossible move
        if(piece_to_place(king_x_me, king_y_me, board) == 1 )
        {
            gtk_label_set_text(info,"Impossible to move the king as checkmate would be unavoidable");
            ok=1;
        }
               
        if (errgestion(board,x,y))
        {
            ok=1;
        }
    }
    //____________________________________ Game settings _____________________________________________________________

    //kingstatus created in other file
    //Dealling with the Rock
    if( kingstatus == 0 && rock == 1 && board[(y-1)*8+(x-1)].color == color && board[(y-1)*8+(x-1)].type == KING)
    {

        if (isValidMove_Rock( x - 1, y-1, des_x-1, des_y-1, board[(y-1)*8+(x-1)].color, board))
        {
            board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);
            king_x_me = des_x - 1;
            king_y_me = des_y - 1;


            if(piece_to_place(king_x_me, king_y_me, board) == 1)
            {
                    
                board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
                
                gtk_label_set_text(info,"Impossible to move the king as checkmate would be unavoidable, please try another move");
                king_x_me = x - 1;
                king_y_me = y - 1;

                if( x - 1 == 4 && y - 1 == 7)
                {
                     
                    if(des_x - 1 == 6 && des_y - 1 == 7) //little rock
                   {
                    board[color*7*8+7].type = ROOK;
                     board[color*7*8+7].color = color;
                     board[color*7*8+5].type = NONE;
                     board[color*7*8+5].color = 0;
                   }
                   if (des_x - 1 == 2 && des_y - 1 == 7) //big rock
                   {
                     board[color*7*8+0].type = ROOK;
                     board[color*7*8+0].color = color;
                     board[color*7*8+3].type = NONE;
                     board[color*7*8+3].color = 0;
                   }
                 }
                while(1)
                {
                    if(clicked_for_change)
                    {
                        clicked_for_change= 0;
                        return throw_action(board);
                    }
                }
            }
        }
    }
           
    //Move chess piece
    board = pieceMove(x-1 , y-1, des_x-1, des_y-1, board);
    
    //________________________________________________
    //then check for exeptions________________________
    //________________________________________________
    
    //________ King ____________
    //change position of the king to help check/pat/checkmat
    if(board[(y-1)*8+(x-1)].type == KING)
    {
        king_x_me = des_x - 1;
        king_y_me = des_y - 1;
        //variable to create
        rock = 0;
    }
    //___________________________

    //________________________________________________________________________
    //Dealing with impossible move if check mate is not avoidable_____________
    //________________________________________________________________________
    if(piece_to_place(king_x_me, king_y_me, board) == 1 )
    {
        board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
        gtk_label_set_text(info,"Impossible to move the king as checkmate would be unavoidable, pklease try another move");
        

        if(board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
        {
                king_x_me = x - 1;
                king_y_me= y - 1;
        }
        while(1)
        {
            if(clicked_for_change)
            {
                clicked_for_change= 0;
                return throw_action(board);
            }
        }
    }

    //saying if the player created a checkmate
    if (kingcheck_place(king_x_other, king_y_other, des_x-1, des_y-1, board) == 1)
    {
        kingstatus_other = 1;
        gtk_label_set_text(info,"Checkmate for the other king");
        *buf_input = '6';
        *(buf_input+1)='1';
        *(buf_input+2) ='0';
        winner=1;
        
    }

    if (kingcheck_place(king_x_me, king_y_me, des_x-1, des_y-1, board) == 0)
    {
        kingstatus = 0;
    }
    if (check_mat(king_x_other, king_y_other, !color,  board)== 1)
    {
        //modifying winner to detect that the check mate happened
        winner=1;
        return board;
    }
                           
    if(pat(king_x_other, king_y_other, board))
    {
        gtk_label_set_text(info,"It's a draw");
            pat2();
            return NULL;
    }
           
    printf(reset);
        
    gtk_label_set_text(info,"you move was just approved, now wait for the other player to make a move\n");
    return board;
                           
}


//End safety loop guard
#endif
