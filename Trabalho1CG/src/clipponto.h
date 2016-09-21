#ifndef CLIPPONTO_H
#define CLIPPONTO_H
#include "window.h"
#include "objeto.h"
#include <iostream>
#include "transformadas.hpp"

class ClipPonto {
public:
	ClipPonto( Window2D * window );
	Objeto * clip( Objeto * objeto );
private:
	Window2D * janela;
	
};

#endif // CLIPPONTO_H
