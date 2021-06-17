#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include "Local1.c"
#include "Local1_init.c"
#include "added_functions4local.c"
#include "playnetwork.c"
#include "thirdV_init.c"
#include "thirdversion.c"
#ifndef MAINPAGE_C
#define MAINPAGE_C

//_____INTITIALISATION___________________________________
//__________ variables
GtkWidget* window1;

//____________________ First Window
// First version window -> Player 1
GtkWidget* window1st_v_1;
// New player n1 first version
GtkWidget* NewPL1_W1;
// First version window -> Player 2
GtkWidget* window1_version_PL2;
// New player n2 first version
GtkWidget* NewPL2_W1;
//Login player 1
GtkWidget* LoginAccount;
//Login player 2
GtkWidget* LoginAccount2;

//____Global_Initialization___
// The player structure
struct Player *pl1;
// The player structure
struct Player *pl2;
// Player Turn
enum turn *player_turn;


//______ First Player ________
// Entry for name
GtkEntry * Name_Entry1;
// Entry for Email
GtkEntry * Email_Entry1;
// Entry for password
GtkEntry * Password_Entry1;
// Label to say if accound has been created with success
GtkLabel * Create_account1_yes;

//______ Second Player ________
// Entry for name
GtkEntry * Name_Entry2;
// Entry for Email
GtkEntry * Email_Entry2;
// Entry for password
GtkEntry * Password_Entry2;
// Label to say if accound has been created with success
GtkLabel * Create_account2_yes;

//___Login 1_________________

//Entry for Email
GtkEntry * Email_Log1;
//Entry for Password
GtkEntry * Password_Log1;
//Reusing structure player 1 or 2 depending


//___Login 2_________________

//Entry for Email
GtkEntry * Email_Log2;
//Entry for Password
GtkEntry * Password_Log2;
//Reusing structure player 1 or 2 depending

//____________________ Second Window
// second version window
GtkWidget* window2nd_v_1;

GtkWidget* window_login_N;
GtkWidget* window_newplayer_N;

//______ Network Player ________
// Entry for name
GtkEntry * Name_EntryN;
// Entry for Email
GtkEntry * Email_EntryN;
// Entry for password
GtkEntry * Password_EntryN;
// Entry for Email
GtkEntry * Email_EntryN2;
// Entry for password
GtkEntry * Password_EntryN2;
// Label to say if accound has been created with success
GtkLabel * Create_accountN_yes;
//Entry for Email
GtkEntry * Email_LogN;
//Entry for Password
GtkEntry * Password_LogN;
struct for_clicked *move_str2;
// Entry for original coordinates
GtkEntry * Ori_CoordN;
// Entry for new coordinates
GtkEntry * New_CoordN;

GtkWidget* LoginAccountN;

GtkWidget* gamenetwork;

GtkButton* WithdrawN;
struct added_F *added_structN;
GtkButton* StalemateN;
GtkWidget* Game_OverN;

//

// ____________________ Third Window _______
// ________ Player vs AI ___________________
// third version window
GtkWidget* window3rd_v_1;
// Button for new player
GtkWidget* new_player3_1;
// Back n°1
GtkWidget* back_3_1;
// Button to log in
GtkWidget* login_3_1;

// ___________________________
// New player
GtkWidget* NewPL_3;
// Back n°2
GtkWidget* back_3_2;
// Name
GtkEntry* name3_1;
// Email
GtkEntry* email3_1;
// Password
GtkEntry* password3_1;
// Lock
GtkButton* lock_new_3_1;
// Create account
GtkLabel* create_account3_1_yes;

// ___________________________
//Login player
GtkWidget* LoginAccount3_1;
// Email
GtkEntry* email3_2;
// Password
GtkEntry* password3_2;
// Lock
GtkButton* lock_new_3_2;
// Back n°3
GtkWidget* back_3_3;
// Chose AI
GtkWidget * window_chose_AI;

//____ GAME (Local) ____________
// Main Page for GAME
GtkWidget* game_v1;
// Entry for original coordinates
GtkEntry * Ori_Coord;
// Entry for new coordinates
GtkEntry * New_Coord;
struct for_clicked *move_str;
// Button for Withdraw
GtkButton* WithdrawB;
// Button for Stalemate
GtkButton* StalemateB;
struct added_F *added_struct;
// End of game window
GtkWidget* Game_Over;

//____ GAME (Player vs AI) ____________
struct for_clicked *move_str3;
struct added_F *added_struct3;
// Main Page for GAME
GtkWidget* game_v3;
// Entry for original coordinates
GtkEntry * oriCOORD_3;
// Entry for new coordinates
GtkEntry * newCOORD_3;
// Button for Withdraw
GtkButton* withdraw_3;


//__________________________________________________________________
//END_____INITIALISATION____________________________________________
//__________________________________________________________________

/*
 * @author Anna
 * @date 10/04/2021
 * @details Show first version's window
*/
void first_v_start(GtkButton *button, gpointer user_data)
{ gtk_widget_show(window1st_v_1);
  gtk_widget_hide(window1);         }


/*
  * @author Anna
  * @date 10/04/2021
  * @details Back to the mainpage
*/
void back_from_first(GtkButton *button, gpointer user_data)
{   gtk_widget_show(window1);
    gtk_widget_hide(window1st_v_1); }

/*
  * @author Anna
  * @date 10/04/2021
  * @details Show first player n1's window (new or login)
*/
void first_player_new(GtkButton *button, gpointer user_data)
{   gtk_widget_show(window1st_v_1);
    gtk_widget_hide(window1);       }

/*
  * @author Anna
  * @date 10/04/2021
  * @details Go back to first player of first version's window (new or login)
*/
void back_from_first_double(GtkButton *button, gpointer user_data)
{   gtk_widget_hide(NewPL1_W1);
    gtk_widget_show(window1st_v_1); }

