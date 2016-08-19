#include "DrawingArea.hpp"
#include <cairomm/context.h>


DrawingArea::DrawingArea( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
	Gtk::DrawingArea( cobject ), builder( refGlade ) {
}

DrawingArea::~DrawingArea() {
}

void DrawingArea::atualizaObjectFile( ObjectFile * of ) {
	this->mainOf = of;
	queue_draw();
}

void DrawingArea::atualizaWindow( Window2D * window ) {
	this->mainWindow = window;
	queue_draw();
}


bool DrawingArea::on_draw( const Cairo::RefPtr<Cairo::Context> & cr ) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	std::cout << "ViewPort de tamanho  " << width << "," << height << std::endl;
	this->viewPort = new ViewPort( set2DPoint( 0, 0 ), set2DPoint( width, height ) );
	std::cout << "Vai desenhar " << mainOf->obterObjetos().size() << " objetos" << std::endl;
	for( Objeto * objeto : mainOf->obterObjetos() ) {
		switch( objeto->tipoObjeto ) {
			case Objeto::ponto: {

				Ponto * ponto = dynamic_cast<Ponto *>( objeto );
				Ponto2D coordenada = ponto->obterCoordenada();
				coordenada = viewPort->tranformarCoordenadas( *mainWindow, coordenada );
				cr->arc( coordenada.x, coordenada.y, 1., 0., 2 * M_PI );
				cr->stroke();

				break;
			}
			case Objeto::reta: {
				Reta * reta = dynamic_cast<Reta *>( objeto );
				Ponto2D inicial = reta->obterCoordenadaInicial();
				inicial = viewPort->tranformarCoordenadas( *mainWindow, inicial );
				Ponto2D final = reta->obterCoordenadaFinal();
				final = viewPort->tranformarCoordenadas( *mainWindow, final );
				std::cout << "Vai desenhar uma reta de " << inicial.x << "," << inicial.y
						  << " até " << final.x << "," << final.y << std::endl;
				cr->move_to( inicial.x, inicial.y );
				cr->line_to( final.x, final.y );
				cr->stroke();



				break;
			}
			case Objeto::wireframe: {
				Wireframe * wf = dynamic_cast<Wireframe *>( objeto );
				std::vector<Ponto2D> pontosWF = wf->obterPontos();
				pontosWF.erase( pontosWF.begin() );
				Ponto2D inicial = viewPort->tranformarCoordenadas( *mainWindow, pontosWF.front() );
				cr->move_to( inicial.x, inicial.y );
				for( Ponto2D ponto : pontosWF ) {
					ponto = viewPort->tranformarCoordenadas( *mainWindow, ponto );
					cr->line_to( ponto.x, ponto.y );
					cr->move_to( ponto.x, ponto.y );
				}
				cr->line_to( inicial.x, inicial.y );
				cr->stroke();


				break;

			}
		}
	}

	/*
		// coordinates for the center of the window
		int xc, yc;
		xc = width / 2;
		yc = height / 2;

		cr->set_line_width( 2.0 );

		// draw red lines out from the center of the window
		cr->set_source_rgb( 0.0, 0.0, 0.0 );
		cr->move_to( 0, 0 );
		cr->line_to( xc, yc );
		cr->line_to( 0, height );
		cr->move_to( xc, yc );
		cr->line_to( width, yc );
		cr->stroke();
	*/
	return true;

}