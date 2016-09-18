#include "DrawingArea.hpp"
#include <cairomm/context.h>


DrawingArea::DrawingArea( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
	Gtk::DrawingArea( cobject ), builder( refGlade ) {
}

DrawingArea::~DrawingArea() {
}

void DrawingArea::setObjectFile( ObjectFile * of ) {
	this->mainOf = of;
	mainOf->subscribe( this );

}

void DrawingArea::setWindow( Window2D * window ) {
	this->mainWindow = window;
	mainWindow->subscribe( this );
}

void DrawingArea::update() {

	queue_draw();

}


bool DrawingArea::on_draw( const Cairo::RefPtr<Cairo::Context> & cr ) {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	std::cout << "[DrawingArea]ViewPort de tamanho  " << width << "," << height << std::endl;
	std::cout << "[DrawingArea]Window de tamanho  " << mainWindow->obterXMaximo() - mainWindow->obterXMinimo() << "," << mainWindow->obterYMaximo() - mainWindow->obterYMinimo()  << std::endl;

	this->viewPort = new ViewPort( set2DPoint( 0, 0 ), set2DPoint( width, height ) );
	std::cout << "[DrawingArea]Vai desenhar " << mainOf->obterObjetos().size() << " objetos" << std::endl;
	for( Objeto * objeto : mainOf->obterObjetos() ) {
		switch( objeto->tipoObjeto ) {
			case Objeto::ponto: {

				Ponto * ponto = dynamic_cast<Ponto *>( objeto );
				Ponto2D coordenada = ponto->obterCoordenadaSCN();

				coordenada = viewPort->tranformarCoordenadasSCN( *mainWindow, coordenada );
				std::cout << "[DrawingArea]Vai desenhar um ponto em (" << coordenada.x << " , " << coordenada.y << ")\n";
				cr->arc( coordenada.x, coordenada.y, 1., 0., 2 * M_PI );
				cr->stroke();

				break;
			}
			case Objeto::reta: {
				Reta * reta = dynamic_cast<Reta *>( objeto );
				Ponto2D inicial = reta->obterCoordenadaInicialSCN();
				inicial = viewPort->tranformarCoordenadasSCN( *mainWindow, inicial );
				Ponto2D final = reta->obterCoordenadaFinalSCN();
				final = viewPort->tranformarCoordenadasSCN( *mainWindow, final );
				std::cout << "[DrawingArea]Vai desenhar uma reta de " << inicial.x << "," << inicial.y
						  << " até " << final.x << "," << final.y << std::endl;
				cr->move_to( inicial.x, inicial.y );
				cr->line_to( final.x, final.y );
				cr->stroke();



				break;
			}
			case Objeto::wireframe: {
				Wireframe * wf = dynamic_cast<Wireframe *>( objeto );
				std::vector<Ponto2D> pontosWF = wf->obterPontosSCN();
				std::cout<< "[DrawingArea] Wireframe com tamanho " << pontosWF.size() << "\n";
				//pontosWF.erase( pontosWF.begin() );
				if(pontosWF.size()>2){
				Ponto2D inicial = viewPort->tranformarCoordenadasSCN( *mainWindow, pontosWF.front() );
				cr->move_to( inicial.x, inicial.y );
				
				for( Ponto2D ponto : pontosWF ) {
					ponto = viewPort->tranformarCoordenadasSCN( *mainWindow, ponto );
					std::cout << "[DrawingArea]Vai desenhar um ponto do poligono em (" << ponto.x << " , " << ponto.y << ")\n";
					cr->line_to( ponto.x, ponto.y );
					cr->move_to( ponto.x, ponto.y );
				}
				cr->line_to( inicial.x, inicial.y );
				cr->stroke();
				}

				break;

			}
		}
	}

	return true;

}