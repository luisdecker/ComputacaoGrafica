/*
 * Lista de objetos de um Sistema Gráfico Interativo
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

#ifndef OBJECTFILE_H
#define OBJECTFILE_H
//Global Includes
#include <list>
#include <vector>
#include <iostream>
//Local Includes
#include "objeto.h"
#include "Subject.hpp"
#include "window.h"
#include "liangbarsky.h"
#include "cohensutherland.h"
#include "clipponto.h"
#include "WeilerAtherton.hpp"
#include "wireframeclipper.h"

class ObjectFile : public Subject {
public:

	ObjectFile() {
		objectFile = new std::vector<Objeto *>;
	}//Construtor Padrão
//-----------------------------------------------
	~ObjectFile() {
		delete objectFile;
	}

	//-----------------------------------------------
	void inserirObjeto( Objeto * objeto );  //Insere um objeto no fim do ObjectFile.
	//-----------------------------------------------
	std::vector<Objeto *> obterObjetos();  //Recupera os objetos do ObjectFile.
	//-----------------------------------------------
	void retirarObjeto( Objeto * objeto );  //Retira o dado objeto do ObjectFile.
	//-----------------------------------------------
	Objeto * obterObjetoNome( std::string nome );  //Obtém um objeto a partir do seu nome.
	//-----------------------------------------------
	void atualizarObjeto( Objeto * objeto ); //Modifica o objeto no ObjectFile.
	//-----------------------------------------------
	bool contemObjeto( std::string nome ); //Verifica se o objet com dado nome está na ObjectFile.
	//-----------------------------------------------
	void atualizaWindow( Window2D * window );
	//-----------------------------------------------
	void atualizaSCNTodosObjetos();//Atualiza o SCN de cada um dos objetos
	//-----------------------------------------------
	void setarLiamBarsky(){algoritmoClip = false;}//Seta o algoritmo de clipagem pra Liam Barsky
	//-----------------------------------------------
	void setarCohenSutherland(){algoritmoClip = true;}//Seta o algoritmo de clipagem pra Cohen Suthreland
private:

	void cliparObjetos();
	Window2D * window;
	std::vector<Objeto *> * objectFile;
	void atualizaSCN( Objeto * obj );
	bool algoritmoClip = false;
};

#endif // OBJECTFILE_H
