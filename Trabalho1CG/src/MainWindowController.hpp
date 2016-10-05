#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "objectfile.h"
#include "window.h"

#define ZOOM 5
#define PASSO 10
#define ANGULO 10

class MainWindowController {

	ObjectFile * obf;
	Window2D * window;

public:
	void setObjectFile( ObjectFile * obf );
	void setWindow( Window2D * window );

	Objeto * obtemUltimoObjInserido();
	int obtemTamanhoObjectFile();
	void windowZoomIn();
	void windowZoomOut();
	void windowRight();
	void windowLeft();
	void windowUp();
	void windowDown();
	void windowRodaHorario();
	void windowRodaAntiHorario();
};

#endif