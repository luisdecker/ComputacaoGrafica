/*
 * Window de um Sistema Gráfico Interativo
 * Copyright (C) 2016  <Luís Gustavo Lorgus Decker> <decker@incod.ufsc.br>
 * 		       <Cesar Smaniotto Júnior>     <cesarsjb@gmail.com>
 **
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

#ifndef WINDOW_H
#define WINDOW_H
#include "tipos.hpp"

class Window2D {
public:
	Window2D() { //Construtor padrão
		ie = set2DPoint( 0, 0 );
		sd = set2DPoint( 1, 1 );

	}
	//-----------------------------------------------
	Window2D( Ponto2D inferiorEsquerdo, Ponto2D superiorDireito );
	//-----------------------------------------------
	int obterXMinimo();//Retorna o x mínimo da window.
	//-----------------------------------------------
	int obterXMaximo();//Retorna o x máximo da window.
	//-----------------------------------------------
	int obterYMinimo();//Retorna o y minimo da window.
	//-----------------------------------------------
	int obterYMaximo();//Retorna o y máximo da window.
	//-----------------------------------------------
	//~Window2D();
	Ponto2D inferiorEsquerdo() {return ie;}
	Ponto2D superiorDireito() {return sd;}
private:
	Ponto2D ie;//Ponto inferior Esquerdo.
	Ponto2D sd;//Ponto superior Direito.
};

#endif // WINDOW_H
