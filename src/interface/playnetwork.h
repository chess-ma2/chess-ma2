
void change_clicked(GtkButton *button, gpointer user_data);

void game_process_robot();

void sendto_network(GtkButton *button, gpointer user_data);

void wait_game_output();

int incorrect_coor(char x,int y);

int errgestion(struct Piece* board,int x,int y);

void stalemate2();

void withdraw2();

void pat2();

int valid_interpret(int a);

void change_king_other(char * buf);

struct Piece * throw_action(struct Piece * board);
