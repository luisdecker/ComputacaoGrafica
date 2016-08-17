/*
 * ViewPort de um Sistema Gráfico Interativo
 * Copyright (C) 2016  <Luís Gustavo Lorgus Decker> <decker@incod.ufsc.br>
 * 		               <Cesar Smaniotto Júnior>     <cesarsjb@gmail.com>
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

#include "viewport.h"

//-----------------------------------------------
ViewPort::ViewPort( Ponto2D superiorEsquerdo, Ponto2D inferiorDireito ) {
	this->se = superiorEsquerdo, this->id = inferiorDireito;
}
//-----------------------------------------------
int ViewPort::obterXMaximo() {
	return id.x;
}
//-----------------------------------------------
int ViewPort::obterXMinimo() {
	return se.x;
}
//-----------------------------------------------
int ViewPort::obterYMaximo() {
	return id.y;
}
//-----------------------------------------------
int ViewPort::obterYMinimo() {
	return se.y;
}
//-----------------------------------------------
Ponto2D ViewPort::tranformarCoordenadas( Window window, Ponto2D ponto ) {// Confia que essa tripa ta certa.
	return set2DPoint( ( ( ponto.x - window.obterXMinimo() ) / window.obterXMaximo() - window.obterXMinimo() ) * obterXMaximo() - obterXMinimo(),
					   ( ( 1 - ( ponto.y - window.obterYMinimo() ) / ( window.obterYMaximo() - window.obterYMinimo() ) ) * ( obterYMaximo() - obterYMinimo() ) ));
}
//-----------------------------------------------