/*
  * @author Anna
  * @date 10/04/2021
  * @details Show new first player n1's window
*/
void new_player1CB(GtkButton *button, gpointer user_data)
{   gtk_widget_hide(window1st_v_1);
    gtk_widget_show(NewPL1_W1); }

/*
 * @author Anna
 * @date 13/04/2021
 * @details Create new first player for first version
 */
void save_pl1(GtkButton *button, gpointer user_data)
{
  // New Player subfunction into .db
  struct Player *res = New_player_v1(Name_Entry1, Email_Entry1, Password_Entry1, Create_account1_yes, NewPL1_W1, LoginAccount);
  if (res != NULL) {
    pl1 = res;
    // Show transition window
    transition_page(NewPL1_W1, window1_version_PL2);
  }
}


// _____ Player 2 ____________________________________________________________
/*
 * @author Anna
 * @date 14/04/2021
 * @details Back to main_page from player 2
*/

void back_to_main(GtkButton *button, gpointer user_data)
{     gtk_widget_show(window1);
      gtk_widget_hide(window1_version_PL2); }

/*
  * @author Anna
  * @date 14/04/2021
  * @details Go back to first player of first version's window (new or login)
*/
void back_pl2(GtkButton *button, gpointer user_data)
{   gtk_widget_hide(NewPL2_W1);
    gtk_widget_show(window1_version_PL2); }

 /*
  * @author Anna
  * @date 14/04/2021
  * @details Show new second player's window
  */
void new_pl2(GtkButton *button, gpointer user_data)
{   gtk_widget_hide(window1_version_PL2);
    gtk_widget_show(NewPL2_W1); }


/*
 * @author Anna
 * @date 14/04/2021
 * @details Create new second player for first version
 */
void save_pl2(GtkButton *button, gpointer user_data)
{
  // New Player subfunction into .db
  struct Player *res = New_player_v1(Name_Entry2, Email_Entry2, Password_Entry2, Create_account2_yes, NewPL2_W1, LoginAccount2);

  if (res != NULL) {
    pl2 = res;
    gtk_window_fullscreen(GTK_WINDOW(game_v1));
    gtk_widget_hide(NewPL2_W1);
    gtk_widget_show(game_v1);
    // Start Game
    struct to_play *playing = user_data;
    move_str->Window = game_v1;
    init_gtk(pl1, pl2, playing->constr, playing->Rules, playing->Info, playing->turn, move_str, Game_Over);
    init_added_structures(move_str->player1, move_str->player2, added_struct, Game_Over);

  }
}

//____________________________________________________________________________
/*
 * @author Marine
 * @date 16/04/2021
 * @details Show the login1 window
 */
void login1_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(LoginAccount);
    gtk_widget_hide(window1st_v_1);
}

/*
 * @author Marine
 * @date 18/04/2021
 * @details connects player 1 to database
 */
void connect1(GtkButton *button, gpointer user_data)
{
    pl1 =findplayer(Email_Log1,Password_Log1);
    if (pl1!=NULL)
    {
        //gtk_widget_show(transition1);
        transition_page(LoginAccount, window1_version_PL2);

    }
    else
    {
        gtk_widget_show(window1st_v_1);
    }
        gtk_widget_hide(LoginAccount);
}

 /*
  * @author Marine
  * @date 16/04/2021
  * @details Back to the mainpage from login1
  */
void back_from_login1(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1st_v_1);
    gtk_widget_hide(LoginAccount);
}

//____________________________________________________________________________
/*
 * @author Marine
 * @date 16/04/2021
 * @details Show the login2 window
 */
void login2_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(LoginAccount2);
    gtk_widget_hide(window1_version_PL2);
}
/*
 * @author Marine
 * @date 18/04/2021
 * @details connects player 2 to database
 */
void connect2(GtkButton *button, gpointer user_data)
{

    pl2 =findplayer(Email_Log2,Password_Log2);
    if (pl2!=NULL)
    {
        gtk_widget_show(game_v1); // Show GAME
        gtk_window_fullscreen(GTK_WINDOW(game_v1));
        // _________ Play Game _______________
        struct to_play *playing = user_data;
        move_str->Window = game_v1;
        init_gtk(pl1, pl2, playing->constr, playing->Rules, playing->Info, playing->turn, move_str, Game_Over);
        init_added_structures(move_str->player1, move_str->player2, added_struct, Game_Over);
    }
    else
    {
        gtk_widget_show(window1_version_PL2);
    }
        gtk_widget_hide(LoginAccount2);
}

 /*
  * @author Marine
  * @date 16/04/2021
  * @details Back to the mainpage from login2
  */
void back_from_login2(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1_version_PL2);
    gtk_widget_hide(LoginAccount2);
}

/*
 * @author Anna
 * @date 23/05/2021
 * @details Back to main menu from first version of game
 */
void playagain(GtkButton *button, gpointer user_data)
{
    gtk_widget_hide(Game_Over);
    gtk_widget_show(window1);

}



//____________________________________________________________________________
/*
 * @author Anna
 * @date 10/04/2021
 * @details Show second version's window
*/
void second_v_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window2nd_v_1);
    gtk_widget_hide(window1);
}

/*
  * @author Anna
  * @date 10/04/2021
  * @details Back to the mainpage
*/
void back_from_second(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1);
    gtk_widget_hide(window2nd_v_1);
}

/*
 * @author Marine
 * @date 13/06/2021
 * @details login with network
*/
void login_N(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window_login_N);
    gtk_widget_hide(window2nd_v_1);
}

/*
  * @author Marine
  * @date 13/06/2021
  * @details new player with network
*/
void window_playerN(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window_newplayer_N);
    gtk_widget_hide(window2nd_v_1);
}

/*
  * @author Marine
  * @date 13/06/2021
  * @details back from new player in network
*/
void backNN(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window2nd_v_1);
    gtk_widget_hide(window_newplayer_N);
}

/*
 * @author Marine
 * @date 13/06/2021
 * @details back from login in n
*/
void backLN(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window2nd_v_1);
    gtk_widget_hide(window_login_N);
}

