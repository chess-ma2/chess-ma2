/**
 * @author Marine
 * @date Start 2/04/2021
 * @details process
 */


void wait_game_output();

int incorrect_coor(char x,int y);

void game_process();

struct Piece * throw_action(struct Piece* board);

int errgestion(struct Piece* board,int x,int y);

void stalemate2();

void withdraw2();

void change_king_other(char * buf);

int valid_interpret(int a);


