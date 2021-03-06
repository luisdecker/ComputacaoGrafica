#ifndef INCLUDEOBJECTCONTROLLER_H
#define INCLUDEOBJECTCONTROLLER_H

#include <string>
#include "objectfile.h"
#include "window.h"
using namespace std;
typedef std::vector<Ponto2D> ListaPontos;
class IncludeObjectController {

	ObjectFile * obf;
	Window2D * window;

public:
	void setObjectFile( ObjectFile * obf );
	void setWindow( Window2D * window );
	bool incluirPonto( string nome, double x, double y );
	bool incluirReta( string nome, double x0, double y0, double x1, double y1 );
	bool incluirPontoWireframe( string nome, double x, double y );
	bool confirmaInclusaoWireframe( string nome, bool todosPontosInclusos, bool preenchido );
	bool incluirBezier( string nome, ListaPontos pontosControle );
	bool incluirBSpline( string nome, ListaPontos pontosControle );

};

#endif