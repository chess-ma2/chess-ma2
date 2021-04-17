#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include "Local1.c"
#ifndef MAINPAGE_C
#define MAINPAGE_C

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

//____ GAME ____________
// Main Page for GAME
GtkWidget* game_v1;

//______ First Player ________
// Entry for name
GtkEntry * Name_Entry1;
// Entry for Email
GtkEntry * Email_Entry1;
// Entry for password
GtkEntry * Password_Entry1;
// Label to say if accound has been created with success
GtkLabel * Create_account1_yes;
// The player structure
struct Player *pl1;

//_________ Transition ___________________________
// Transition Window
GtkWidget* transition1;

//______ Second Player ________
// Entry for name
GtkEntry * Name_Entry2;
// Entry for Email
GtkEntry * Email_Entry2;
// Entry for password
GtkEntry * Password_Entry2;
// Label to say if accound has been created with success
GtkLabel * Create_account2_yes;
// The player structure
struct Player *pl2;

//____________________ Second Window
// second version window
GtkWidget* window2nd_v_1;

//____________________ Third Window
// third version window
GtkWidget* window3rd_v_1;

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
  pl1 = New_player_v1(Name_Entry1, Email_Entry1, Password_Entry1, Create_account1_yes);

  // Show transition window
  gtk_widget_show(transition1);
  gtk_widget_hide(NewPL1_W1);
}

// _____ TRANSITION ____________________________________________________________
/*
 * @author Anna
 * @date 15/04/2021
 * @details From transition window to player n2's window
*/
void go_2_player2(GtkButton *button, gpointer user_data)
{
  // Show general window for Player 2 (login or new)
  gtk_widget_show(window1_version_PL2);
  gtk_widget_hide(transition1);
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
  pl2 = New_player_v1(Name_Entry2, Email_Entry2, Password_Entry2, Create_account2_yes);
  // Start Game
  gtk_widget_hide(NewPL2_W1);
  gtk_widget_show(game_v1);
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

//____________________________________________________________________________
/*
 * @author Anna
 * @date 10/04/2021
 * @details Show third version's window
 */
void third_v_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window3rd_v_1);
    gtk_widget_hide(window1);
}

 /*
  * @author Anna
  * @date 10/04/2021
  * @details Back to the mainpage
  */
