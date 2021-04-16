#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include "Local1.h"

//_____STARTINTITIALISATION___________________________________

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
// Main Page for GAME
GtkWidget* game_v1;
//Login player 1
GtkWidget* LoginAccount;
//Login player 2
GtkWidget* LoginAccount2;


//____Global_Initialization___
// The player structure
struct Player *pl1;
// The player structure
struct Player *pl2;


//______ First Player __create____
// Entry for name
GtkEntry * Name_Entry1;
// Entry for Email
GtkEntry * Email_Entry1;
// Entry for password
GtkEntry * Password_Entry1;
// Label to say if accound has been created with success
GtkLabel * Create_account1_yes;


//______ Second Player ___create___
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

//____________________ Third Window
// third version window
GtkWidget* window3rd_v_1;

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
  * @details Go back to first NEW player of first version's window (new or login)
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

  //sleep before going to player2's window (so user can see success message)
  sleep(1);

  // Show general window for Player 2 (login or new)
  gtk_widget_show(window1_version_PL2);
  gtk_widget_hide(NewPL1_W1);
}
// _____ Player 2 _______createaccount________________________________
/*
 * @author Anna
 * @date 14/04/2021
 * @details Back to main_page from create player 2
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
    //TODO
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
    gtk_widget_hide(window1);
}

 /*
  * @author Marine
  * @date 16/04/2021
  * @details Back to the mainpage from login1
  */
void back_from_login1(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1);
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
    gtk_widget_hide(window1);
}

 /*
  * @author Marine
  * @date 16/04/2021
  * @details Back to the mainpage from login2
  */
void back_from_login2(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1);
    gtk_widget_hide(LoginAccount2);
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

//END CREATING SUB FUNCTIONS___________________________________________________


//_____________________________________________________________________________
//______MAIN FUNCTION _________________________________________________________
//_____________________________________________________________________________
/*
 * @author Anna and Marine the queens
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
    GtkButton* back3 = GTK_BUTTON(gtk_builder_get_object(builder,"back3"));

    // New Player n1 ___________________________________________________________________
    // New Player n°1 button
    //create
    GtkButton* new_player1 = GTK_BUTTON(gtk_builder_get_object(builder, "new_player1"));
    //login
    GtkButton* login1 = GTK_BUTTON(gtk_builder_get_object(builder,"login_1"));

    // ButtonImage to go back to mainpage
    GtkWidget* Image_back;
    Image_back = gtk_image_new_from_file ("Images/back.png");
    GtkWidget* Image_back_bis;
    Image_back_bis = gtk_image_new_from_file ("Images/back.png");
    gtk_button_set_image(back, Image_back_bis);

    // First player is a new player Window
    NewPL1_W1 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL1_W1"));
    // First player exists
    LoginAccount = GTK_WIDGET(gtk_builder_get_object(builder, "LoginAccount"));

    // Back to first version
    GtkButton* back_w1 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w1"));
    GtkButton* back_w3 = GTK_BUTTON(gtk_builder_get_object(builder,"back_w3"));

    // ButtonImage to go back to first version window
    GtkWidget* Image_back2;
    Image_back2 = gtk_image_new_from_file ("Images/back.png");
    GtkWidget* Image_back2_bis;
    Image_back2_bis = gtk_image_new_from_file ("Images/back.png");
    
    gtk_button_set_image(back_w1, Image_back2_bis);
    gtk_button_set_image(back_w3,Image_back2_bis);

    // Save new info about player 1
    GtkButton* lock_new1 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new1"));
    GtkButton* lock_new3 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new3"));
    
    GtkWidget* Image_save;
    GtkWidget* Image_savebis;
    
    Image_save = gtk_image_new_from_file ("Images/save.png");
    Image_savebis = gtk_image_new_from_file ("Images/save.png");
    
    gtk_button_set_image(lock_new1, Image_savebis);
    gtk_button_set_image(lock_new3, Image_savebis); //tochange

    // Label when info is saved
    Create_account1_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account1_yes"));

    //CREATE ACCOUNT
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
    gtk_button_set_image(back2, Image_back);

    // Second player is a new player Window
    NewPL2_W1 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL2_W1"));
    //Second player is not new
    LoginAccount2=GTK_WIDGET(gtk_builder_get_object(builder, "LoginAccount2"));

    // Back to first version
    GtkButton* back_w2 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w2"));
    GtkButton* back_w4 = GTK_BUTTON(gtk_builder_get_object(builder,"back_w4"));

    // Button to go back to first version window
    gtk_button_set_image(back_w2, Image_back2);
    gtk_button_set_image(back_w4, Image_back2);

     //LOGIN ACCOUNT
    //entry for mail
    Email_Log2 = GTK_ENTRY(gtk_builder_get_object(builder,"email4"));
    //entry for password
    Password_Log2= GTK_ENTRY(gtk_builder_get_object(builder,"password4"));

    // Save new info about player 2
    GtkButton* lock_new2 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new2"));
    gtk_button_set_image(lock_new2, Image_save);
    GtkButton* lock_new4 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new4"));
    gtk_button_set_image(lock_new4,Image_save); //tochange

    // Label when info is saved
    Create_account2_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account2_yes"));

    //  Game  _______________________________________________________________________
    GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));

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

    //___________ Version 1 __________________________________________________
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

    // Player 2____________________

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
    g_signal_connect(area, "draw", G_CALLBACK(on_draw), NULL);


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
