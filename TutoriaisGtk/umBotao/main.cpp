#include <iostream>
#include <iomanip>
#include <gtk/gtk.h>

static void
printHello( GtkWidget *GtkWidget,
			gpointer data ) {

	g_print( "Hello" );
}


/*Gerenciador de sinal de delete_event. Quando retorna true, a janela é destruída. Útil para janelas tipo "Tem certeza que deseja sair"*/
static gboolean
on_delete_event( GtkWidget *widget,
				 GdkEvent  *event,
				 gpointer   data ) {

	return gtk_true();
}



int
main( int argc,
	  char **argv ) {

	/*GtkWidget é o container padrão para widgets*/
	GtkWidget * janela;
	GtkWidget * botao;

	/*Este comando inicia as aplicações GTK. É um MUST HAVE*/
	gtk_init( &argc, &argv );

	/*Cria uma nova janela, e seta seu titulo*/
	janela = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_title( GTK_WINDOW( janela ), "Olá" );

	/*Quando a janela emitir um sinal "delete-event" (emitido pelo gtk em resposta a um evento do window manager, como um clique no X), ela chama o
	 método on_delete_event*/
	g_signal_connect( janela, "delete-event", G_CALLBACK( on_delete_event ), NULL );

	/*Aqui, conectamos o sinal de "destroy" a função de gtk_main_quit
	  Este sinal é emitido quando chamamos gtk_window_destroy() na janela ou então delete_event retorna falso.
	 */
	g_signal_connect( janela, "destroy", G_CALLBACK( gtk_main_quit ), NULL );

	/*Seta a largura da borda da janela*/
	gtk_container_set_border_width( GTK_CONTAINER( janela ), 10 );

	/*Cria um botão com a label "Olá"*/
	botao = gtk_button_new_with_label( "Olá, otário!" );

	/*Quando o botão receber um sinal "clicked", ele chama a funcao printHello, passando NULL como argumento*/
	g_signal_connect( botao, "clicked", G_CALLBACK( printHello ), NULL );

	/*Conecta o sinal de "clicked" do botão a gtk_window_destroy,
	 * substituindo o argumento padrão (o botão) para o argumento do usuário(a janela)*/
	g_signal_connect_swapped( botao, "clicked", G_CALLBACK( gtk_widget_destroy ), janela );

	/*Adiciona o botão na janela. Como uma GTK_WINDOW herda de GtkBin, ela só pode ter um filho. */
	gtk_container_add( GTK_CONTAINER( janela ), botao );

	/*Amostra as coisa tudo*/
	gtk_widget_show( botao );
	gtk_widget_show( janela );

	/*Todas as aplicações tem um gtkMain(). O controle termina aqui,e espera por um evento, até gtk_main_quit */
	gtk_main();
}