/*
 * @author Marine
 * @date 13/06/2021
 * @details connecting from NET in new player
*/
void connectNN(GtkButton *button, gpointer user_data)
{
    struct Player *res = New_player_v1(Name_EntryN, Email_EntryN, Password_EntryN, Create_accountN_yes, window_newplayer_N, LoginAccountN);
    // creating a random player 2 information
    /*pl2->name = "Other";
    pl2->email = "networkother";
    strcpy((char *)&(pl2->password),"dnjsoivjno7896vgxui");*/

    if (res != NULL)
    {
        pl1 = res;
        gtk_widget_show(gamenetwork);
        gtk_window_fullscreen(GTK_WINDOW(gamenetwork));
        gtk_widget_hide(LoginAccountN);

        struct to_play *playing = user_data;
        sendto_network(playing, move_str2->Ori_Coord,move_str2->New_Coord);
    }
}

/*
* @author Marine
* @date 13/06/2021
* @details connecting from NET in login*/

void connectLN(GtkButton *button, gpointer user_data)
{
    pl1 = findplayer(Email_EntryN,Password_EntryN);

    // creating a player 2 with predifined informations
    /*pl2->name = "Other";
    pl2->email = "networkother";
    strcpy((char *)&(pl2->password),"dnjsoivjno7896vgxui");*/

    if (pl1!=NULL)
    {
        gtk_widget_show(gamenetwork);
        struct to_play *playing = user_data;
        sendto_network(playing, move_str2->Ori_Coord,move_str2->New_Coord);
        //transition_page(LoginAccountN, window2nd_v_1);
    }
    else
    {
        gtk_widget_show(window2nd_v_1);
    }
        gtk_widget_hide(LoginAccountN);
}


//____________________________________________________________________________
/*
 * @author Anna
 * @date 16/06/2021
 * @details Show third version's window
 */
void third_v_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window3rd_v_1);
    gtk_widget_hide(window1);
}

 /*
  * @author Anna
  * @date 16/06/2021
  * @details Back to the mainpage
  */
void back_from_third(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1);
    gtk_widget_hide(window3rd_v_1);
}

/*
 * @author Anna
 * @date 16/06/2021
 * @details Show MiniMax window
 */
void show_minimax(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(game_v3); // Show GAME
    gtk_window_fullscreen(GTK_WINDOW(game_v3));
    // _________ Play Game _______________
    struct to_play *playing = user_data;
    move_str3->Window = game_v3;
    move_str3->AI = MINIMAX;
    init_gtk3(pl1, pl2, playing->constr, playing->Rules, playing->Info, playing->turn, move_str3, Game_Over);
    init_added_structures(move_str3->player1, move_str3->player2, added_struct, Game_Over);
    gtk_widget_hide(window_chose_AI);
}

/*
 * @author Anna
 * @date 16/06/2021
 * @details Show MiniMax window
 */
void show_monte(GtkButton *button, gpointer user_data)
{
  gtk_widget_show(game_v3); // Show GAME
  gtk_window_fullscreen(GTK_WINDOW(game_v3));
  // _________ Play Game _______________
  struct to_play *playing = user_data;
  move_str3->Window = game_v3;
  move_str3->AI = MONTECARLO;
  init_gtk3(pl1, pl2, playing->constr, playing->Rules, playing->Info, playing->turn, move_str3, Game_Over);
  init_added_structures(move_str3->player1, move_str3->player2, added_struct, Game_Over);
  gtk_widget_hide(window_chose_AI);
}

/*
 * @author Anna
 * @date 16/06/2021
 * @details Back from AI list
 */
void back_AI_list(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window3rd_v_1);
    gtk_widget_hide(window_chose_AI);
}


/*
  * @author Anna
  * @date 16/06/2021
  * @details Show new players window
*/
void new_player_3(GtkButton *button, gpointer user_data)
{   gtk_widget_hide(window3rd_v_1);
    gtk_widget_show(NewPL_3); }

  /*
   * @author Anna
   * @date 14/06/2021
   * @details Create new player for third version
   */
void save_pl3(GtkButton *button, gpointer user_data)
{
  // New Player subfunction into .db
  struct Player *res = New_player_v1(name3_1, email3_1, password3_1, create_account3_1_yes, NewPL_3, LoginAccount3_1);
  if (res != NULL) {
    pl1 = res;
    gtk_widget_hide(NewPL_3);
    gtk_widget_show(window_chose_AI);
  }
}

/*
  * @author Anna
  * @date 16/06/2021
 * @details Show login window
 */
void to_login3_1(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(LoginAccount3_1);
    gtk_widget_hide(window3rd_v_1);
}
/*
 * @author Anna
 * @date 16/06/2021
 * @details Connect player to database
 */
void connect3_1(GtkButton *button, gpointer user_data)
{

    pl1 = findplayer(email3_2,password3_2);
    if (pl1!=NULL)
    {
        gtk_widget_show(window_chose_AI);
    }
    else
    {
        gtk_widget_show(window3rd_v_1);
    }
        gtk_widget_hide(LoginAccount3_1);
}

 /*
  * @author Anna
  * @date 16/06/2021
  * @details Back to the mainpage from login
  */
void back_from_login3_2(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window3rd_v_1);
    gtk_widget_hide(LoginAccount3_1);
}

/*
 * @author Anna
 * @date 16/06/2021
 * @details Back to the mainpage from new player
 */
void back_from_login3_1(GtkButton *button, gpointer user_data)
{
   gtk_widget_show(window3rd_v_1);
   gtk_widget_hide(NewPL_3);
}
/*
 * @author Anna and Marine the queen
 * @date 10/04/2021
 * @details Main function
 */
