#ifndef COHENSUTHERLAND_H
#define COHENSUTHERLAND_H

#include "window.h"
#include "transformadas.hpp"
#include "objeto.h"
#include <iostream>
class CohenSutherland {
public:
	enum direcao {norte, nordeste, leste, sudeste, sul, sudoeste, oeste, noroeste, centro};
	CohenSutherland( Window2D * janela );
	Objeto * clip( Objeto * objeto );
	

private:

	//================BINCODE====================
	struct binCode {
		void setBit0( bool bit ) {code[0] = bit;}
		void setBit1( bool bit ) {code[1] = bit;}
		void setBit2( bool bit ) {code[2] = bit;}
		void setBit3( bool bit ) {code[3] = bit;}
		void reset() {setBit0( 0 ); setBit1( 0 ); setBit2( 0 ); setBit3( 0 );}
		void set() {setBit0( 1 ); setBit1( 1 ); setBit2( 1 ); setBit3( 1 );}
		binCode operator &( binCode other );
		bool operator ==( binCode other );
		CohenSutherland::direcao obterDirecaoCodigo();

	private:
		bool code[4] = {0, 0, 0, 0};
		int codeToInt();
	};
	//===========================================


	Window2D * janela;//Window do sistema

	binCode checkCode( Ponto2D ponto );//verificar o codigo binario de um ponto em relacao a window

	double obterCoeficienteAngular( Reta * reta );



	bool pontoNaWindow( Ponto2D ponto ); //Verifica se o ponto esta na window

	Ponto2D interseccaoTopo( Ponto2D ponto, double coeficienteAngular ); //Verifica a interseccao do ponto da reta com o topo

	Ponto2D interseccaoEsquerda( Ponto2D ponto, double coeficienteAngular ); //Verifica a interseccao do ponto da reta com a esquerda

	Ponto2D interseccaoDireita( Ponto2D ponto, double coeficienteAngular ); //Verifica a interseccao do ponto da reta com a direita

	Ponto2D interseccaoFundo( Ponto2D ponto, double coeficienteAngular ); //Verifica a interseccao do ponto da reta com o fundo



};

#endif // COHENSUTHERLAND_H
