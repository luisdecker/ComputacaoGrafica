/*
 * Tipos de dados para um Sistema Gráfico Interativo
 * Copyright (C) 2016  <Luís Gustavo Lorgus Decker> <decker@incod.ufsc.br>
 * 		       <Cesar Smaniotto Júnior>     <cesarsjb@gmail.com>
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

#pragma once
#include <cstdlib>


typedef struct Ponto2D {
	int x, y;
};
typedef struct Ponto3D {
	int x, y, z;
};

Ponto2D set2DPoint( int x, int y ) {
	Ponto2D retorno;
	retorno.x = x;
	retorno.y = y;
	return retorno;
}

Ponto2D set3DPoint( int x, int y, int z ) {
	Ponto3D retorno;
	retorno.x = x;
	retorno.y = y;
	retorno.z = z;
	return retorno;
}


