#include <gtkmm/builder.h>
#include <gtkmm/application.h>
#include "MainWindow.hpp"
#include "IncludeObjectDialog.hpp"
#include "DrawingArea.hpp"
#include "TransformationDialog.hpp"
#include "window.h"
#include "objectfile.h"

#include <iostream>
#define TESTES_MODELO

#ifdef TESTES_MODELO
#include "objeto.h"
#include "cohensutherland.h"
#include "liangbarsky.h"
#endif


int main( int argc, char * argv[] ) {

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "org.gtkmm.example" );

	//Aloca um ponteiro para um mainwindow
	MainWindow * mainWindow = NULL;
	IncludeObjectDialog * includeObjDiag = NULL;
	DrawingArea * drawingArea = NULL;
	TransformationDialog * transformationDialog = NULL;

	Window2D * window = new Window2D( set2DPoint( 0, 0 ), set2DPoint( 500, 500 ) );
	ObjectFile * of = new ObjectFile();

	//Cria o objeto a partir do XLM do GLADE
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file( "window_main.glade" );

	builder->get_widget_derived( "window_main", mainWindow );
	builder->get_widget_derived( "diag_incl_obj", includeObjDiag );
	builder->get_widget_derived( "drawingarea", drawingArea );
	builder->get_widget_derived( "transformationDialog", transformationDialog );


	mainWindow->setIncludeObjectDialog( includeObjDiag );
	mainWindow->setDrawingArea( drawingArea );
	mainWindow->setTransformationDialog( transformationDialog );

	drawingArea->setWindow( window );
	mainWindow->setWindow( window );

	mainWindow->setObjectFile( of );
	includeObjDiag->setObjectFile( of );
	drawingArea->setObjectFile( of );
	transformationDialog->setObjectFile( of );

	mainWindow->set_resizable( false );

	/*TESTES DO MODELO*/
#ifdef TESTES_MODELO
	std::cout << "=======================================================\n";
	Reta retaTeste( "reta", set2DPoint( -100, 250 ), set2DPoint( 600, 250 ) );

//	CohenSutherland clipper( window );
	//Window2D novaWindow(set2DPoint(70,60), set2DPoint(230,150));
	LiangBarsky clipper( window );
	Objeto * clipada = clipper.clip( &retaTeste );
	if( !(clipada == nullptr) ) {
		Reta * resultado = dynamic_cast<Reta *>( clipada );
		std::cout << "Ponto inicial: (" << resultado->obterCoordenadaInicial().x << " , " << resultado->obterCoordenadaInicial().y << ")\n";
		std::cout << "Ponto final: (" << resultado->obterCoordenadaFinal().x << " , " << resultado->obterCoordenadaFinal().y << ")\n";
	}else {
		std::cout << "NULA\n";
	}
	std::cout << "=======================================================\n";
	return 0;
#endif
	app->run( *mainWindow );

	return 0;

}
