#include <gtk/gtk.h>

void on_button_clicked(GtkWidget * button, gpointer data)
{
    GtkWidget *dialog;

    //init dialog
    dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL |
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
            (gchar *) data);
    //show dialog
    gtk_dialog_run(GTK_DIALOG(dialog));

    //close dialog
    gtk_widget_destroy(dialog);
    //	gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkWidget *window,*but;
    GtkWidget *button_o;
    //GtkWidget *button_q;

    GtkWidget *label;
    GtkWidget *view;
    GtkWidget *vbox;
    GtkWidget *frame;
    //init
    gtk_init(&argc, &argv);

    //new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //register function
    g_signal_connect(G_OBJECT(window), "delete_event",
            G_CALLBACK(gtk_main_quit), NULL);

    // destroy events
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    //button
    but=gtk_button_new_with_label("close");
    g_signal_connect_swapped(but,"clicked",G_CALLBACK(gtk_object_destroy),window);

    //set title
    gtk_window_set_title(GTK_WINDOW(window), "Hell World");

    //set border
    gtk_container_set_border_width(GTK_CONTAINER(window), 50);

    //set label
    button_o = gtk_button_new_with_label("Hello world");
    //button_q = gtk_button_new_with_label("quit");

    //call hello func when clicked
    g_signal_connect(G_OBJECT(button_o), "clicked",
            G_CALLBACK(on_button_clicked),
            (gpointer) "Hi How are you?\n");


    //g_signal_connect(G_OBJECT(window), "clicked",
    //		 G_CALLBACK(gtk_main_quit), NULL);


    //add button to top window
    //gtk_container_add(GTK_CONTAINER(window), button_o);
   
    //paned
    //GtkWidget *hpaned=gtk_hpaned_new();
    //GtkWidget *hpaned1=gtk_hpaned_new();
    //label
    label=gtk_label_new("hello,gtk!");
    g_print("hello\n");
    //frame
        frame=gtk_frame_new("f");

    //gtk_paned_pack1(GTK_PANED(hpaned),but,1,0);

    //gtk_paned_pack1(GTK_PANED(hpaned1),button_o,1,0);
    //gtk_paned_pack2(GTK_PANED(hpaned1),label,1,0);

    //gtk_paned_pack2(GTK_PANED(hpaned),hpaned1,1,1);
    vbox=gtk_vbox_new(0,1); 
    //gtk_box_pack_start(GTK_BOX(vbox),frame,TRUE,0,0);
    gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
    view=gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox),button_o,0,0,0);
    gtk_box_pack_start(GTK_BOX(vbox),but,0,0,0);
    //gtk_box_pack_end(GTK_BOX(vbox),view,0,0,0);
    //gtk_container_add(GTK_CONTAINER(frame),hpaned);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    //show windown
    gtk_widget_show_all(window);

    //message loop
    gtk_main();

    return 0;
}
