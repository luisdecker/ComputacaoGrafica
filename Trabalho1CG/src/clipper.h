#ifndef CLIPPER_H
#define CLIPPER_H

#include "window.h"
#include "objeto.h"

class Clipper {
public:
	Clipper( Window2D * janela );
	~Clipper();
	Objeto * operator()( Objeto * obj );

private:
	Ponto * clipPonto( Ponto * ponto );
	Reta * clipReta( Reta * reta );
	Wireframe * clipPoligono(Wireframe * wireframe);
	Objeto * clip(Objeto * objeto);
	Window2D * janela;
};

#endif // CLIPPER_H
