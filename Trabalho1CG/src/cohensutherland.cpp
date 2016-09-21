#include "cohensutherland.h"

CohenSutherland::CohenSutherland( Window2D * janela ) : janela( janela ) {

}
//-----------------------------------------------
Objeto * CohenSutherland::clip( Objeto * objeto ) {
	if( objeto->tipoObjeto != Objeto::reta ) {
		std::cout << "[WARNING][CohenSutherland] Enviado um objeto nao-reta para clipagem!\n";
		return nullptr;
	}
	Reta * retaorg = dynamic_cast<Reta *>( objeto );

	//Rotaciona a reta para trabalharmos em coordenadas da window
	Reta * reta = dynamic_cast<Reta *>( Tranformadas::rotacionar( retaorg, janela->obterRotacao(), janela->obterCentro() ) );
	binCode codigoInicio = checkCode( reta->obterCoordenadaInicial() );
	binCode codigoFim = checkCode( reta->obterCoordenadaFinal() );
	binCode codigoAnalise = codigoInicio & codigoFim;
	binCode zero;
	zero.reset();
	if( codigoInicio == codigoFim ) { //codigos iguais
		if( codigoInicio == zero ) { //Completamente dentro
			return retaorg; //Retorna a reta original, ja que os dois pontos dela estao Completamente dentro da window!
		} else { //comeca e termina no mesmo quadrante, fora da window
			return nullptr;
		}
	} else { //codigos diferentes
		if( codigoAnalise == zero ) {//and dos codigos = 0 -> possivel desenho
			double coeficienteAngular = obterCoeficienteAngular( reta );
			bool desenhar = true; //Se alguem decidir que desenhar e false, entao nao desenha! (Ponto nao tem interseccao com ninguem que deveria ter)
			Ponto2D novoPonto1;
			Ponto2D novoPonto2;
			if( coeficienteAngular != 0 ) {

				//Tratamento do ponto 1

				switch( codigoInicio.obterDirecaoCodigo() ) {

					case CohenSutherland::norte: {// possivelmente vai trombar com o topo

						novoPonto1 = interseccaoTopo( reta->obterCoordenadaInicial(), coeficienteAngular );
						desenhar = pontoNaWindow( novoPonto1 );

						break;
					}
					case CohenSutherland::nordeste: {
						Ponto2D tentativa = interseccaoTopo( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						tentativa = interseccaoDireita( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						desenhar = false;
						break;
					}
					case CohenSutherland::leste: {
						novoPonto1 = interseccaoDireita( reta->obterCoordenadaInicial(), coeficienteAngular );
						desenhar = pontoNaWindow( novoPonto1 );
						break;
					}
					case CohenSutherland::sudeste: {
						Ponto2D tentativa = interseccaoFundo( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						tentativa = interseccaoDireita( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						desenhar = false;
						break;
					}
					case CohenSutherland::sul: {
						novoPonto1 = interseccaoFundo( reta->obterCoordenadaInicial(), coeficienteAngular );
						desenhar = pontoNaWindow( novoPonto1 );
						break;

					}
					case CohenSutherland::sudoeste: {
						Ponto2D tentativa = interseccaoFundo( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						tentativa = interseccaoEsquerda( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						desenhar = false;
						break;
					}
					case CohenSutherland::oeste: {
						novoPonto1 = interseccaoEsquerda( reta->obterCoordenadaInicial(), coeficienteAngular );
						desenhar = pontoNaWindow( novoPonto1 );
						break;
					}
					case CohenSutherland::noroeste: {
						Ponto2D tentativa = interseccaoTopo( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						tentativa = interseccaoEsquerda( reta->obterCoordenadaInicial(), coeficienteAngular );
						if( pontoNaWindow( tentativa ) ) {
							desenhar = true;
							novoPonto1 = tentativa;
							break;
						}
						desenhar = false;
						break;
					}
					case CohenSutherland::centro: {//Ta dentro, deixa la!
						novoPonto1 = reta->obterCoordenadaInicial();
						desenhar = true;
						break;
					}

				}//Switch codigo ponto inicial
				//Informacoes sobre o ponto inicial prontas. Verificar se ele esta desenhavel
				if( desenhar ) {//primeiro ponto interceptou a window!
					direcao direcaoPonto2 = codigoFim.obterDirecaoCodigo();
					switch( codigoFim.obterDirecaoCodigo() ) {
						case CohenSutherland::norte: {// possivelmente vai trombar com o topo

							novoPonto2 = interseccaoTopo( reta->obterCoordenadaInicial(), coeficienteAngular );
							desenhar = pontoNaWindow( novoPonto2 );

							break;
						}
						case CohenSutherland::nordeste: {
							Ponto2D tentativa = interseccaoTopo( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							tentativa = interseccaoDireita( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							desenhar = false;
							break;
						}
						case CohenSutherland::leste: {
							novoPonto2 = interseccaoDireita( reta->obterCoordenadaInicial(), coeficienteAngular );
							desenhar = pontoNaWindow( novoPonto2 );
							break;
						}
						case CohenSutherland::sudeste: {
							Ponto2D tentativa = interseccaoFundo( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							tentativa = interseccaoDireita( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							desenhar = false;
							break;
						}
						case CohenSutherland::sul: {
							novoPonto2 = interseccaoFundo( reta->obterCoordenadaInicial(), coeficienteAngular );
							desenhar = pontoNaWindow( novoPonto2 );
							break;

						}
						case CohenSutherland::sudoeste: {
							Ponto2D tentativa = interseccaoFundo( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							tentativa = interseccaoEsquerda( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							desenhar = false;
							break;
						}
						case CohenSutherland::oeste: {
							novoPonto2 = interseccaoEsquerda( reta->obterCoordenadaInicial(), coeficienteAngular );
							desenhar = pontoNaWindow( novoPonto2 );
							break;
						}
						case CohenSutherland::noroeste: {
							Ponto2D tentativa = interseccaoTopo( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							tentativa = interseccaoEsquerda( reta->obterCoordenadaInicial(), coeficienteAngular );
							if( pontoNaWindow( tentativa ) ) {
								desenhar = true;
								novoPonto2 = tentativa;
								break;
							}
							desenhar = false;
							break;
						}
						case CohenSutherland::centro: {//Ta dentro, deixa la!
							novoPonto2 = reta->obterCoordenadaInicial();
							desenhar = true;
							break;
						}
					}//Switch codigo 2
					Reta * novaReta = new Reta( objeto->nome, novoPonto1, novoPonto2 );
					return novaReta;
				}/*Desenhar?*/else {
					//O primeiro ponto nao interceptou a window nem ta dentro. Nao desenha!!!
					return nullptr;
				}//Else desenhar
			} else {//coeficiente Angular = 0
				//Tratamento Ponto 1
				switch( codigoInicio.obterDirecaoCodigo() ) {

					case CohenSutherland::leste: {
						novoPonto1 = set2DPoint( janela->obterXMaximo(), reta->obterCoordenadaInicial().y );
						desenhar = true;
						break;
					}
					case CohenSutherland::oeste: {
						novoPonto1 = set2DPoint( janela->obterXMinimo(), reta->obterCoordenadaInicial().y );
						break;
					}
					case CohenSutherland::centro: {//Ponto ja ta dentro, deixa assim mesmo
						novoPonto1 = set2DPoint( reta->obterCoordenadaInicial().x, reta->obterCoordenadaInicial().y );
						break;
					}
				}//switch ponto 1
				//Tratamento ponto 2
				switch( codigoFim.obterDirecaoCodigo() ) {
					case CohenSutherland::leste: {
						novoPonto2 = set2DPoint( janela->obterXMaximo(), reta->obterCoordenadaInicial().y );
						desenhar = true;
						break;
					}
					case CohenSutherland::oeste: {
						novoPonto2 = set2DPoint( janela->obterXMinimo(), reta->obterCoordenadaInicial().y );
						desenhar = true;
						break;
					}
					case CohenSutherland::centro: {//Ponto ja ta dentro, deixa assim mesmo
						novoPonto2 = set2DPoint( reta->obterCoordenadaInicial().x, reta->obterCoordenadaInicial().y );
						desenhar = true;
						break;
					}
				}//switch ponto 2
				return new Reta( objeto->nome, novoPonto1, novoPonto2 );
			}
		} else {//and dos codigos != 0 -> nao desenha
			return nullptr;
		}
	}//codigos diferentes
	std::cout << "[WARNING][CohenSutherland] Nao coberto por nenhum caso. Comportamento anormal.\n";
	return nullptr;
}
//-----------------------------------------------
Ponto2D CohenSutherland::interseccaoTopo( Ponto2D ponto, double coeficienteAngular ) {
	return
		set2DPoint( ponto.x + ( 1 / coeficienteAngular * ( janela->obterYMaximo() - ponto.y ) ), janela->obterYMaximo() );
}
//-----------------------------------------------
Ponto2D CohenSutherland::interseccaoDireita( Ponto2D ponto, double coeficienteAngular ) {
	return
		set2DPoint( janela->obterXMaximo(),    coeficienteAngular * ( janela->obterXMaximo() - ponto.x ) + ponto.y );
}
//-----------------------------------------------
Ponto2D CohenSutherland::interseccaoEsquerda( Ponto2D ponto, double coeficienteAngular ) {
	return
		set2DPoint( janela->obterXMinimo(), coeficienteAngular * ( janela->obterXMinimo() - ponto.x ) + ponto.y );
}
//-----------------------------------------------
Ponto2D CohenSutherland::interseccaoFundo( Ponto2D ponto, double coeficienteAngular ) {
	return
		set2DPoint( ponto.x + ( 1 / coeficienteAngular * ( janela->obterYMinimo() - ponto.y ) ), janela->obterYMinimo() );
}
//-----------------------------------------------
CohenSutherland::binCode CohenSutherland::checkCode( Ponto2D ponto ) {
	binCode retorno;

	retorno.setBit0( ponto.y > janela->obterYMaximo() );
	retorno.setBit1( ponto.y < janela->obterYMinimo() );
	retorno.setBit2( ponto.x > janela->obterXMaximo() );
	retorno.setBit3( ponto.x < janela->obterXMinimo() );

	return retorno;
}
//-----------------------------------------------
double CohenSutherland::obterCoeficienteAngular( Reta * reta ) {
	Ponto2D pontoInicial = reta->obterCoordenadaInicial();
	Ponto2D pontoFinal = reta->obterCoordenadaFinal();
	return ( pontoInicial.y - pontoFinal.y ) / ( pontoInicial.x - pontoFinal.x );
}
//-----------------------------------------------
bool CohenSutherland::pontoNaWindow( Ponto2D ponto ) {
	return
		ponto.x >= janela->obterXMinimo() &&
		ponto.x <= janela->obterXMaximo() &&
		ponto.y >= janela->obterYMinimo() &&
		ponto.y <= janela->obterYMaximo();
}
//-----------------------------------------------


/*Operacoes de codigo binario*/
//-----------------------------------------------
CohenSutherland::binCode CohenSutherland::binCode::operator&( CohenSutherland::binCode other ) {
	binCode retorno;
	retorno.setBit0( this->code[0] && other.code[0] );
	retorno.setBit1( this->code[1] && other.code[1] );
	retorno.setBit2( this->code[2] && other.code[2] );
	retorno.setBit3( this->code[3] && other.code[3] );
	return retorno;
}
//-----------------------------------------------
bool CohenSutherland::binCode::operator==( CohenSutherland::binCode other ) {
	return code[0] == other.code[0] &&
		   code[1] == other.code[1] &&
		   code[2] == other.code[2] &&
		   code[3] == other.code[3];
}
//-----------------------------------------------
CohenSutherland::direcao CohenSutherland::binCode::obterDirecaoCodigo() {
	switch( codeToInt() ) {
		case 1000: return norte;
		case 1010: return nordeste;
		case 10: return leste;
		case 110: return sudeste;
		case 100: return sul;
		case 101: return sudoeste;
		case 1: return oeste;
		case 1001: return noroeste;
		case 0: return centro;

	}
}
//-----------------------------------------------
int CohenSutherland::binCode::codeToInt() {
	return ( ( ( int ) code[0] * 1000 ) + ( ( int ) code[1] * 100 ) + ( ( int ) code[2] * 10 ) + ( ( int ) code[3] * 1 ) );
}




/*

					 case CohenSutherland::norte: {
						break;
					}
					case CohenSutherland::nordeste: {
						break;
					}
					case CohenSutherland::leste: {
						break;
					}
					case CohenSutherland::sudeste: {
						break;
					}
					case CohenSutherland::sul: {
						break;
					}
					case CohenSutherland::sudoeste: {
						break;
					}
					case CohenSutherland::oeste: {
						break;
					}
					case CohenSutherland::noroeste: {
						break;
					}
					case CohenSutherland::centro: {
						break;
					}

 */






