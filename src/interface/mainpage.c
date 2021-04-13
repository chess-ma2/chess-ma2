#include <gtk/gtk.h>
#include "Local1.h"


//__________ variables
GtkWidget* window1;

//____________________ First Window
// First version window
GtkWidget* window1st_v_1;
// New player n1 first version
GtkWidget* NewPL1_W1;

//______ First Player ________
// Entry for name
GtkEntry * Name_Entry1;
// Entry for Email
GtkEntry * Email_Entry1;
// Entry for password
GtkEntry * Password_Entry1;
// Label to say if accound has been created with success
GtkLabel * Create_account1_yes;

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
  New_player_v1(Name_Entry1, Email_Entry1, Password_Entry1, Create_account1_yes);
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
    gtk_button_set_image(back, Image_back);

    // First player is a new player Window
    NewPL1_W1 = GTK_WIDGET(gtk_builder_get_object(builder, "NewPL1_W1"));

    // Back to first version
    GtkButton* back_w1 = GTK_BUTTON(gtk_builder_get_object(builder, "back_w1"));

    // ButtonImage to go back to first version window
    GtkWidget* Image_back2;
    Image_back2 = gtk_image_new_from_file ("Images/back.png");
    gtk_button_set_image(back_w1, Image_back2);

    // Save new info about player 1
    GtkButton* lock_new1 = GTK_BUTTON(gtk_builder_get_object(builder, "lock_new1"));
    GtkWidget* Image_save;
    Image_save = gtk_image_new_from_file ("Images/save.png");
    gtk_button_set_image(lock_new1, Image_save);

    // Label when info is saved
    Create_account1_yes = GTK_LABEL(gtk_builder_get_object(builder, "create_account1_yes"));



//__________________________________________________________________________________________
    //Exemple for area
    //GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
//__________________________________________________________________________________________

    // Entry for name
    Name_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "name1"));
    // Entry for email
    Email_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "email1"));
    // Entry for password
    Password_Entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "password1"));

    // __________________________________________________________________________________

    //_______ Version 2 _______
    // Button to get to second version
    GtkButton* second_version = GTK_BUTTON(gtk_builder_get_object(builder, "2ndVersion"));


    //________ Version 3 _______
    // Button to get to third version
    GtkButton* third_version = GTK_BUTTON(gtk_builder_get_object(builder, "3rdVersion"));


    // Connects signal handlers.
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

// Example for area
    //g_signal_connect(area, "draw", G_CALLBACK(on_draw), NULL);
//


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

    // Exits
    return 0;
}
