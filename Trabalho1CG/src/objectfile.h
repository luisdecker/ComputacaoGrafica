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
//Local Includes
#include "objeto.h"

class ObjectFile {
public:

	ObjectFile() {
		objectFile = new std::vector<Objeto>;
	}//Construtor Padrão

	~ObjectFile() {
		delete objectFile;
	}

	void inserirObjeto( Objeto objeto );  //Insere um objeto no fim do ObjectFile.

	std::vector<Objeto> obterObjetos();  //Recupera os objetos do ObjectFile.

	void retirarObjeto( Objeto objeto );  //Retira o dado objeto do ObjectFile.

	Objeto * obterObjetoNome( std::string nome );  //Obtém um objeto a partir do seu nome.

	void atualizarObjeto( Objeto objeto ); //Modifica o objeto no ObjectFile.

	bool contemObjeto( std::string nome ); //Verifica se o objet com dado nome está na ObjectFile.


private:

	std::vector<Objeto> * objectFile;
};

#endif // OBJECTFILE_H
