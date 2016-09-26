#ifndef WIREFRAMECLIPPER_H
#define WIREFRAMECLIPPER_H
#include "window.h"
#include "objeto.h"
#include "transformadas.hpp"
#include <vector>
#include "cohensutherland.h"

class WireframeClipper {
public:
	WireframeClipper( Window2D * janela ): janela( janela ) {}
	Objeto * clip( Objeto * objeto );
private:
	typedef std::vector<Reta *> RetasWireframe;
	typedef std::vector<Ponto2D> ListaPontos;
	Window2D * janela;
	RetasWireframe converterParaRetas( Wireframe * wireframe );
	RetasWireframe cliparRetas( RetasWireframe retas );
	ListaPontos LigarRetas( RetasWireframe retasClipadas );
};

#endif // WIREFRAMECLIPPER_H
