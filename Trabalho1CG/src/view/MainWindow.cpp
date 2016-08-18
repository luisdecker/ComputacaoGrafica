#include <iostream>
#include "MainWindow.hpp"
#include "../window.h"


MainWindow::MainWindow( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
	Gtk::Window( cobject ), builder( refGlade ) {

	includeObjDiag = nullptr;
	drawingArea = nullptr;

	builder->get_widget( "btn_include", btnInclude );
	builder->get_widget( "btn_in", btnIn );
	builder->get_widget( "btn_out", btnOut );
	builder->get_widget( "btn_up", btnUp );
	builder->get_widget( "btn_down", btnDown );
	builder->get_widget( "btn_left", btnLeft );
	builder->get_widget( "btn_right", btnRight );

	builder->get_widget_derived( "diag_incl_obj", includeObjDiag );
	builder->get_widget_derived( "drawingarea", drawingArea );

	of = new ObjectFile();
	atualizaObjectFile( of );
	atualizaWindow( new Window2D( set2DPoint( 0, 0 ), set2DPoint( 500, 500 ) ) );


	builder->get_widget( "list_obj", m_TreeView );

	m_Columns = new ModelColumns();

	Gtk::TreeModelColumnRecord * tmcr = dynamic_cast<Gtk::TreeModelColumnRecord *>( m_Columns );

	m_refTreeModel = Gtk::ListStore::create( *tmcr );
	m_TreeView->set_model( m_refTreeModel );

	Gtk::TreeModel::Row row = *( m_refTreeModel->append() );
	row[m_Columns->nameObj] = "teste";
	row[m_Columns->typeObj] = "recta";

	row = *( m_refTreeModel->append() );
	row[m_Columns->nameObj] = "2";
	row[m_Columns->typeObj] = "point";

	m_TreeView->append_column( "Nome", m_Columns->nameObj );
	m_TreeView->append_column( "Tipo", m_Columns->typeObj );



	btnInclude->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_include_clicked ) );
	btnIn->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_in_clicked ) );
	btnOut->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_out_clicked ) );
	btnUp->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_up_clicked ) );
	btnDown->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_down_clicked ) );
	btnLeft->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_left_clicked ) );
	btnRight->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_right_clicked ) );


	//papel->signal_draw().connect( sigc::mem_fun( *this, &MainWindow::drawObject ) );

}

void MainWindow::on_btn_include_clicked() {

	includeObjDiag->executar( of );
	atualizaObjectFile( of );

}

void MainWindow::on_btn_in_clicked() {
	Ponto2D ie = this->windowPrincipal->inferiorEsquerdo();
	ie.x += 10, ie.y += 10;
	Ponto2D sd = this->windowPrincipal->superiorDireito();
	sd.x -= 10, sd.y -= 10;

	Window2D * newWindow = new Window2D( ie, sd );
	std::cout << "Novas coordenadas da window: " << ie.x << "," << ie.y << " | " << sd.x << "," << sd.y << std::endl;
	atualizaWindow( newWindow );
}
void MainWindow::on_btn_down_clicked() {
	Ponto2D ie = this->windowPrincipal->inferiorEsquerdo();
	ie.y -= 10;
	Ponto2D sd = this->windowPrincipal->superiorDireito();
	sd.y -= 10;

	Window2D * newWindow = new Window2D( ie, sd );
	std::cout << "Novas coordenadas da window: " << ie.x << "," << ie.y << " | " << sd.x << "," << sd.y << std::endl;

	atualizaWindow( newWindow );
}

void MainWindow::on_btn_left_clicked() {
	Ponto2D ie = this->windowPrincipal->inferiorEsquerdo();
	ie.x -= 10;
	Ponto2D sd = this->windowPrincipal->superiorDireito();
	sd.x -= 10;

	Window2D * newWindow = new Window2D( ie, sd );
	std::cout << "Novas coordenadas da window: " << ie.x << "," << ie.y << " | " << sd.x << "," << sd.y << std::endl;

	atualizaWindow( newWindow );
}

void MainWindow::on_btn_right_clicked() {
	Ponto2D ie = this->windowPrincipal->inferiorEsquerdo();
	ie.x += 10;
	Ponto2D sd = this->windowPrincipal->superiorDireito();
	sd.x += 10;

	Window2D * newWindow = new Window2D( ie, sd );
	std::cout << "Novas coordenadas da window: " << ie.x << "," << ie.y << " | " << sd.x << "," << sd.y << std::endl;

	atualizaWindow( newWindow );
}
void MainWindow::on_btn_up_clicked() {
	Ponto2D ie = this->windowPrincipal->inferiorEsquerdo();
	ie.y += 10;
	Ponto2D sd = this->windowPrincipal->superiorDireito();
	sd.y += 10;

	Window2D * newWindow = new Window2D( ie, sd );
	std::cout << "Novas coordenadas da window: " << ie.x << "," << ie.y << " | " << sd.x << "," << sd.y << std::endl;

	atualizaWindow( newWindow );
}



void MainWindow::on_btn_out_clicked() {
	Ponto2D ie = this->windowPrincipal->inferiorEsquerdo();
	ie.x -= 10, ie.y -= 10;
	Ponto2D sd = this->windowPrincipal->superiorDireito();
	sd.x += 10, sd.y += 10;

	Window2D * newWindow = new Window2D( ie, sd );
	std::cout << "Novas coordenadas da window: " << ie.x << "," << ie.y << " | " << sd.x << "," << sd.y << std::endl;
	atualizaWindow( newWindow );
}

void MainWindow::atualizaObjectFile( ObjectFile * newOf ) {
	this->of = newOf;
	this->drawingArea->atualizaObjectFile( newOf );
}
void MainWindow::atualizaWindow( Window2D * window ) {
	this->windowPrincipal = window;
	this->drawingArea->atualizaWindow( window );
}

/*
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

}*/



















