#include "objeto.h"
#include "transformadas.hpp"

double CurvaBezier::gerarBk( double l, double k, double t ) {
	long long int fatL = Tranformadas::fatorial( l );
	long long int fatK = Tranformadas::fatorial( k );
	long long int fatLMenosK = Tranformadas::fatorial( l - k );
	double parte1 = fatL / ( fatK * ( fatLMenosK ) );
	double parte2 = pow( 1 - t, l - k );
	double parte3 = pow( t, k );
	return parte1 * parte2 * parte3;
}
//-----------------------------------------------
Ponto2D CurvaBezier::calculaPonto( double t ) {
	int L = pontosDeControle.size() - 1;
	double somaX = 0;
	for( int k = 0; k <= L; k++ ) {
		somaX += gerarBk( L, k, t ) * pontosDeControle[k].x;
	}
	double somaY = 0;
	for( int k = 0; k <= L; k++ ) {
		somaY += gerarBk( L, k, t ) * pontosDeControle[k].y;
	}
	return set2DPoint( somaX, somaY );
}
//-----------------------------------------------
std::vector<Ponto2D> CurvaBezier::caculaPontos( int numeroPontos ) {
	std::vector<Ponto2D> pontosDaCurva;
	double passo = 1. / numeroPontos;
	for( double t = 0; t < 1 ; t += passo ) {

		pontosDaCurva.push_back( calculaPonto( t ) );
	}
	return pontosDaCurva;
}
//-----------------------------------------------
void CurvaBezier::atualizarCoordenadaExibicao( Objeto * objeto ) {
	if( objeto == nullptr ) {
		desenhar = false;
		return;
	}
	CurvaBezier * curva = dynamic_cast<CurvaBezier *>( objeto );
	if( curva->pontosExibicao.empty() ) {
		desenhar = false;
		return;
	}
	this->pontosExibicao = curva->pontosExibicao;
	desenhar = true;	
}
//-----------------------------------------------
void CurvaBezier::atualizaCoordenadasControle( std::vector<Ponto2D> coordenadas ) {
	if( coordenadas.size() > 4 ) {
		this->pontosDeControle = coordenadas;
		this->pontosCalculados = caculaPontos( resolucao );
	}
}
//----------------------------------------------
void CurvaBezier::atualizarCoordenadaSCN( Matriz transformacao ) {
	if( desenhar ) {
		std::vector<Ponto2D> pontosSCN;
		for( Ponto2D ponto : this->pontosExibicao ) {
			Matriz matPonto( Tranformadas::ponto2DParaHomogeneo( ponto ) );
			matPonto = matPonto * transformacao;
			Ponto3D novoPontoHomogeneo = Tranformadas::matrizParaPonto3D( matPonto );
			pontosSCN.push_back( Ponto2D( novoPontoHomogeneo.x, novoPontoHomogeneo.y ) );
		}
		this->pontosSCN = pontosSCN;
	}
}
//-----------------------------------------------
std::vector<Ponto2D> CurvaBezier::obterCoordenadasSCN() {
	return std::vector<Ponto2D> ( pontosSCN );
}