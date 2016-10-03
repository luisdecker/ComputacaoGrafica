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
	const int deslocamento = 10;
	const int width = allocation.get_width() - deslocamento;
	const int height = allocation.get_height() - deslocamento;


	//std::cout << "[DrawingArea]ViewPort de tamanho  " << width << "," << height << std::endl;
	//std::cout << "[DrawingArea]Window de tamanho  " << mainWindow->obterXMaximo() - mainWindow->obterXMinimo() << "," << mainWindow->obterYMaximo() - mainWindow->obterYMinimo()  << std::endl;

	//Aqui desenha os boundaries da viewport
	cr->move_to( deslocamento, deslocamento );
	cr->line_to( deslocamento, height );
	cr->move_to( deslocamento, height );
	cr->line_to( width, height );
	cr->move_to( width, height );
	cr->line_to( width, deslocamento );
	cr->move_to( width, deslocamento );
	cr->line_to( deslocamento, deslocamento );
	cr->stroke();


	this->viewPort = new ViewPort( set2DPoint( 10, 10 ), set2DPoint( width, height ) );



	//std::cout << "[DrawingArea]Vai desenhar " << mainOf->obterObjetos().size() << " objetos" << std::endl;
	for( Objeto * objeto : mainOf->obterObjetos() ) {
		if( !objeto->desenhar ) continue;
		switch( objeto->tipoObjeto ) {
			case Objeto::ponto: {

				Ponto * ponto = dynamic_cast<Ponto *>( objeto );
				Ponto2D coordenada = ponto->obterCoordenadaSCN();

				coordenada = viewPort->tranformarCoordenadasSCN( *mainWindow, coordenada );
				std::cout << "[DrawingArea]Vai desenhar um ponto em (" << coordenada.x << " , " << coordenada.y << ")\n";
				cr->arc( coordenada.x + deslocamento, coordenada.y + deslocamento, 1., 0., 2 * M_PI );
				cr->stroke();

				break;
			}//Ponto
			case Objeto::reta: {

				Reta * reta = dynamic_cast<Reta *>( objeto );

				Ponto2D inicial = reta->obterCoordenadaInicialSCN();
				inicial = viewPort->tranformarCoordenadasSCN( *mainWindow, inicial );
				Ponto2D final = reta->obterCoordenadaFinalSCN();
				final = viewPort->tranformarCoordenadasSCN( *mainWindow, final );
				//	std::cout << "[DrawingArea]Vai desenhar uma reta de " << inicial.x << "," << inicial.y
				//		  << " até " << final.x << "," << final.y << std::endl;
				cr->move_to( inicial.x + deslocamento, inicial.y + deslocamento );
				cr->line_to( final.x + deslocamento, final.y + deslocamento );
				cr->stroke();



				break;
			}//Reta
			case Objeto::wireframe: {
				Wireframe * wf = dynamic_cast<Wireframe *>( objeto );

				if( wf->possuiTodosPontosInclusos() ) {
					if( wf->ehPreenchido() ) {
						std::vector< std::vector<Ponto2D> > todosPontosSCN = wf->obterPontosSCN();
						for( std::vector<Ponto2D> pontosWF : todosPontosSCN ) {

							Ponto2D inicial = viewPort->tranformarCoordenadasSCN( *mainWindow, pontosWF.front() );
							cr->move_to( inicial.x + deslocamento, inicial.y + deslocamento );

							for( Ponto2D ponto : pontosWF ) {
								ponto = viewPort->tranformarCoordenadasSCN( *mainWindow, ponto );
								cr->line_to( ponto.x + deslocamento, ponto.y + deslocamento );
							}

							cr->close_path();

							if( wf->ehPreenchido() ) {
								cr->fill();
							}

							cr->stroke();


						}
					} else {
						for( Reta * reta : wf->obterRetas() ) {
							Ponto2D inicial = reta->obterCoordenadaInicialSCN();
							inicial = viewPort->tranformarCoordenadasSCN( *mainWindow, inicial );
							Ponto2D final = reta->obterCoordenadaFinalSCN();
							final = viewPort->tranformarCoordenadasSCN( *mainWindow, final );
							//	std::cout << "[DrawingArea]Vai desenhar uma reta de " << inicial.x << "," << inicial.y
							//		  << " até " << final.x << "," << final.y << std::endl;
							cr->move_to( inicial.x + deslocamento, inicial.y + deslocamento );
							cr->line_to( final.x + deslocamento, final.y + deslocamento );
							cr->stroke();
						}
					}
				}
				break;

			}//Wireframe
			case Objeto::bezier: {
				CurvaBezier * curva = dynamic_cast<CurvaBezier *>( objeto );
				ListaPontos pontosSCN = curva->obterCoordenadasSCN(), pontosExpandidos;
				for( Ponto2D pontoSCN : pontosSCN ) {
					Ponto2D pontoExpandido = viewPort->tranformarCoordenadasSCN( *mainWindow, pontoSCN );
					pontosExpandidos.push_back( pontoExpandido );
				}
				Ponto2D pontoInicial = pontosExpandidos.front();
				cr->move_to( pontoInicial.x + deslocamento, pontoInicial.y + deslocamento );
				for( Ponto2D pontoExpandido : pontosExpandidos ) {
					cr->line_to( pontoExpandido.x + deslocamento, pontoExpandido.y + deslocamento );
					cr->move_to( pontoExpandido.x + deslocamento, pontoExpandido.y + deslocamento );
				}
				cr->stroke();
				break;
			}//Bezier
		}
	}

	return true;

}

// // cr->rectangle(20, 140, 100, 100);
// cr->move_to(20, 140);
//  cr->rel_line_to(100, 0);
//  cr->rel_line_to(0, 100);
//  cr->rel_line_to(-100, 0);
//  cr->close_path();
// cr->stroke();

// cr->move_to(60, 220);
//  cr->line_to(150, 0);
//  // cr->move_to(150, 0);
//  cr->line_to(0, 150);
//  // cr->move_to(0, 150);
//  cr->line_to(-150, 0);
//  // cr->move_to(-150, 0);
// cr->close_path();
// cr->fill();
// cr->stroke();


