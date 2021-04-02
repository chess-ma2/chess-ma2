//____________________________________ Game settings _____________________________________________________________
//Rock
//kingstatus to create
if( (kingstatus == NOTHING && white_rock == CAN_ROCK && board[(y-1)*8+(x-1)].color == color && board[(y-1)*8+(x-1)].type == KING))
{

  if (isValidMove_Rock( x - 1, y-1, des_x-1, des_y-1, board[(y-1)*8+(x-1)].color, board) == 1)
  {   board = pieceMove_Rock(x-1, y-1, des_x-1, des_y-1, board);

      if (player_turn == WHITETURN) {
        king_x_me = des_x - 1;
        king_y_me = des_y - 1;
      }


      if(piece_to_place(king_x_me, king_y_me, board) == 1)
     {
         
      board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
      printf("Impossible move for chessmate is inevitable\n");

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
         //SEND GAME CAUS ROCK WAS MADE
    }
  }
//display_board_special(board);
continue;
}
}
//Other chess piece movements
int possible = isValidMove(x-1, y-1, des_x-1, des_y-1, board); //movement is possible
//int possible = isValidMove(x, y-1, des_x, des_y-1, board); //movement is possible

//printf("%d", possible);
printf(RED);
switch(possible)
{
    case 0:
        printf("This move isn't possible for that chess piece, please check the rules.\n\n");
        break;
    case 2:
        printf("This move isn't possible because one or some coordinates are out of bounds\n\n");
        break;
    case 3:
        printf("This move isn't possible because the chess piece on the destination coordinates is already yours!\n\n");
        break;
    case 4:
        printf("This move isn't possible because there aren't any chess pieces to move!\n\n");
        break;
    case 1:

        //Move chess piece
        board = pieceMove(x-1 , y-1, des_x-1, des_y-1, board);

      //________ King ____________
        if(board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
            {
                king_x_me = des_x - 1;
                king_y_me = des_y - 1;
                //variable to create
                rock = CANT_ROCK;
            }

        //___________________________


        // Impossible move
          if(piece_to_place(king_x_me, king_y_me, board) == 1 )
            {
            board = pieceMove(des_x-1, des_y-1, x-1, y-1, board);
              printf("Impossible to move the king as checkmate would be unavoidable\n");

              if(board[(y-1)*8+(x-1)].type == KING) //change position of the king to help check/pat/checkmat
                {   king_x_me = x - 1;
                    king_y_me= y - 1; }

        //___________________________ Black team's turn
          if(player_turn == BLACKTURN)
            {
            if (kingcheck_place(king_x_other, king_y_other, des_x-1, des_y-1, board) == 1) {
                {kingstatus = CHECK;
                printf("Checkmate for the white king \n");
            }

            if (kingcheck_place(king_x_me, king_y_me, des_x-1, des_y-1, board) == 0)
              black_kingstatus = NOTHING;

            if (check_mat(king_x_other, king_y_other, color,  board)== 1) {
                return
              //return blackT_Vict(player1, player2);
            }
            //lancer le tour de l'autre
          }

          if(pat(king_y_other, king_y_other, board))
            {
            printf(BHGRN "\n It's a draw!! \n" reset);
                //add victory to both of the players
            //update_victory(player1->email);
            //update_victory(player2->email);
              return 0;
            }
}
printf(reset);
display_board_special(board); //print the board after modifications
