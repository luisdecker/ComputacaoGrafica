#include <gtkmm/builder.h>
#include <gtkmm/application.h>
#include "MainWindow.hpp"
#include "IncludeObjectDialog.hpp"
#include "DrawingArea.hpp"
#include "TransformationDialog.hpp"
#include "window.h"
#include "objectfile.h"

#include <iostream>

//#define TESTES_MODELO

#ifdef TESTES_MODELO

#include "objeto.h"
#include "cohensutherland.h"
#include "liangbarsky.h"
#include "curveclipper.h"

#endif

#include "objeto.h"



int main( int argc, char * argv[] ) {

		// std::vector<Ponto2D> pontosControle;

		// pontosControle.push_back( set2DPoint( 1, 1 ) );
		// pontosControle.push_back( set2DPoint( 2, 2 ) );
		// pontosControle.push_back( set2DPoint( 3, 2 ) );
		// pontosControle.push_back( set2DPoint( 4, 1 ) );
		// pontosControle.push_back( set2DPoint( 5, 3 ) );

		// CurvaBSpline minhaCurvaFofinha( "Curva", pontosControle );
		// int i = 0;
		// for( Ponto2D ponto : minhaCurvaFofinha.obterPontosCalculados() ) {
		// 	std::cout << "Ponto " << i << ": ( " << ponto.x << " , " << ponto.y << " )\n";
		// 	i++;
		// }




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
#ifdef TESTES_MODELO2
	std::cout << "=======================================================\n";
	BezierClipper::listaPontos pontosControle;
	pontosControle.push_back( set2DPoint( 100, 100 ) );
	pontosControle.push_back( set2DPoint( 200, 300 ) );
	pontosControle.push_back( set2DPoint( 300, 300 ) );
	pontosControle.push_back( set2DPoint( 400, 100 ) );
	CurvaBezier minhaCurvaFofinha( "Curva", pontosControle );
	int i = 0;
	for( Ponto2D ponto : minhaCurvaFofinha.obterPontosCalculados() ) {
		std::cout << "Ponto " << i << ": ( " << ponto.x << " , " << ponto.y << " )\n";
		i++;
	}
	
	BezierClipper(window).clip(&minhaCurvaFofinha);
	
	


	std::cout << "=======================================================\n";
	return 0;
#endif
	app->run( *mainWindow );

	return 0;

}
