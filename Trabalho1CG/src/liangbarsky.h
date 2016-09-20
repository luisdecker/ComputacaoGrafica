#ifndef LIANGBARSKY_H
#define LIANGBARSKY_H
#include <iostream>
#include "window.h"
#include "objeto.h"


class LiangBarsky {
public:
	LiangBarsky(Window2D * window);
	Objeto * clip( Objeto * objeto );
private:
	Window2D * janela;
};

#endif // LIANGBARSKY_H
