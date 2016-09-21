/*
 * Objeto de mundo de um Sistema Gráfico Interativo
 * Copyright (C) 2016  <Luís Gustavo Lorgus Decker> <decker@incod.ufsc.br>
 * 		       <Cesar Smaniotto Júnior>     <cesarsjb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "objeto.h"
#include "transformadas.hpp"// Isso é pra deixar minha IDE feliz. Não muda nada.


//-----------------------------------------------
Ponto::Ponto( std::string nome, Ponto2D coordenada ) {
	this->coordenada = coordenada, this->nome = nome, this->tipoObjeto = Objeto::ponto;
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
Reta::Reta( std::string nome, Ponto2D pontoInicial, Ponto2D pontoFinal ) {
	this->pontoInicial = pontoInicial, this->pontoFinal = pontoFinal, this->nome = nome, this->tipoObjeto = Objeto::reta;
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
//-------------------------------------------
Wireframe::Wireframe( std::string nome, std::vector< Ponto2D > pontos ) {
	this->pontos = pontos, this->nome = nome, this->tipoObjeto = Objeto::wireframe;
}
//-----------------------------------------------
std::vector< Ponto2D > Wireframe::obterPontos() {
	return std::vector<Ponto2D>( this->pontos );
}
//-----------------------------------------------
std::vector< Ponto2D > Wireframe::obterPontosSCN() {
	return std::vector<Ponto2D>( this->pontosSCN );
}
//-----------------------------------------------
void Wireframe::adicionarPonto( Ponto2D ponto ) {
	this->pontos.push_back( ponto );
}
//-----------------------------------------------
void Wireframe::setPreenchido( bool preenchido ) {
	this->preenchido = preenchido;
}
//-----------------------------------------------
bool Wireframe::ehPreenchido() {
	return this->preenchido;
}
//-----------------------------------------------
void Wireframe::setTodosPontosInclusos( bool todosPontosInclusos ) {
	this->todosPontosInclusos = todosPontosInclusos;
}
//-----------------------------------------------
bool Wireframe::possuiTodosPontosInclusos() {
	return this->todosPontosInclusos;
}
//-----------------------------------------------
Ponto2D Ponto::obterCentro() {
	return coordenada;
}
//-----------------------------------------------
Ponto2D Reta::obterCentro() {
	double mediaX = ( this->pontoInicial.x + this->pontoFinal.x ) / 2;
	double mediaY = ( this->pontoInicial.y + this->pontoFinal.y ) / 2;
	return set2DPoint( mediaX, mediaY );

}
//-----------------------------------------------
Ponto2D Wireframe::obterCentro() {
	double somaX;
	double somaY;
	for( Ponto2D ponto : this->obterPontos() ) {
		somaX += ponto.x;
		somaY += ponto.y;
	}
	double mediaX = somaX / pontos.size();
	double mediaY = somaY / pontos.size();
	return set2DPoint( mediaX, mediaY );
}
//-----------------------------------------------
void Ponto::atualizarCoordenadaSCN( Matriz transformacao ) {
	Matriz matrizCoordenada = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( coordenada ) );
	matrizCoordenada = matrizCoordenada * transformacao;
	Ponto3D coordenadaHomogenea = Tranformadas::matrizParaPonto3D( matrizCoordenada );
	this->coordenadaSCN = set2DPoint( coordenadaHomogenea.x, coordenadaHomogenea.y );

}
//-----------------------------------------------
void Reta::atualizarCoordenadaSCN( Matriz transformacao ) {
	Matriz matrizCoordenadaInicial = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( obterCoordenadaInicial() ) );
	Matriz matrizCoordenadaFinal = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( obterCoordenadaFinal() ) );
	matrizCoordenadaInicial = matrizCoordenadaInicial * transformacao;
	matrizCoordenadaFinal = matrizCoordenadaFinal * transformacao;
	Ponto3D coordenadaHomogeneaInicial = Tranformadas::matrizParaPonto3D( matrizCoordenadaInicial );
	Ponto3D coordenadaHomogeneaFinal = Tranformadas::matrizParaPonto3D( matrizCoordenadaFinal );
	this->pontoInicialSCN = set2DPoint( coordenadaHomogeneaInicial.x, coordenadaHomogeneaInicial.y );
	this->pontoFinalSCN = set2DPoint( coordenadaHomogeneaFinal.x, coordenadaHomogeneaFinal.y );

}

//-----------------------------------------------
void Wireframe::atualizarCoordenadaSCN( Matriz transformacao ) {
	std::vector<Ponto2D> coordenadasSCN;
	for( Ponto2D coordenada : obterPontos() ) {
		Matriz matrizCoordenada = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( coordenada ) );
		matrizCoordenada = matrizCoordenada * transformacao;
		Ponto3D coordenadaHomogenea = Tranformadas::matrizParaPonto3D( matrizCoordenada );
		Ponto2D coordenadaSCN = set2DPoint( coordenadaHomogenea.x, coordenadaHomogenea.y );
		coordenadasSCN.push_back( coordenadaSCN );
	}
	this->pontosSCN = coordenadasSCN;
}

//-----------------------------------------------
void Ponto::atualizarCoordenadaExibicao( Objeto * objeto ) {
	Ponto * ponto = dynamic_cast<Ponto *>( objeto );
	this->coordenadaExibicao = ponto->coordenada;

}
//-------------------------------------------
void Reta::atualizarCoordenadaExibicao( Objeto * objeto ) {
	Reta * reta = dynamic_cast<Reta *>( objeto );

}
//-------------------------------------------
void Wireframe::atualizarCoordenadaExibicao( Objeto * objeto ) {

}
//-------------------------------------------


















