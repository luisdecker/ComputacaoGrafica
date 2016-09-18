/*
 * Matriz de pontos flutuantes para um sistema gráfico interativo
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

#ifndef MATRIZ_H
#define MATRIZ_H

#include <cassert>
#include "tipos.hpp"
#include <iostream>

class Matriz {
public:
	Matriz() {std::cout << "Criou uma matriz padrão, não sei como\n";}
	Matriz( int linhas, int colunas );
	double & at( int linha, int coluna );
	Matriz operator * ( const Matriz outra ) {return multiplicar( outra );}
	Matriz operator + ( const Matriz outra ) {return somar( outra );}
	Matriz operator - ( const Matriz outra ) {return subtrair( outra );}
	bool  operator == ( const Matriz outra ) {return igual( outra );}
	Matriz transpor();
	int numLinhas() {return linhas;}
	int numColunas() {return colunas;}
	void print();
private:
	int linhas, colunas;
	double * data;
	Matriz multiplicar( Matriz outra );
	Matriz somar( Matriz outra );
	Matriz subtrair( Matriz outra );
	bool igual( Matriz outra );

};

#endif // MATRIZ_H
