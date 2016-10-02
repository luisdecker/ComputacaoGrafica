#include "objeto.h"

//-----------------------------------------------
Ponto::Ponto( std::string nome, Ponto2D coordenada ) {
	this->coordenada = coordenada, this->nome = nome, this->tipoObjeto = Objeto::ponto; desenhar = false;
}
//-----------------------------------------------
Ponto2D Ponto::obterCoordenada() {
	return  set2DPoint( this->coordenada.x, this->coordenada.y );
}
//-----------------------------------------------
Ponto2D Ponto::obterCoordenadaSCN() {
	return coordenadaSCN;
}
//-----------------------------------------------
Ponto2D Ponto::obterCentro() {
	return coordenada;
}
//-----------------------------------------------
void Ponto::atualizarCoordenadaSCN( Matriz transformacao ) {

	Matriz matrizCoordenada;
	if( desenhar ) {
		matrizCoordenada = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( coordenadaExibicao ) );
	} else {
		matrizCoordenada = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( coordenada ) );
	}
	matrizCoordenada = matrizCoordenada * transformacao;
	Ponto3D coordenadaHomogenea = Tranformadas::matrizParaPonto3D( matrizCoordenada );
	this->coordenadaSCN = set2DPoint( coordenadaHomogenea.x, coordenadaHomogenea.y );

}
//-----------------------------------------------
void Ponto::atualizarCoordenadaExibicao( Objeto * objeto ) {
	if( objeto == nullptr ) {
		desenhar = false;
		return;
	}
	Ponto * ponto = dynamic_cast<Ponto *>( objeto );
	this->coordenadaExibicao = ponto->coordenada;
	desenhar = true;

}