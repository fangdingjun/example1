#include <gtk/gtk.h>

static GtkBuilder *builder;

int main(int argc, char **argv)
{
	static GtkWidget *win;
	GtkUIManager *ui;
	GError *error = NULL;
	GtkActionGroup *actions;
	GtkWidget *box1;
	GtkWidget *bn;
	GtkWidget *treeview;
    GtkCellRenderer *ren;
    gchar *filename = "bbb.ui";
    
	gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder,filename,&error);
    if (error)
    {
        g_error("error: %s\n",error->message);
        return -1;
    }

    gtk_builder_connect_signals(builder,NULL);
    win = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
    treeview=GTK_WIDGET(gtk_builder_get_object(builder,"treeview1"));

    //ren=gtk_cell_renderer_text_new();
    //g_object_set_data(G_OBJECT(ren),"column","CC");
    //gtk_tree_view_insert_column_with_attributes(treeview,-1,"c1",ren,"value"); 
    //g_signal_connect(win,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show_all(win);

	gtk_main();
	return 0;
}