int main (int argc, char *argv[])
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Loads the UI description and builds the UI.
    // (Exits if an error occurs.)
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "main_page.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Gets the widgets.
    // Main Window
    window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

    // First Version Window
    window1st_v_1 = GTK_WIDGET(gtk_builder_get_object(builder, "window_1st_Version"));

    // Second Version Window
    window2nd_v_1 = GTK_WIDGET(gtk_builder_get_object(builder, "window_2nd_Version"));

    // Third Version Window
    window3rd_v_1 = GTK_WIDGET(gtk_builder_get_object(builder, "window_3rd_Version"));

    //__________________ Version 1  Widgets that are needed ____________________________
    // Button to get to first version
    GtkButton* first_version = GTK_BUTTON(gtk_builder_get_object(builder, "first_version"));

    // Button to go back to main page
    GtkButton* back = GTK_BUTTON(gtk_builder_get_object(builder, "back"));

    // New Player n1 ___________________________________________________________________
    // New Player n°1 button
    //create
    GtkButton* new_player1 = GTK_BUTTON(gtk_builder_get_object(builder, "new_player1"));
    //login
    GtkButton* login1 = GTK_BUTTON(gtk_builder_get_object(builder,"login_1"));

    // ButtonImage to go back to mainpage
    gtk_button_set_image(back, gtk_image_new_from_file ("Images/back.png"));

    // First player is a new player Window
    NewPL1_W1 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL1_W1"));

    // First player exists
    LoginAccount = GTK_WIDGET(gtk_builder_get_object(builder, "LoginAccount"));

    // Back to first version
    GtkButton* back_w1 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w1"));
    GtkButton* back_w3 = GTK_BUTTON(gtk_builder_get_object(builder,"back_w3"));

    // ButtonImage to go back to first version window
    gtk_button_set_image(back_w1, gtk_image_new_from_file ("Images/back.png"));
    gtk_button_set_image(back_w3, gtk_image_new_from_file ("Images/back.png"));

    // Save new info about player 1
    GtkButton* lock_new1 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new1"));

    GtkButton* lock_new3 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new3"));

    gtk_button_set_image(lock_new1, gtk_image_new_from_file ("Images/save.png"));
    gtk_button_set_image(lock_new3, gtk_image_new_from_file ("Images/save.png"));

    // Label when info is saved
    Create_account1_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account1_yes"));

    // Entry for name
    Name_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "name1"));
    // Entry for email
    Email_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "email1"));
    // Entry for password
    Password_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "password1"));

    //LOGIN ACCOUNT
    //entry for mail
    Email_Log1 = GTK_ENTRY(gtk_builder_get_object(builder,"email3"));
    //entry for password
    Password_Log1= GTK_ENTRY(gtk_builder_get_object(builder,"password3"));




    // Player n°2  _______________________________________________________________________
    // General window (login or new player)
    window1_version_PL2 = GTK_WIDGET(gtk_builder_get_object(builder, "window1_version_PL2"));

    // Button to go back to main page
    GtkButton* back2 = GTK_BUTTON(gtk_builder_get_object(builder, "back2"));

    // New Player n2 ___________________________________________________________________
    // New Player n°2 button
    GtkButton* new_player2 = GTK_BUTTON(gtk_builder_get_object(builder, "new_player2"));
    GtkButton* login_2 = GTK_BUTTON(gtk_builder_get_object(builder, "login_2"));

    // ButtonImage to go back to mainpage
    gtk_button_set_image(back2, gtk_image_new_from_file ("Images/back.png"));

    // First player is a new player Window
    NewPL2_W1 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL2_W1"));
    //Second player is not new
    LoginAccount2=GTK_WIDGET(gtk_builder_get_object(builder, "LoginAccount2"));

    // Back to first version
    GtkButton* back_w2 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w2"));
    GtkButton* back_w4 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w4"));
    //Second player is not new
    LoginAccount2=GTK_WIDGET(gtk_builder_get_object(builder, "LoginAccount2"));

    // Button to go back to first version window
    gtk_button_set_image(back_w2, gtk_image_new_from_file ("Images/back.png"));
    gtk_button_set_image(back_w4, gtk_image_new_from_file ("Images/back.png"));

    // Save new info about player 2
    GtkButton* lock_new2 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new2"));
    gtk_button_set_image(lock_new2, gtk_image_new_from_file ("Images/save.png"));
    GtkButton* lock_new4 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new4"));
    gtk_button_set_image(lock_new4,gtk_image_new_from_file ("Images/save.png"));

    // Label when info is saved
    Create_account2_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account2_yes"));

    // Entry for name
    Name_Entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "name2"));
    // Entry for email
    Email_Entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "email2"));
    // Entry for password
    Password_Entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "password2"));

    //LOGIN ACCOUNT
   //entry for mail
   Email_Log2 = GTK_ENTRY(gtk_builder_get_object(builder,"email4"));
   //entry for password
   Password_Log2= GTK_ENTRY(gtk_builder_get_object(builder,"password4"));

    //  Game  _______________________________________________________________________
    GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
    game_v1 = GTK_WIDGET(gtk_builder_get_object(builder, "game_v1"));
    GtkFixed *fixed = GTK_FIXED(gtk_builder_get_object(builder, "paned1"));
    GtkLabel *Info = GTK_LABEL(gtk_builder_get_object(builder, "Info"));
    GtkLabel *rulesL = GTK_LABEL(gtk_builder_get_object(builder, "rulesL"));
    printRulesLabel(rulesL);
    GtkLabel *turn = GTK_LABEL(gtk_builder_get_object(builder, "turn"));
    Ori_Coord = GTK_ENTRY(gtk_builder_get_object(builder,"oriCOORD"));
    New_Coord = GTK_ENTRY(gtk_builder_get_object(builder,"newCOORD"));
    GtkButton * click_coordinates = GTK_BUTTON(gtk_builder_get_object(builder, "click_coordinates"));
    gtk_button_set_image(click_coordinates,gtk_image_new_from_file ("Images/save.png"));

    // withdraw
    WithdrawB = GTK_BUTTON(gtk_builder_get_object(builder, "withdraw"));
    gtk_button_set_image(WithdrawB, gtk_image_new_from_file ("Images/Withdraw.png"));
    StalemateB = GTK_BUTTON(gtk_builder_get_object(builder, "StalemateB"));
    gtk_button_set_image(StalemateB, gtk_image_new_from_file ("Images/Stalemate.png"));

    // 2 modes
    GtkButton * normal_mode = GTK_BUTTON(gtk_builder_get_object(builder, "NormalMode"));
    GtkButton * epita_mode = GTK_BUTTON(gtk_builder_get_object(builder, "EPITAMode"));


    // Create widgets -> button board
    struct construction constr;
    constr.board = init_board();
    // Create board and put into fixed
    constr.ImageBoard = malloc(64 * sizeof(GtkWidget));
    constr.fixed = fixed;
    int x_co = 56; //original coordinates
    int y_co = 90; //original coordinates

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
      constr.ImageBoard[i*8+j] = gtk_image_new();
      gtk_widget_set_size_request (constr.ImageBoard[i*8+j],60,60);
      gtk_fixed_put (constr.fixed, constr.ImageBoard[i*8+j], x_co + 15, y_co + 15);
      x_co += 60;
      }
      x_co = 56;
      y_co += 60;
    }

    // End of game
    Game_Over = GTK_WIDGET(gtk_builder_get_object(builder, "Game_Over"));
    GtkButton * play_again = GTK_BUTTON(gtk_builder_get_object(builder, "play_again"));
    GtkButton * exit_game = GTK_BUTTON(gtk_builder_get_object(builder, "exit_game"));


    // __________________________________________________________________________________

    //_______ Version 2 _______
    // Button to get to second version
    GtkButton* second_version = GTK_BUTTON(gtk_builder_get_object(builder, "2ndVersion"));

    //create
    GtkButton* newplayerN = GTK_BUTTON(gtk_builder_get_object(builder, "newplayerN"));
    //login
    GtkButton* loginN = GTK_BUTTON(gtk_builder_get_object(builder,"loginN"));
    GtkButton* backN = GTK_BUTTON(gtk_builder_get_object(builder,"backN"));

    gtk_button_set_image(backN, gtk_image_new_from_file ("Images/back.png"));
    GtkButton* backN2 = GTK_BUTTON(gtk_builder_get_object(builder,"backNlog"));

    // ButtonImage to go back to mainpage
    gtk_button_set_image(backN2, gtk_image_new_from_file ("Images/back.png"));

    // First player is a new player Window
    window_newplayer_N = GTK_WIDGET(gtk_builder_get_object(builder, "window_newplayer_N"));
    window_login_N =GTK_WIDGET(gtk_builder_get_object(builder, "window_login_N"));

    // First player exists
    LoginAccountN = GTK_WIDGET(gtk_builder_get_object(builder, "LoginAccountN"));

    // Back to 2nd version
    GtkButton* back_wN = GTK_BUTTON(gtk_builder_get_object(builder, "back_wN"));
    GtkButton* back_wN2 = GTK_BUTTON(gtk_builder_get_object(builder,"back_wN2"));

    // ButtonImage to go back to first version window
    gtk_button_set_image(back_wN, gtk_image_new_from_file ("Images/back.png"));
    gtk_button_set_image(back_wN2, gtk_image_new_from_file ("Images/back.png"));

    // Save new info about player 1
    GtkButton* lock_newN = GTK_BUTTON(gtk_builder_get_object(builder, "lock_newN"));

    GtkButton* lock_newN2 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_newN2"));

    gtk_button_set_image(lock_newN, gtk_image_new_from_file ("Images/save.png"));
    gtk_button_set_image(lock_newN2, gtk_image_new_from_file ("Images/save.png"));

    // Label when info is saved
    Create_account1_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account1_yes"));

    // Entry for name
    Name_EntryN = GTK_ENTRY(gtk_builder_get_object(builder, "nameN"));
    // Entry for email
    Email_EntryN = GTK_ENTRY(gtk_builder_get_object(builder, "emailN"));
    // Entry for password
    Password_EntryN = GTK_ENTRY(gtk_builder_get_object(builder, "passwordN"));

    //LOGIN ACCOUNT
    //entry for mail
    Email_LogN = GTK_ENTRY(gtk_builder_get_object(builder,"emailN"));
    //entry for password
    Password_LogN= GTK_ENTRY(gtk_builder_get_object(builder,"passwordN"));

    //__________G_A_M_E_____N_E_T_W_O_R_K____________________________
    gamenetwork = GTK_WIDGET(gtk_builder_get_object(builder, "gamenetwork"));

    GtkDrawingArea* areaN = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "areaN"));
    GtkFixed *fixedN = GTK_FIXED(gtk_builder_get_object(builder, "panedN"));
    GtkLabel *InfoN = GTK_LABEL(gtk_builder_get_object(builder, "InfoN"));
    GtkLabel *rulesN = GTK_LABEL(gtk_builder_get_object(builder, "rulesN"));
    printRulesLabel(rulesN);
    GtkLabel *turnN = GTK_LABEL(gtk_builder_get_object(builder, "turnN"));
    Ori_CoordN = GTK_ENTRY(gtk_builder_get_object(builder,"oriCOORDN"));
    New_CoordN = GTK_ENTRY(gtk_builder_get_object(builder,"newCOORDN"));
    GtkButton * click_coordinatesN = GTK_BUTTON(gtk_builder_get_object(builder, "click_coordinatesN"));
    gtk_button_set_image(click_coordinatesN,gtk_image_new_from_file ("Images/save.png"));


    // withdraw
    WithdrawN = GTK_BUTTON(gtk_builder_get_object(builder, "withdrawN"));
    gtk_button_set_image(WithdrawN, gtk_image_new_from_file ("Images/Withdraw.png"));
    StalemateN = GTK_BUTTON(gtk_builder_get_object(builder, "StalemateN"));
    gtk_button_set_image(StalemateN, gtk_image_new_from_file ("Images/Stalemate.png"));

    // Create widgets -> button board
    struct construction constrN;
    constrN.board = init_board();
    // Create board and put into fixed
    constrN.ImageBoard = malloc(64 * sizeof(GtkWidget));
    constrN.fixed = fixed;
    int x_coN = 56; //original coordinates
    int y_coN = 90; //original coordinates

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
      constrN.ImageBoard[i*8+j] = gtk_image_new();
      gtk_widget_set_size_request (constrN.ImageBoard[i*8+j],60,60);
      gtk_fixed_put (constrN.fixed, constrN.ImageBoard[i*8+j], x_coN + 15, y_coN + 15);
      x_coN += 60;
      }
      x_coN = 56;
      y_coN += 60;
    }

    // End of game
    Game_OverN = GTK_WIDGET(gtk_builder_get_object(builder, "Game_OverN"));
    GtkButton * play_againN = GTK_BUTTON(gtk_builder_get_object(builder, "play_againN"));
    GtkButton * exit_gameN = GTK_BUTTON(gtk_builder_get_object(builder, "exit_gameN"));


    // __________________________________________________________________________________
    //________ Version 3 _______
    pl2 = makeRobot();

    // Button to get to third version
    GtkButton* third_version = GTK_BUTTON(gtk_builder_get_object(builder, "3rdVersion"));
    // When clicked go to new player page
    GtkButton* new_player3_1 = GTK_BUTTON(gtk_builder_get_object(builder, "new_player3_1"));
    //login
    GtkButton* login_3_1 = GTK_BUTTON(gtk_builder_get_object(builder,"login_3_1"));
    // Back button
    GtkButton* back_3_1 = GTK_BUTTON(gtk_builder_get_object(builder,"back_3_1"));
    // ButtonImage to go back to mainpage
    gtk_button_set_image(back_3_1, gtk_image_new_from_file ("Images/back.png"));

    // new player Window
    NewPL_3 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL_3"));

    // login window
    LoginAccount3_1 = GTK_WIDGET(gtk_builder_get_object(builder, "LoginAccount3_1"));

    // Save new info about player
    GtkButton* lock_new_3_2 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new_3_2"));
    GtkButton* lock_new_3_1 = GTK_BUTTON(gtk_builder_get_object(builder,"lock_new_3_1"));

    // ButtonImage to go back to first version window
    gtk_button_set_image(lock_new_3_2, gtk_image_new_from_file ("Images/save.png"));
    gtk_button_set_image(lock_new_3_1, gtk_image_new_from_file ("Images/save.png"));

    // Back to main page
    GtkButton* back_3_2 = GTK_BUTTON(gtk_builder_get_object(builder, "back_3_2"));
    GtkButton* back_3_3 = GTK_BUTTON(gtk_builder_get_object(builder, "back_3_3"));

    gtk_button_set_image(back_3_3, gtk_image_new_from_file ("Images/back.png"));
    gtk_button_set_image(back_3_2, gtk_image_new_from_file ("Images/back.png"));

    // Label when info is saved
    create_account3_1_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account3_1_yes"));

    // Chose AI
    // new AI list Window
    window_chose_AI = GTK_WIDGET(gtk_builder_get_object(builder, "window_chose_AI"));
    // minimax
    GtkButton* chose_minimax = GTK_BUTTON(gtk_builder_get_object(builder,"chose_minimax"));
    // back
    GtkButton* back_3_AI = GTK_BUTTON(gtk_builder_get_object(builder,"back_3_AI"));
    gtk_button_set_image(back_3_AI, gtk_image_new_from_file ("Images/back.png"));
    // montecarlo
    GtkButton* chose_mt = GTK_BUTTON(gtk_builder_get_object(builder,"chose_mt"));


    // Entry for name
    name3_1 = GTK_ENTRY(gtk_builder_get_object(builder, "name3_1"));
    // Entry for email
    email3_1 = GTK_ENTRY(gtk_builder_get_object(builder, "email3_1"));
    // Entry for password
    password3_1 = GTK_ENTRY(gtk_builder_get_object(builder, "password3_1"));

    //LOGIN ACCOUNT
    //entry for mail
    email3_2 = GTK_ENTRY(gtk_builder_get_object(builder,"email3_2"));
    //entry for password
    password3_2 = GTK_ENTRY(gtk_builder_get_object(builder,"password3_2"));

    //  Game  _______________________________________________________________________
    GtkDrawingArea* area_3 = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area_3"));
    game_v3 = GTK_WIDGET(gtk_builder_get_object(builder, "game_v3"));
    GtkFixed *paned1_3 = GTK_FIXED(gtk_builder_get_object(builder, "paned1_3"));
    GtkLabel *Info_3 = GTK_LABEL(gtk_builder_get_object(builder, "Info_3"));
    GtkLabel *rulesL_3 = GTK_LABEL(gtk_builder_get_object(builder, "rulesL_3"));
    printRulesLabel(rulesL_3);
    GtkLabel *turn_3 = GTK_LABEL(gtk_builder_get_object(builder, "turn_3"));
    oriCOORD_3 = GTK_ENTRY(gtk_builder_get_object(builder,"oriCOORD_3"));
    newCOORD_3 = GTK_ENTRY(gtk_builder_get_object(builder,"newCOORD_3"));
    GtkButton * click_coordinates_3 = GTK_BUTTON(gtk_builder_get_object(builder, "click_coordinates_3"));
    gtk_button_set_image(click_coordinates_3, gtk_image_new_from_file ("Images/save.png"));

    // withdraw
    withdraw_3 = GTK_BUTTON(gtk_builder_get_object(builder, "withdraw_3"));
    gtk_button_set_image(withdraw_3, gtk_image_new_from_file ("Images/Withdraw.png"));

    // Create widgets -> button board
    struct construction constr3;
    constr3.board = init_board();
    // Create board and put into fixed
    constr3.ImageBoard = malloc(64 * sizeof(GtkWidget));
    constr3.fixed = paned1_3;
    x_co = 56; //original coordinates
    y_co = 90; //original coordinates

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
      constr3.ImageBoard[i*8+j] = gtk_image_new();
      gtk_widget_set_size_request (constr3.ImageBoard[i*8+j],60,60);
      gtk_fixed_put (constr3.fixed, constr3.ImageBoard[i*8+j], x_co + 15, y_co + 15);
      x_co += 60;
      }
      x_co = 56;
      y_co += 60;
    }



    //________________________________________________________________________________
    // Connects signal handlers.
    //________________________________________________________________________________


    // Destroy window (main page)
    g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //___________ Version 1 _________________________________________________________
    struct to_play playing;
    playing.constr = constr;
    playing.Rules = rulesL;
    playing.Info = Info;
    playing.turn = turn;

    // Got to first version
    g_signal_connect(first_version, "clicked", G_CALLBACK(first_v_start), NULL);
    // Destroys .exe when first version window is closed
    g_signal_connect(window1st_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Destroys .exe when new first player first version window is closed
    g_signal_connect(NewPL1_W1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Go back to mainpage
    g_signal_connect(back, "clicked", G_CALLBACK(back_from_first), NULL);
    // First Player is New player -> go to said page
    g_signal_connect(new_player1, "clicked", G_CALLBACK(new_player1CB), NULL);
    // Destroys .exe when first player (new) of first version window is closed
    g_signal_connect(new_player1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Back to first player of first window (new or login)
    g_signal_connect(back_w1, "clicked", G_CALLBACK(back_from_first_double), NULL);
    // Click on New Player 1 -> Save info and create player in db
    g_signal_connect(lock_new1, "clicked", G_CALLBACK(save_pl1), NULL);

    //LOGIN PLAYER 1
    // Back to second player of first window (new or login)
    g_signal_connect(back_w3, "clicked", G_CALLBACK(back_from_login1), NULL);
    //goes to login n1
    g_signal_connect(login1, "clicked", G_CALLBACK(login1_start), NULL);
    // Destroys .exe when first player (new) of first version window is closed
    g_signal_connect(login1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(lock_new3, "clicked", G_CALLBACK(connect1), NULL);

    // Player 2_________________________

    // Destroys .exe when first version window is closed for player 2 (new or login)
    g_signal_connect(window1_version_PL2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Destroys .exe when new first player first version window is closed
    g_signal_connect(NewPL2_W1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Destroys .exe when new first player login account is closed
    g_signal_connect(LoginAccount, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Go back to mainpage
    g_signal_connect(back2, "clicked", G_CALLBACK(back_to_main), NULL);
    // Second Player is New player -> go to said page
    g_signal_connect(new_player2, "clicked", G_CALLBACK(new_pl2), NULL);
    // Back to second player of first window (new or login)
    g_signal_connect(back_w2, "clicked", G_CALLBACK(back_pl2), NULL);
    // Click on New Player 2 -> Save info and create player in db
    g_signal_connect(lock_new2, "clicked", G_CALLBACK(save_pl2), &playing);

    //LOGIN player 2
    // Back to second player of first window (new or login)
    g_signal_connect(back_w4, "clicked", G_CALLBACK(back_from_login2), NULL);
    //goes to login n2
    g_signal_connect(login_2, "clicked", G_CALLBACK(login2_start), NULL);
    // Destroys .exe when first player (new) of first version window is closed
    g_signal_connect(login_2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Click on New Player 2 -> Save info and create player in db
    g_signal_connect(lock_new4, "clicked", G_CALLBACK(connect2), &playing);


    // Destroys .exe when new first player login account is closed
    g_signal_connect(LoginAccount, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Destroys .exe when new first player login account 2 is closed
    g_signal_connect(LoginAccount2, "destroy", G_CALLBACK(gtk_main_quit), &playing);


    // Game ___________________________________________________________
    // Destroys .exe when game first version window is closed
    g_signal_connect(game_v1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Draw Chessboard
    g_signal_connect(area, "draw", G_CALLBACK(on_draw), &constr);

    // Structure for Movements
    player_turn = malloc(sizeof(enum turn));
    * player_turn = WHITETURN;
    move_str = malloc(sizeof(struct for_clicked));
    move_str->Ori_Coord = Ori_Coord;
    move_str->New_Coord = New_Coord;
    move_str->constr = constr;
    move_str->player_turn = player_turn;
    move_str->constr.type = NORMAL;

    // Structure for Stalemate and Withdraw
    added_struct = malloc(sizeof(struct added_F));
    added_struct->player_turn = player_turn;
    added_struct->Window = game_v1;

    g_signal_connect(click_coordinates, "clicked", G_CALLBACK(click4move), move_str);
    // Goes to withdraw function
    g_signal_connect(WithdrawB, "clicked", G_CALLBACK(withdraw_2), added_struct);
    // Goes to Stalemate function
    g_signal_connect(StalemateB, "clicked", G_CALLBACK(stalemate_2), added_struct);
    // Normal Mode
    g_signal_connect(epita_mode, "clicked", G_CALLBACK(changepita), move_str);
    // Epita Mode
    g_signal_connect(normal_mode, "clicked", G_CALLBACK(changenormal), move_str);


    // End of Game
    // Destroys .exe when window is closed
    g_signal_connect(Game_Over, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(play_again, "clicked", G_CALLBACK(playagain), NULL);
    g_signal_connect(exit_game, "clicked", G_CALLBACK(exitgame), NULL);


    //___________ Version 2 _________________________________________________________
    // Got to second version
    struct to_play playingN;
    playingN.constr = constrN;
    playingN.Rules = rulesN;
    playingN.Info = InfoN;
    playingN.turn = turnN;

    g_signal_connect(second_version, "clicked", G_CALLBACK(second_v_start), NULL);
    g_signal_connect(backN, "clicked", G_CALLBACK(back_from_second), NULL);
    g_signal_connect(newplayerN, "clicked", G_CALLBACK(window_playerN), NULL);
    g_signal_connect(loginN, "clicked", G_CALLBACK(login_N), NULL);
    g_signal_connect(back_wN , "clicked", G_CALLBACK(backLN), NULL);
    g_signal_connect(back_wN2, "clicked", G_CALLBACK(backNN), NULL);

    // Entry for name
    Name_EntryN = GTK_ENTRY(gtk_builder_get_object(builder, "nameN"));
    // Entry for email
    Email_EntryN = GTK_ENTRY(gtk_builder_get_object(builder, "emailN"));
    // Entry for password
    Password_EntryN = GTK_ENTRY(gtk_builder_get_object(builder, "passwordN"));
    // Entry for email
    Email_EntryN2 = GTK_ENTRY(gtk_builder_get_object(builder, "emailN2"));
    // Entry for password
    Password_EntryN2 = GTK_ENTRY(gtk_builder_get_object(builder, "passwordN2"));

    g_signal_connect(lock_newN , "clicked", G_CALLBACK(connectLN), NULL);

    g_signal_connect(lock_newN2, "clicked", G_CALLBACK(connectNN), NULL);

    // Game _network__________________________________________________________
    // Destroys .exe when game first version window is closed
    g_signal_connect(gamenetwork, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Draw Chessboard
    g_signal_connect(areaN, "draw", G_CALLBACK(on_draw), &constr);

    // Structure for Movements
    move_str2 = malloc(sizeof(struct for_clicked));
    move_str2->Ori_Coord = Ori_CoordN;
    move_str2->New_Coord = New_CoordN;
    move_str2->constr = constrN;
    move_str2->player_turn = player_turn;

    // Structure for Stalemate and Withdraw
    added_structN = malloc(sizeof(struct added_F));
    added_structN->player_turn = player_turn;
    added_structN->Window = gamenetwork;

    g_signal_connect(click_coordinatesN, "clicked", G_CALLBACK(change_clicked), move_str2);
    // Goes to withdraw function
    g_signal_connect(WithdrawN, "clicked", G_CALLBACK(withdraw_2), added_struct);
    // Goes to Stalemate function
    g_signal_connect(StalemateN, "clicked", G_CALLBACK(stalemate_2), added_struct);

    // End of Game
    // Destroys .exe when window is closed
    g_signal_connect(Game_OverN, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(play_againN, "clicked", G_CALLBACK(playagain), NULL);
    g_signal_connect(exit_gameN, "clicked", G_CALLBACK(exitgame), NULL);
    // Destroys .exe when second version window is closed
    g_signal_connect(window2nd_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //___________ Version 3 _________________________________________________________
    struct to_play playing3;
    playing3.constr = constr3;
    playing3.Rules = rulesL_3;
    playing3.Info = Info_3;
    playing3.turn = turn_3;
    // Got to third version
    g_signal_connect(third_version, "clicked", G_CALLBACK(third_v_start), NULL);
    // Destroys .exe when third version window is closed
    g_signal_connect(window3rd_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // New Player
    // Destroys .exe when new first player first version window is closed
    g_signal_connect(NewPL_3, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Go back to mainpage
    g_signal_connect(back_3_1, "clicked", G_CALLBACK(back_from_third), NULL);
    // First Player is New player -> go to said page
    g_signal_connect(new_player3_1, "clicked", G_CALLBACK(new_player_3), NULL);
    // Back to first player of first window (new or login)
    g_signal_connect(back_3_2, "clicked", G_CALLBACK(back_from_login3_1), NULL);
    // Click on New Player 1 -> Save info and create player in db
    g_signal_connect(lock_new_3_1, "clicked", G_CALLBACK(save_pl3),  &playing3);

    // Login PLAYER
    // Back to second player of first window (new or login)
    g_signal_connect(back_3_2, "clicked", G_CALLBACK(back_from_login3_2), NULL);
    // goes to login
    g_signal_connect(login_3_1, "clicked", G_CALLBACK(to_login3_1), NULL);
    // Destroys .exe when window is closed
    g_signal_connect(LoginAccount3_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(lock_new_3_2, "clicked", G_CALLBACK(connect3_1),  &playing3);

    // Chose AI
    // Destroys .exe when AI list window is closed
    g_signal_connect(window_chose_AI, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Back to first window (new or login)
    g_signal_connect(back_3_AI, "clicked", G_CALLBACK(back_AI_list), NULL);
    // MiniMax is chosen
    g_signal_connect(chose_minimax, "clicked", G_CALLBACK(show_minimax), &playing3);
    // Monte Carlo is chosen
    g_signal_connect(chose_mt, "clicked", G_CALLBACK(show_monte), &playing3);

    // Game ___________________________________________________________
    // Destroys .exe when game first version window is closed
    g_signal_connect(game_v3, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Draw Chessboard
    g_signal_connect(area_3, "draw", G_CALLBACK(on_draw), &constr3);

    // Structure for Movements
  //  player_turn = malloc(sizeof(enum turn));
  //  * player_turn = WHITETURN;
    move_str3 = malloc(sizeof(struct for_clicked));
    move_str3->Ori_Coord = oriCOORD_3;
    move_str3->New_Coord = newCOORD_3;
    move_str3->constr = constr3;
    move_str3->player_turn = player_turn;
    move_str3->constr.type = NORMAL;

    // Structure for Stalemate and Withdraw
    added_struct3 = malloc(sizeof(struct added_F));
    added_struct3->player_turn = player_turn;
    added_struct3->Window = game_v3;

    g_signal_connect(click_coordinates_3, "clicked", G_CALLBACK(click4move_3), move_str3);
    // Goes to withdraw function
    g_signal_connect(withdraw_3, "clicked", G_CALLBACK(withdraw_2), added_struct3);



    // Runs the main loop.
    gtk_main();


    //Free what needs to be freed
    //free(pl1);
    //free(move_str);

    // Exits
    return 0;
}

#endif
