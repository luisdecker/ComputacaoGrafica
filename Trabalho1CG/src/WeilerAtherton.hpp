#ifndef WEILERATHERTON_H
#define WEILERATHERTON_H

#include "objeto.h"
#include "window.h"
#include "tipos.hpp"
#include <vector>
#include <cmath>

#define INF 10000

class WeilerAtherton{

public:
	WeilerAtherton(Window2D * window);
	void clip(Wireframe *wire);

	private:
		Window2D *window;

		std::vector<Ponto2D*> subjectPoints,windowPoints,clipPoints;

		Ponto2D * calculaInterseccaoEntreRetas(Ponto2D a, Ponto2D b, Ponto2D c, Ponto2D d);
		bool estaDentroDaLinha(Ponto2D a, Ponto2D b, Ponto2D c);
		bool existeInterseccao(Ponto2D p1, Ponto2D q1, Ponto2D p2, Ponto2D q2);
		int orientacao(Ponto2D p, Ponto2D q, Ponto2D r);
		bool  pontoEstaSobreAReta(Ponto2D p, Ponto2D q, Ponto2D r);
		std::vector<Ponto2D*>::iterator procuraPonto(std::vector<Ponto2D*> &lista, Ponto2D pontoBusca);
		void definePontosDeEntrada();
		bool todosPontosEntradaVisitados();
		std::vector<Ponto2D*>::iterator proximoPontoEntrada();
		bool estaDentroDaWindow(Ponto2D p);
		bool pontoJaInserido(std::vector<Ponto2D*> &lista, Ponto2D pontoBusca);

};



#endif 