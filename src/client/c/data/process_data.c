/**
 * @author Marine
 * @date 25/03/2021
 * @details part made to process the data incoming to the server
 */

#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../rules/pieces.h"



int get_number(int data, int rank)
{
    return (data-(data%rank))/rank;
}

int get_rest(int data, int rank)
{
    return data%rank;
}

//uncodify data form : x/abAB

//x is the code of the data
//__//0 is a move to actualise

//_____//a-first x position
//_____//b-first y position
//_____//A-new x position
//_____//B-new y position

//__//1 is a request from both players

//_____//a-code of the request
//_____//b-code 0 if doesn't need an answer/ 1 if needs an answer
//_____//A-code 0 if not answered/ 1 if this is the repplied data
//_____//B-code 0 if no / 1 if yes (needs to be intialised to -1

//_____//a-code of info (example 0 for player aborted mission)

//uncodifying data and actualising it in board
void uncodify_data(int data,  struct Piece *board)
{
    int code= get_number(data,10000);
    data= get_rest(data,10000);
    
    switch (code)
    {
        case 0:
            int x=get_number(data,1000);
            data= get_rest(data,1000);
            int y=get_number(data,100);
            data= get_rest(data,100);
            int X=get_number(data,10);
            data= get_rest(data,10);
            int Y=data;
            board = pieceMove(x,y,X,Y);
            //display board?
            break;
            
        case 1:
            code= get_number(data,100);
            
            send_request(data,board);
            
    }
}

void send_request(int data,struct Piece * board)
{
    
}
