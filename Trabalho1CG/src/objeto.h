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

#ifndef OBJETO_H
#define OBJETO_H

//Global Includes
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <list>
#include <vector>
//Local Includes
#include "tipos.hpp"
//#include "window.h" //Circular
#include "matriz.hpp"
#include "transformadas.hpp"

class Tranformadas;
class Objeto {
public:
	enum tipo {ponto, reta, wireframe}; //Enumerador com os tipos de objeto
	//-------------------------------------------
	std::string nome;//O nome do objeto
	//-------------------------------------------
	tipo tipoObjeto;//O tipo do objeto
	//-------------------------------------------

	Objeto() {}; //Construtor padrão
	//-------------------------------------------
	virtual ~Objeto() {}; //Destrutor

	Ponto2D obterCentro() {return set2DPoint( 0, 0 );}

	virtual void atualizarCoordenadaSCN( Matriz transformacao ) = 0;

	virtual void atualizarCoordenadaExibicao( Objeto * objeto ) = 0;
private:

};
//-------------------------------------------------------------------------------------------------
class Ponto : public Objeto {
public:
	//-------------------------------------------
	//Contrutor padrão
	Ponto( std::string nome ) {
		coordenada = set2DPoint( 0, 0 );
		tipoObjeto = Objeto::ponto;
		this->nome = nome;
	};
	//-------------------------------------------

	Ponto( std::string nome, Ponto2D coordenada );  //Contrutor parametrizado

	//-------------------------------------------
	Ponto2D obterCoordenada(); //Retorna a coordenada do ponto.
	//-------------------------------------------
	//void atualizarCoordenadaSCN( Ponto2D coordenada );
	//-------------------------------------------
	Ponto2D obterCentro();
	//-------------------------------------------
	virtual void atualizarCoordenadaSCN( Matriz transformacao );
	//-------------------------------------------
	Ponto2D obterCoordenadaSCN();//Retorna a coordenada do ponto em SCN
	//-------------------------------------------
	virtual void atualizarCoordenadaExibicao( Objeto * objeto );
private:

	Ponto2D coordenada; //coordenada do ponto no mundo;
	//-------------------------------------------
	Ponto2D coordenadaSCN;//Coordenada no SCN;
	//-------------------------------------------
	Ponto2D coordenadaExibicao;//Coordenada no mundo apos clip
};
//-------------------------------------------------------------------------------------------------

class Reta : public Objeto {
public:
	//-------------------------------------------
	//Cosntrutor padrão
	Reta( std::string nome ) {
		pontoInicial = set2DPoint( 0, 0 );
		pontoFinal = set2DPoint( 0, 0 );
		tipoObjeto = Objeto::reta;
		this->nome = nome;
	}
	//-------------------------------------------
	Reta( std::string nome, Ponto2D pontoInicial, Ponto2D pontoFinal );  //Contrutor parametrizado
	//-------------------------------------------
	Ponto2D obterCoordenadaInicial();//Retorna o ponto inicial da reta.
	//-------------------------------------------
	Ponto2D obterCoordenadaInicialSCN();
	//-------------------------------------------
	Ponto2D obterCoordenadaFinal();//Retorna o ponto final da reta.
	//-------------------------------------------
	Ponto2D obterCoordenadaFinalSCN();
	//-------------------------------------------
	Ponto2D obterCentro();
	//-------------------------------------------
	virtual void atualizarCoordenadaSCN( Matriz transformacao );
	//-------------------------------------------
	virtual void atualizarCoordenadaExibicao( Objeto * objeto );
private:
	Ponto2D pontoInicial, pontoInicialSCN;
	//-------------------------------------------
	Ponto2D pontoFinal, pontoFinalSCN;
	//-------------------------------------------
	Ponto2D pontoInicialExibicao, pontoFinalExibicao;

};
//-------------------------------------------------------------------------------------------------

class Wireframe: public Objeto {
public:
	//-------------------------------------------
	//Construtor padrão
	Wireframe( std::string nome ) {
		this->pontos.clear();
		this->pontosSCN.clear();
		this->pontosExibicao.clear();
		//this->pontos.push_back( set2DPoint( 0, 0 ) );
		this->nome = nome;
		this->tipoObjeto = Objeto::wireframe;
	}
	//-------------------------------------------
	Wireframe( std::string nome, std::vector<Ponto2D> pontos ); //Contrutor parametrizado
	//-------------------------------------------
	std::vector<Ponto2D> obterPontos();//Retorna um vetor com os pontos do poligono.
	//-------------------------------------------
	std::vector<Ponto2D> obterPontosSCN();//Retorna um vetor com os pontos SCN do poligono.
	//-------------------------------------------
	void adicionarPonto( Ponto2D ponto ); //Adiciona um ponto a lista.
	//-------------------------------------------
	Ponto2D obterCentro();
	//-------------------------------------------
	virtual void atualizarCoordenadaSCN( Matriz transformacao );
	//-------------------------------------------
	virtual void atualizarCoordenadaExibicao( Objeto * objeto );
private:
	std::vector<Ponto2D> pontos;//Vetor de pontos ordenados. O poligono é ligado seguinto a ordem desta lista.
	std::vector<Ponto2D> pontosSCN;//Pontos na SCN.
	std::vector<Ponto2D> pontosExibicao;//Pontos apos clip.
};


#endif // OBJETO_H

