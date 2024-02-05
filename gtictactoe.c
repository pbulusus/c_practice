#include<gtk/gtk.h>
#include<stdlib.h>

static char mark[] = "X";
char winmsg[] = "Player   has won!";

unsigned short btncount = 0;
short vals[3][3];

GtkGrid* grid;
GtkWindow* window;

void quick_message (GtkWindow* parent, char* message)
{
    GtkAlertDialog* dialog = gtk_alert_dialog_new (message);
    g_signal_connect (dialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
    gtk_alert_dialog_show (dialog, parent);
}

void reset(GtkGrid* grid)
{
    int i, j;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            vals[i][j] = -1;
            gtk_button_set_label(GTK_BUTTON(gtk_grid_get_child_at(grid, i, j)), "-");
        }        
    } 
    btncount = 0;
    mark[0] = 'X';
}

static void mark_tile (GtkWidget* widget, gpointer plocation)
{
    
    GtkButton* button = GTK_BUTTON(widget);

    
    if (gtk_button_get_label(button)[0] != '-')
        return;

    int row = (int)plocation / 3;
    int col = (int)plocation % 3;
    char current = mark[0];

    gtk_button_set_label(button, mark);
    if (mark[0] == 'X')
    {
        mark[0] = 'O';
        vals[row][col] = 3;
    }
    else
    {
        mark[0] = 'X';
        vals[row][col] = 0;
    }
    if(++btncount < 5)
        return;

    short sumrow = 0, sumcol = 0, sumdiag1 = 0, sumdiag2 = 0, i;

    for (i = 0; i < 3; ++i)
    {
        sumrow   += vals[row][i];
        sumcol   += vals[i][col];
        sumdiag1 += vals[i][i];
        sumdiag2 += vals[i][2-i];
    }

    if (sumrow == 0 || sumrow == 9 || sumcol == 0 || sumcol == 9 ||
       (row == col && (sumdiag1 == 0 || sumdiag1 == 9)) ||
       (row == 2 - col && (sumdiag2 == 0 || sumdiag2 == 9)))
    {
        winmsg[7] = current;
        quick_message(GTK_WINDOW(window), winmsg);
        reset(grid);
        return;
    }

    if (btncount == 9)
    {
        quick_message(GTK_WINDOW(window), "No Winner...resetting grid.");
        reset(grid);
    }

}

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget* button;
    /* create a new window, and set its title */
    window = GTK_WINDOW(gtk_application_window_new (app));
    gtk_window_set_title (window, "Tic Tac Toe");

    /* Here we construct the container that is going pack our buttons */
    grid = GTK_GRID(gtk_grid_new ());
    gtk_widget_set_hexpand(GTK_WIDGET(grid), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(grid), TRUE);

    /* Pack the container in the window */
    gtk_window_set_child (window, GTK_WIDGET(grid));

    int i, j;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            button = gtk_button_new_with_label ("-");
            gtk_widget_set_hexpand(GTK_WIDGET(button), TRUE);
            gtk_widget_set_vexpand(GTK_WIDGET(button), TRUE);
            vals[i][j] = -1;
            g_signal_connect (button, "clicked", G_CALLBACK (mark_tile), 3 * i + j);
            gtk_grid_attach (GTK_GRID (grid), button, i, j, 1, 1);
        }
    }

    button = gtk_button_new_with_label ("Reset");
    gtk_widget_set_hexpand(GTK_WIDGET(button), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(button), TRUE);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (reset), grid);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 3);

    /* Place the first button in the grid cell (0, 0), and make it fill
    * just 1 cell horizontally and vertically (ie no spanning)
    */
    gtk_window_present (window);
}

int main (int argc, char **argv)
{
    // setvbuf (stdout, NULL, _IONBF, 0);
    GtkApplication* app;
    int status;

    app = gtk_application_new ("org.gtk.example", 0);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}

// void close_alert(GtkAlertDialog* dialog, GAsyncResult *res, gpointer user_data)
// {
//     GError *err = NULL;
//     int button = gtk_alert_dialog_choose_finish (dialog, res, &err);
//     gtk_window_destroy((GtkWindow*)dialog);
// }

// void quick_message (GtkWindow* parent, char* message)
// {
//     GtkAlertDialog* dialog = gtk_alert_dialog_new (message);
//     const char* buttons[] = {"Cancel", "Proceed"};
//     gtk_alert_dialog_set_detail (dialog, "Contents of the message");
//     gtk_alert_dialog_set_buttons (dialog, buttons);
//     gtk_alert_dialog_set_cancel_button (dialog, 0);   // Cancel is at index 0
//     gtk_alert_dialog_set_default_button (dialog, 1);

//     gtk_alert_dialog_choose  (dialog, parent, NULL, (GAsyncReadyCallback)close_alert, NULL);
// }

    // const char* markup = "<span size=\"30.0pt\">-</span>";
    // GtkWidget*  btn_label;
    

    // int i, j;
    // for (i = 0; i < 3; ++i)
    // {
    //     for (j = 0; j < 3; ++j)
    //     {
    //         button = gtk_button_new_with_label ("-");
    //         gtk_widget_set_hexpand(GTK_WIDGET(button), TRUE);
    //         gtk_widget_set_vexpand(GTK_WIDGET(button), TRUE);
    //         btn_label = gtk_label_new(NULL);
    //         gtk_label_set_markup ((GtkLabel*)btn_label, markup);
    //         gtk_button_set_child(GTK_BUTTON(button), GTK_WIDGET(btn_label));
    //         vals[i][j] = -1;
    //         g_signal_connect (button, "clicked", G_CALLBACK (mark_tile), 3 * i + j);
    //         gtk_grid_attach (GTK_GRID (grid), button, i, j, 1, 1);
    //     }
    // }
