#include <gtk/gtk.h>


//__________ variables
GtkWidget* window1;
GtkWidget* window1st_v_1;
GtkWidget* window2nd_v_1;
GtkWidget* window3rd_v_1;

void first_v_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window1st_v_1);
    gtk_widget_hide(window1);
}

void second_v_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window2nd_v_1);
    gtk_widget_hide(window1);
}

void third_v_start(GtkButton *button, gpointer user_data)
{
    gtk_widget_show(window3rd_v_1);
    gtk_widget_hide(window1);
}


// Main function.
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
    window1 = GTK_WINDOW(gtk_builder_get_object(builder, "window1"));
    window1st_v_1 = GTK_WINDOW(gtk_builder_get_object(builder, "window_1st_Version"));
    window2nd_v_1 = GTK_WINDOW(gtk_builder_get_object(builder, "window_2nd_Version"));
    window3rd_v_1 = GTK_WINDOW(gtk_builder_get_object(builder, "window_3rd_Version"));
    //GtkLabel* WelcomeLabel = GTK_LABEL(gtk_builder_get_object(builder, "WelcomeLabel"));
    GtkButton* first_version = GTK_BUTTON(gtk_builder_get_object(builder, "first_version"));
    GtkButton* second_version = GTK_BUTTON(gtk_builder_get_object(builder, "2ndVersion"));
    GtkButton* third_version = GTK_BUTTON(gtk_builder_get_object(builder, "3rdVersion"));


    // Connects signal handlers.
    g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Version 1
    g_signal_connect(first_version, "clicked", G_CALLBACK(first_v_start), NULL);
    g_signal_connect(window1st_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Version 2
    g_signal_connect(second_version, "clicked", G_CALLBACK(second_v_start), NULL);
    g_signal_connect(window2nd_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Version 3
    g_signal_connect(third_version, "clicked", G_CALLBACK(third_v_start), NULL);
    g_signal_connect(window3rd_v_1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Runs the main loop.
    gtk_main();

    // Exits
    return 0;
}
