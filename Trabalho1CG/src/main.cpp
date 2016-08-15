#include <gtk/gtk.h>

GtkBuilder      *builder; 
 GtkWidget *dialog_add;
 GtkWidget *button_add;

 
// called when window is closed
extern "C" G_MODULE_EXPORT void on_window_main_destroy()
{
    gtk_main_quit();
}

extern "C" G_MODULE_EXPORT void on_button1_clicked()
{
  builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
  dialog_add = GTK_WIDGET(gtk_builder_get_object(builder, "dialog1"));
  
    gtk_window_present(GTK_WINDOW(dialog_add));
    

}

 
int main(int argc, char *argv[])
{
    
    GtkWidget       *window;
     
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    
    gtk_builder_connect_signals(builder, NULL);
    
     button_add = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
 
