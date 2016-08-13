/*
 * Objeto de mundo de um Sistema Gráfico Interativo
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

#ifndef OBJETO_H
#define OBJETO_H

//Global Includes
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <list>
//Local Includes
#include "tipos.hpp"

class Objeto
{
public:
    enum tipo {ponto,reta,wireframe}; //Enumerador com os tipos de objeto

    std::string nome;//O nome do objeto

    Objeto();//Construtor padrão
    ~Objeto();//Destrutor
private:

};

class Ponto : public Objeto
{
public:

    //Contrutor padrão
    Ponto() {
        coordenada.x = 0;
        coordenada.y=0;
    };

    Ponto ( int x, int y ); //Contrutor parametrizado

private:
    Ponto2D coordenada; //coordenada do ponto;
};

class Reta : public Objeto
{

};

class wireframe: public Objeto
{

};


#endif // OBJETO_H
