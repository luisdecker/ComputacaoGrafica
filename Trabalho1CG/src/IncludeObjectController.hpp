#ifndef INCLUDEOBJECTCONTROLLER_H
#define INCLUDEOBJECTCONTROLLER_H

#include <string>
#include "objectfile.h"
#include "window.h"
using namespace std;

class IncludeObjectController {

	ObjectFile * obf;
	Window2D * window;

public:
	void setObjectFile( ObjectFile * obf );
	void setWindow( Window2D * window );
	bool incluirPonto( string nome, double x, double y );
	bool incluirReta( string nome, double x0, double y0, double x1, double y1 );
	bool incluirPontoWireframe( string nome, double x, double y );

};

#endif