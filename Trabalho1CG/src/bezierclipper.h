#ifndef BEZIERCLIPPER_H
#define BEZIERCLIPPER_H
#include "objeto.h"
#include "window.h"
#include "cohensutherland.h"
#include <vector>


class BezierClipper {
public:
	//-----------------------------------------------
	//Vetor de retas da curva
	typedef std::vector<Reta *> listaRetas;
	//-----------------------------------------------
	//Vetor de pontos
	typedef std::vector<Ponto2D> listaPontos;
	//-----------------------------------------------
	//Construtor padrao
	BezierClipper( Window2D * janela ) {
		this->janela = janela;
	}
	//-----------------------------------------------
	//Clipa a curva, clipando suas retas
	CurvaBezier * clip( CurvaBezier * curvaOriginal );
private:
	//-----------------------------------------------
	//Cria um vetor de retas a partir dos pontos calculados da curva
	listaRetas paraRetas( CurvaBezier * curva );
	//-----------------------------------------------
	//Clipa todas as retas de dado vetor
	listaRetas cliparRetas( listaRetas retas );
	//-----------------------------------------------
	//A window atual do SGI.
	Window2D * janela;
	//-----------------------------------------------
	//Transforma uma lista de retas em uma lista de pontos.
	listaPontos paraPontos( listaRetas retas );
};

#endif // BEZIERCLIPPER_H
