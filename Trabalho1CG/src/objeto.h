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
private:
	//-------------------------------------------
	Ponto2D coordenada; //coordenada do ponto;
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
	Ponto2D obterCoordenadaFinal();//Retorna o ponto final da reta.
	//-------------------------------------------
private:
	Ponto2D pontoInicial;
	Ponto2D pontoFinal;

};
//-------------------------------------------------------------------------------------------------

class Wireframe: public Objeto {
public:
	//-------------------------------------------
	//Construtor padrão
	Wireframe( std::string nome ) {
		this->pontos.clear();
		this->pontos.push_back( set2DPoint( 0, 0 ) );
		this->nome = nome;
		this->tipoObjeto = Objeto::wireframe;
	}
	//-------------------------------------------
	Wireframe( std::string nome, std::vector<Ponto2D> pontos ); //Contrutor parametrizado
	//-------------------------------------------
	std::vector<Ponto2D> obterPontos();//Retorna um vetor com os pontos do poligono.
	//-------------------------------------------
private:
	std::vector<Ponto2D> pontos;//Vetor de pontos ordenados. O poligono é ligado seguinto a ordem desta lista.
};


#endif // OBJETO_H
