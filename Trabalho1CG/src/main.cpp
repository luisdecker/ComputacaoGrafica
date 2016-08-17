#include <gtkmm/builder.h>
#include <gtkmm/application.h>
#include "view/MainWindow.cpp"


#include <iostream>

int main( int argc, char * argv[] ) {




	std::cout << "INICIANDO PROGRAMA\n";

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "org.gtkmm.example" );

	std::cout << "Criou Aplicacao\n";

	//Aloca um ponteiro para um mainwindow
	MainWindow * mainWindow = NULL;
	std::cout << "Alocou ponteiro\n";


	//Cria o objeto a partir do XLM do GLADE
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file( "../glade/window_main.glade" );
	std::cout << "Parseou o XLM\n";



	builder->get_widget_derived( "window_main", mainWindow );
	std::cout << "get_derived\n";


	/*Puta gambiarra de testes
	std::cout << "Entrando na sessao gambiarra" << std::endl;

	ObjectFile of;
	Ponto ponto( "Ponto", set2DPoint( 1, 1 ) );
	Reta reta( "Reta", set2DPoint( 1, 3 ), set2DPoint( 3, 3 ) );
	of.inserirObjeto( &ponto );
	of.inserirObjeto( &reta );
	mainWindow->atualizaObjectFile( &of );
	std::cout << "Saindo da sessao gambiarra\n";
	/*Deleta pelo amor*/

	app->run( *mainWindow );

	return 0;


}

// #include <iostream>
// #include <gtk/gtk.h>
//
//
// GtkBuilder      *builder;
//  GtkWidget *dialog_add;
//  GtkWidget *button_add;
//  GtkWidget *button_cancel_add;
//  GtkWidget *button_ok_add;
//  GtkWidget *tabs;
//  GtkWidget *input_name;
//
//  extern "C" G_MODULE_EXPORT void on_btn_cancel_clicked(){
//
//   std::cout << "clicado" << std::endl;
//
// }
//
//  extern "C" G_MODULE_EXPORT void on_btn_on_clicked(){
//
//   std::cout << "clicado" << std::endl;
//
// }
//
// // called when window is closed
// extern "C" G_MODULE_EXPORT void on_window_main_destroy()
// {
//     gtk_main_quit();
// }
//
// extern "C" G_MODULE_EXPORT void on_button1_clicked()
// {
//
//   builder = gtk_builder_new();
//     gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
//   dialog_add = GTK_WIDGET(gtk_builder_get_object(builder, "diag_incl_obj"));
// //       gtk_window_set_deletable(GTK_WINDOW(dialog_add),true);
//
//     tabs = GTK_WIDGET(gtk_builder_get_object(builder, "notebook1"));
//
//     input_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));
//      button_cancel_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cancel"));
//      button_ok_add  = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ok"));
//
//      g_object_unref(builder);
//
//       gint result = gtk_dialog_run (GTK_DIALOG (dialog_add));
//   switch (result)
//   {
//     case GTK_RESPONSE_OK:
//
//
//
//       std::cout <<gtk_notebook_get_current_page(GTK_NOTEBOOK(tabs))<<std::endl;
//
//        std::cout << "deu ok" <<std::endl;
//
//        break;
//      case GTK_RESPONSE_CANCEL:
//        std::cout << "deu cancel" <<std::endl;
//        break;
//   }
// gtk_widget_destroy (dialog_add);
//
// }
//
// int main(int argc, char *argv[])
// {
//
//     GtkWidget       *window;
//     GtkWidget *viewport;
//
//     gtk_init(&argc, &argv);
//
//     builder = gtk_builder_new();
//     gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
//
//     window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
//
//     gtk_builder_connect_signals(builder, NULL);
//
//      button_add = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
//
//      viewport = GTK_WIDGET(gtk_builder_get_object(builder, "viewport1"));
//
//     g_object_unref(builder);
//
//     gtk_widget_show(window);
//     gtk_main();
//
//     return 0;
// }
//






