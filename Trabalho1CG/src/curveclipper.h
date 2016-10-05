#ifndef BEZIERCLIPPER_H
#define BEZIERCLIPPER_H
#include "objeto.h"
#include "window.h"
#include "cohensutherland.h"
#include <vector>


class CurveClipper {
public:
	//-----------------------------------------------
	//Vetor de retas da curva
	typedef std::vector<Reta *> listaRetas;
	//-----------------------------------------------
	//Vetor de pontos
	typedef std::vector<Ponto2D> listaPontos;
	//-----------------------------------------------
	//Construtor padrao
	CurveClipper( Window2D * janela ) {
		this->janela = janela;
	}
	//-----------------------------------------------
	//Clipa a curva, clipando suas retas
	Objeto * clip( Objeto * curvaOriginal );
private:
	//-----------------------------------------------
	//Cria um vetor de retas a partir dos pontos calculados da curva
	listaRetas paraRetas( CurvaBezier * curva );
	//-----------------------------------------------
	//Cria um vetor de retas a partir dos pontos calculados da curva
	listaRetas paraRetas( CurvaBSpline * curva );
	//-----------------------------------------------
	//Clipa todas as retas de dado vetor
	listaRetas cliparRetas( listaRetas retas );
	//-----------------------------------------------
	//A window atual do SGI.
	Window2D * janela;
	//-----------------------------------------------
	//Transforma uma lista de retas em uma lista de pontos.
	listaPontos paraPontos( listaRetas retas );
	//-----------------------------------------------
	//Verifica se o ponto esta na borda da janela
	bool pontoNaBorda( Ponto2D ponto, Window2D *janela );
};

#endif // BEZIERCLIPPER_H
