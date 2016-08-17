#include <iostream>

#include "MainWindow.hpp"



MainWindow::MainWindow( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
	Gtk::Window( cobject ), builder( refGlade ) {

	includeObjDiag = nullptr;




	builder->get_widget( "btn_include", btnInclude );
	builder->get_widget( "btn_in", btnIn );
	builder->get_widget( "btn_out", btnOut );
	builder->get_widget_derived( "diag_incl_obj", includeObjDiag );
	builder->get_widget( "drawingarea", papel );




	btnInclude->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_include_clicked ) );
	btnIn->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_in_clicked ) );
	btnOut->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_out_clicked ) );
	//papel->signal_draw().connect( sigc::mem_fun( *this, &MainWindow::drawObject ) );

}

void MainWindow::on_btn_include_clicked() {

	includeObjDiag->executar();

}

void MainWindow::on_btn_in_clicked() {

}

void MainWindow::on_btn_out_clicked() {

}

void MainWindow::atualizaObjectFile( ObjectFile * newOf ) {
	this->of = newOf;
}


bool MainWindow::drawObject( GtkWidget * widget ) {
	this->cr->set_line_width( 1.0 );
	for( Objeto * objeto : of->obterObjetos() ) {
		switch( objeto->tipoObjeto ) {
			case Objeto::ponto: {
				Ponto * ponto = dynamic_cast<Ponto *>( objeto );
				Ponto2D coordenada = ponto->obterCoordenada();
				this->cr->arc( coordenada.x, coordenada.y, 1., 0., 2 * M_PI );
				this->cr->stroke();

				break;
			}
			case Objeto::reta: {
				Reta * reta = dynamic_cast<Reta *>( objeto );
				Ponto2D inicial = reta->obterCoordenadaInicial();
				Ponto2D final = reta->obterCoordenadaFinal();
				this->cr->move_to( inicial.x, inicial.y );
				this->cr->line_to( final.x, final.y );
				this->cr->stroke();



				break;
			}
			case Objeto::wireframe: {break;}
		}
	}
	//Redesenha a tela
	queue_draw();

}



















