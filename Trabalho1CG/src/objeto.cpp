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


//-----------------------------------------------
Ponto::Ponto( std::string nome, Ponto2D coordenada ) {
    this->coordenada = coordenada, this->nome = nome, this->tipoObjeto = Objeto::ponto;
}
//-----------------------------------------------
Ponto2D Ponto::obterCoordenada() {
    return  set2DPoint( this->coordenada.x, this->coordenada.y );
}
//-------------------------------------------
Reta::Reta( std::string nome, Ponto2D pontoInicial, Ponto2D pontoFinal ) {
    this->pontoInicial = pontoInicial, this->pontoFinal = pontoFinal, this->nome = nome, this->tipoObjeto = Objeto::reta;
}
//-----------------------------------------------
Ponto2D Reta::obterCoordenadaInicial() {
    return set2DPoint( this->pontoInicial.x, this->pontoInicial.y );
}

//-------------------------------------------
Ponto2D Reta::obterCoordenadaFinal() {
    return set2DPoint( this->pontoFinal.x, this->pontoFinal.y );
}
//-------------------------------------------
Wireframe::Wireframe( std::string nome, std::vector< Ponto2D > pontos ) {
    this->pontos = pontos, this->nome = nome, this->tipoObjeto = Objeto::wireframe;
}
//-----------------------------------------------
std::vector< Ponto2D > Wireframe::obterPontos() {
    return std::vector<Ponto2D>( this->pontos );
}
//-------------------------------------------

void Wireframe::adicionarPonto(Ponto2D ponto) {
    this->pontos.push_back(ponto);
}



