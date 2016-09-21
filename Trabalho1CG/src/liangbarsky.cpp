#include "liangbarsky.h"
LiangBarsky::LiangBarsky( Window2D * window ): janela( window ) {

}
//-----------------------------------------------
Objeto * LiangBarsky::clip( Objeto * objeto ) {

	if( ! objeto->tipoObjeto == Objeto::reta ) {
		std::cout << "[WARNING][LiangBarsky] Tentou clipar um objeto que nao ´e uma reta!\n";
		return nullptr;
	}
	Reta * retaOrg = dynamic_cast<Reta *>( objeto );
	//Rotaciona a reta para trabalharmos em coordenadas da window
	Reta * reta = dynamic_cast<Reta *>( Tranformadas::rotacionar( retaOrg, janela->obterRotacao(), janela->obterCentro() ) );
	retaOrg = reta;
	
	double t0 = 0.;
	double t1 = 1.;
	double xDelta = retaOrg->obterCoordenadaFinal().x - retaOrg->obterCoordenadaInicial().x;
	double yDelta = retaOrg->obterCoordenadaFinal().y - retaOrg->obterCoordenadaInicial().y;
	double p, q, r;

	for( int canto = 0; canto < 4; canto++ ) {
		switch( canto ) {
			case 0: {
				p = -xDelta;
				q = -( janela->obterXMinimo() - retaOrg->obterCoordenadaInicial().x );
				break;
			}
			case 1: {
				p = xDelta;
				q = ( janela->obterXMaximo() - retaOrg->obterCoordenadaInicial().x );
				break;
			}
			case 2: {
				p = -yDelta;
				q = - ( janela->obterYMinimo() - retaOrg->obterCoordenadaInicial().y );
				break;
			}
			case 3: {
				p = yDelta;
				q = ( janela->obterYMaximo() - retaOrg->obterCoordenadaInicial().y );
				break;
			}
		}//switch caso
		r = q / p;
		if( p == 0 && q < 0 ) {
			return nullptr; //Linha completamente fora
		}

		if( p < 0 ) {
			if( r > t1 ) {
				return nullptr; //Outra linha fora
			} else {
				if( r > t0 ) {
					t0 = r;
				}
			}
		} else {
			if( p > 0 ) {
				if( r < t0 ) {
					return nullptr;
				} else if( r < t1 ) {
					t1 = r;
				}

			}
		}
	}
	Ponto2D novoInicial = set2DPoint( retaOrg->obterCoordenadaInicial().x + t0 * xDelta, retaOrg->obterCoordenadaInicial().y + t0 * yDelta );
	Ponto2D novoFinal = set2DPoint( retaOrg->obterCoordenadaInicial().x + t1 * xDelta, retaOrg->obterCoordenadaInicial().y + t1 * yDelta );
	Reta * novaReta = new Reta( retaOrg->nome, novoInicial, novoFinal );
	return novaReta;
}