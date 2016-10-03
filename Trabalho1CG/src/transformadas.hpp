#ifndef TRANSFORMADAS_H
#define TRANSFORMADAS_H

#include "objeto.h"
#include "tipos.hpp"
#include "matriz.hpp"
#include <cassert>
#include <math.h>
#include <iostream>
class Objeto;
class Tranformadas {
public:
	static Objeto * transladar( Objeto * obj, Ponto2D direcao );
	static Objeto * rotacionar( Objeto * obj, double graus, Ponto2D pontoReferencia );
	static Objeto * redimensionar( Objeto * obj, Ponto2D escala );
	static Matriz ponto2DparaMatriz( Ponto2D ponto );
	static Ponto2D matrizParaPonto2D( Matriz matriz );
	static Ponto3D ponto2DParaHomogeneo( Ponto2D ponto );
	static Matriz ponto3DparaMatriz( Ponto3D ponto );
	static Ponto3D matrizParaPonto3D( Matriz matriz );
	static Matriz gerarMatrizTranslacao( Ponto2D direcao );
	static Matriz gerarMatrizRotacao( double graus );
	static Matriz gerarMatrizRedimensionamento( double escalaX, double escalaY );
	static long long int fatorial( int n );

};
#endif