/*
 * ViewPort de mundo de um Sistema Gráfico Interativo
 * Copyright (C) 2016  <Luís Gustavo Lorgus Decker> <decker@incod.ufsc.br>
 * 		  		       <Cesar Smaniotto Júnior>     <cesarsjb@gmail.com>
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

#ifndef VIEWPORT_H
#define VIEWPORT_H

//Global Includes
#include<iostream>
//Local Includes
#include "tipos.hpp"
#include "window.h"

class ViewPort {
public:
	ViewPort() {
		this->se = set2DPoint( 0, 0 );
		this->id = set2DPoint( 1, 1 );
	}//Construtor padrão
	//-----------------------------------------------
	ViewPort( Ponto2D superiorEsquerdo, Ponto2D inferiorDireito );//Contrutor parametrizado
	//-----------------------------------------------
	int obterXMinimo();//Retorna o x mínimo da ViewPort.
	//-----------------------------------------------
	int obterXMaximo();//Retorna o x máximo da ViewPort.
	//-----------------------------------------------
	int obterYMinimo();//Retorna o y minimo da ViewPort.
	//-----------------------------------------------
	int obterYMaximo();//Retorna o y máximo da ViewPort.
	//-----------------------------------------------
	int obterLargura();//Retorna a largura da viewport.
	//-----------------------------------------------
	int obterAltura();//Retorna a altura da viewport.
	//-----------------------------------------------
	/*Transforma de coordenadas de window diretamente para coordenadas de viewport (deprecated)*/
	Ponto2D tranformarCoordenadas( Window2D window, Ponto2D ponto );
	//-----------------------------------------------
	/*Transforma de SCN para coordenadas de viewport*/
	Ponto2D tranformarCoordenadasSCN( Window2D window, Ponto2D ponto );
	//-----------------------------------------------
	~ViewPort();
private:
	Ponto2D se;//Ponto superior esquerdo.
	Ponto2D id;//Ponto inferior direito.
};

#endif // VIEWPORT_H
