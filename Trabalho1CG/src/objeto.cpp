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
//-------------------------------------------
Wireframe::Wireframe( std::string nome, std::vector< Ponto2D > pontos ) {
	this->pontos = pontos, this->nome = nome, this->tipoObjeto = Objeto::wireframe; desenhar = false;
}
//-----------------------------------------------
std::vector< Ponto2D > Wireframe::obterPontos() {
	return std::vector<Ponto2D>( this->pontos );
}
//-----------------------------------------------
std::vector<std::vector< Ponto2D >> Wireframe::obterPontosSCN() {
	return std::vector<std::vector<Ponto2D>>( this->pontosSCN );
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
//-----------------------------------------------
void Wireframe::atualizarCoordenadaSCN( Matriz transformacao ) {
	if( desenhar ) {
		std::vector<std::vector<Ponto2D> > pontosSCN;
		for( Wireframe * wireframe : pontosExibicao ) {
			if( wireframe != nullptr ) {
				std::vector<Ponto2D> pontosMundoObj = wireframe->obterPontos(); // Pontos originais de cada wireframe (subobjeto)
				std::vector<Ponto2D> pontosSCNObjeto;//Pontos convertidos de cada wireframe (subobjeto)
				for( Ponto2D ponto : pontosMundoObj ) {
					Matriz matPonto( Tranformadas::ponto2DParaHomogeneo( ponto ) );
					matPonto = matPonto * transformacao;
					Ponto3D pontoSCNHomogeneo = Tranformadas::matrizParaPonto3D( matPonto );
					Ponto2D novoPonto = set2DPoint( pontoSCNHomogeneo.x, pontoSCNHomogeneo.y ); //Um ponto em coordenadas homogeneas
					pontosSCNObjeto.push_back( novoPonto );
				}//Aqui, completou a lista de um dos subobjetos
				pontosSCN.push_back( pontosSCNObjeto );
			}
		}//Completou a lista de subobjetos

		this->pontosSCN = pontosSCN;
	}
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
//-------------------------------------------
void Reta::atualizarCoordenadaExibicao( Objeto * objeto ) {
	if( objeto == nullptr ) {
		desenhar = false;
		return;
	}
	Reta * reta = dynamic_cast<Reta *>( objeto );
	this->pontoInicialExibicao = reta->obterCoordenadaInicial();
	this->pontoFinalExibicao = reta->obterCoordenadaFinal();

	std::cout << "[Reta][" << __LINE__ << "] Atualizou coordenada de exibicao: (" << this->pontoInicial.x << " , " << this->pontoInicial.y
			  << ") -> (" << this->pontoFinal.x << " , " << this->pontoFinal.y << ")\nPara ("
			  << this->pontoInicialExibicao.x << " , " << this->pontoInicialExibicao.y
			  << ") -> (" << this->pontoFinalExibicao.x << " , " << this->pontoFinalExibicao.y << ")" << std::endl;

	desenhar = true;
}
//-------------------------------------------
void Wireframe::atualizarCoordenadaExibicao( Objeto * objeto ) {
	if( objeto == nullptr ) {
		this->pontosExibicao = std::vector<Wireframe *>();
		desenhar = false;
		return;
	}
	Wireframe * wireframe = dynamic_cast<Wireframe *>( objeto );
	this-> pontosExibicao = wireframe->pontosExibicao;
	desenhar = true;
}
//-------------------------------------------
void Wireframe::atualizarCoordenadaExibicao( std::vector< Wireframe * > subObjetos ) {
	if( subObjetos.empty() ) {
		this->pontosExibicao = std::vector<Wireframe *>();
		desenhar = false;
		return;
	}
	this->pontosExibicao = subObjetos;
	desenhar = true;
}


