void back_from_third(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1);
    gtk_widget_hide(window3rd_v_1);
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
    GtkButton* new_player1 = GTK_BUTTON(gtk_builder_get_object(builder, "new_player1"));

    // ButtonImage to go back to mainpage
    GtkWidget* Image_back;
    Image_back = gtk_image_new_from_file ("Images/back.png");
    GtkWidget* Image_back_bis;
    Image_back_bis = gtk_image_new_from_file ("Images/back.png");
    gtk_button_set_image(back, Image_back_bis);

    // First player is a new player Window
    NewPL1_W1 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL1_W1"));

    // Back to first version
    GtkButton* back_w1 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w1"));

    // ButtonImage to go back to first version window
    GtkWidget* Image_back2;
    Image_back2 = gtk_image_new_from_file ("Images/back.png");
    GtkWidget* Image_back2_bis;
    Image_back2_bis = gtk_image_new_from_file ("Images/back.png");
    gtk_button_set_image(back_w1, Image_back2_bis);

    // Save new info about player 1
    GtkButton* lock_new1 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new1"));
    GtkWidget* Image_save;
    GtkWidget* Image_savebis;
    Image_save = gtk_image_new_from_file ("Images/save.png");
    Image_savebis = gtk_image_new_from_file ("Images/save.png");
    gtk_button_set_image(lock_new1, Image_savebis);

    // Label when info is saved
    Create_account1_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account1_yes"));

    // Entry for name
    Name_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "name1"));
    // Entry for email
    Email_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "email1"));
    // Entry for password
    Password_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "password1"));

    // Transition ______________________________________________________________________
    // Window
    transition1 = GTK_WIDGET(gtk_builder_get_object(builder, "transition1"));
    // Button to go 2nd player's page
    GtkButton* go22 = GTK_BUTTON(gtk_builder_get_object(builder, "go22"));



    // Player n°2  _______________________________________________________________________
    // General window (login or new player)
    window1_version_PL2 = GTK_WIDGET(gtk_builder_get_object(builder, "window1_version_PL2"));

    // Button to go back to main page
    GtkButton* back2 = GTK_BUTTON(gtk_builder_get_object(builder, "back2"));

    // New Player n2 ___________________________________________________________________
    // New Player n°2 button
    GtkButton* new_player2 = GTK_BUTTON(gtk_builder_get_object(builder, "new_player2"));

    // ButtonImage to go back to mainpage
    gtk_button_set_image(back2, Image_back);

    // First player is a new player Window
    NewPL2_W1 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL2_W1"));

    // Back to first version
    GtkButton* back_w2 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w2"));

    // Button to go back to first version window
    gtk_button_set_image(back_w2, Image_back2);

    // Save new info about player 2
    GtkButton* lock_new2 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new2"));
    gtk_button_set_image(lock_new2, Image_save);

    // Label when info is saved
    Create_account2_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account2_yes"));

    // Entry for name
    Name_Entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "name2"));
    // Entry for email
    Email_Entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "email2"));
    // Entry for password
    Password_Entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "password2"));

    //  Game  _______________________________________________________________________
    GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
    game_v1 = GTK_WIDGET(gtk_builder_get_object(builder, "game_v1"));
    GtkFixed *fixed = GTK_FIXED(gtk_builder_get_object(builder, "paned1"));

    // Create widgets -> button board
    struct construction constr;
    constr.board = init_board();
    constr.Bboard = malloc(64 * sizeof(GtkWidget));
    constr.ImageBoard = malloc(64 * sizeof(GtkWidget));
    constr.fixed = fixed;

    for (size_t i = 0; i < 64; i++) {
      constr.Bboard[i] = gtk_button_new();
      constr.ImageBoard[i] = gtk_image_new();
    }

    // __________________________________________________________________________________

    //_______ Version 2 _______
    // Button to get to second version
    GtkButton* second_version = GTK_BUTTON(gtk_builder_get_object(builder, "2ndVersion"));


    //________ Version 3 _______
    // Button to get to third version
    GtkButton* third_version = GTK_BUTTON(gtk_builder_get_object(builder, "3rdVersion"));

    //________________________________________________________________________________
    // Connects signal handlers.
    //________________________________________________________________________________


    // Destroy window (main page)
    g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //___________ Version 1 _________________________________________________________
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

    // Transition _________________________
    // Destroys .exe when transition window is closed
    g_signal_connect(transition1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // When ok clicked go to player n°2 page
    g_signal_connect(go22, "clicked", G_CALLBACK(go_2_player2), NULL);

    // Player 2_________________________

    // Destroys .exe when first version window is closed for player 2 (new or login)
    g_signal_connect(window1_version_PL2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Destroys .exe when new first player first version window is closed
    g_signal_connect(NewPL2_W1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Go back to mainpage
    g_signal_connect(back2, "clicked", G_CALLBACK(back_to_main), NULL);
    // Second Player is New player -> go to said page
    g_signal_connect(new_player2, "clicked", G_CALLBACK(new_pl2), NULL);
    // Back to second player of first window (new or login)
    g_signal_connect(back_w2, "clicked", G_CALLBACK(back_pl2), NULL);
    // Click on New Player 2 -> Save info and create player in db
    g_signal_connect(lock_new2, "clicked", G_CALLBACK(save_pl2), NULL);

    // Game ___________________________________________________________
    // Destroys .exe when game first version window is closed
    g_signal_connect(game_v1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Draw Chessboard
    g_signal_connect(area, "draw", G_CALLBACK(on_draw), &constr);


    //___________ Version 2 _________________________________________________________
    // Got to second version
    g_signal_connect(second_version, "clicked", G_CALLBACK(second_v_start), NULL);
    // Destroys .exe when second version window is closed
    g_signal_connect(window2nd_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //___________ Version 3 _________________________________________________________
    // Got to third version
    g_signal_connect(third_version, "clicked", G_CALLBACK(third_v_start), NULL);
    // Destroys .exe when third version window is closed
    g_signal_connect(window3rd_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Runs the main loop.
    gtk_main();

    //Free what needs to be freed
    free(pl1);

    // Exits
    return 0;
}

#endif
