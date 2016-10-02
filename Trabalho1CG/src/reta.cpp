#include "objeto.h"

//-----------------------------------------------
Reta::Reta( std::string nome, Ponto2D pontoInicial, Ponto2D pontoFinal ) {
	this->pontoInicial = pontoInicial, this->pontoFinal = pontoFinal, this->nome = nome, this->tipoObjeto = Objeto::reta; desenhar = false;
}
//-----------------------------------------------
Ponto2D Reta::obterCoordenadaInicial() {
	return set2DPoint( this->pontoInicial.x, this->pontoInicial.y );
}
//-----------------------------------------------
Ponto2D Reta::obterCoordenadaInicialSCN() {
	return pontoInicialSCN;
}
//-----------------------------------------------
Ponto2D Reta::obterCoordenadaFinal() {
	return set2DPoint( this->pontoFinal.x, this->pontoFinal.y );
}
//-----------------------------------------------
Ponto2D Reta::obterCoordenadaFinalSCN() {
	return pontoFinalSCN;
}
//-----------------------------------------------
Ponto2D Reta::obterCentro() {
	double mediaX = ( this->pontoInicial.x + this->pontoFinal.x ) / 2;
	double mediaY = ( this->pontoInicial.y + this->pontoFinal.y ) / 2;
	return set2DPoint( mediaX, mediaY );

}
//-----------------------------------------------
void Reta::atualizarCoordenadaSCN( Matriz transformacao ) {
	if( desenhar ) {

		Matriz matrizCoordenadaInicial;
		Matriz matrizCoordenadaFinal;


		matrizCoordenadaInicial = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( pontoInicialExibicao ) );
		matrizCoordenadaFinal = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( pontoFinalExibicao ) );


		matrizCoordenadaInicial = matrizCoordenadaInicial * transformacao;
		matrizCoordenadaFinal = matrizCoordenadaFinal * transformacao;
		Ponto3D coordenadaHomogeneaInicial = Tranformadas::matrizParaPonto3D( matrizCoordenadaInicial );
		Ponto3D coordenadaHomogeneaFinal = Tranformadas::matrizParaPonto3D( matrizCoordenadaFinal );
		this->pontoInicialSCN = set2DPoint( coordenadaHomogeneaInicial.x, coordenadaHomogeneaInicial.y );
		this->pontoFinalSCN = set2DPoint( coordenadaHomogeneaFinal.x, coordenadaHomogeneaFinal.y );
	}

}
//-------------------------------------------
void Reta::atualizarCoordenadaExibicao( Objeto * objeto ) {
	if( objeto == nullptr ) {
		desenhar = false;
		return;
	}
	Reta * reta = dynamic_cast<Reta *>( objeto );
	this->pontoInicialExibicao = reta->obterCoordenadaInicial();
	this->pontoFinalExibicao = reta->obterCoordenadaFinal();

	/*	std::cout << "[Reta][" << __LINE__ << "] Atualizou coordenada de exibicao: (" << this->pontoInicial.x << " , " << this->pontoInicial.y
				  << ") -> (" << this->pontoFinal.x << " , " << this->pontoFinal.y << ")\nPara ("
				  << this->pontoInicialExibicao.x << " , " << this->pontoInicialExibicao.y
				  << ") -> (" << this->pontoFinalExibicao.x << " , " << this->pontoFinalExibicao.y << ")" << std::endl;*/

	desenhar = true;
}