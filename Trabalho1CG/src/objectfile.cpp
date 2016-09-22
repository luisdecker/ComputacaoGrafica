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

#include "objectfile.h"
//-----------------------------------------------
bool ObjectFile::contemObjeto( std::string nome ) {
	for( Objeto * obj : *objectFile ) {
		if( obj->nome == nome ) {

			return true;
		}
	}
	return false;
}
//-----------------------------------------------
void ObjectFile::inserirObjeto( Objeto * objeto ) {

	atualizaSCN( objeto );

	if( contemObjeto( objeto->nome ) ) {
		return;
	}
	std::cout  << "[ObjectFile][" << __LINE__<<"] adicionando novo objeto " << objeto->nome << " [" << objeto << "] " << objectFile->size() << "+1\n";

	objectFile->push_back( objeto );
	notify();
}
//-----------------------------------------------
Objeto * ObjectFile::obterObjetoNome( std::string nome ) {


	for( int iterator = 0; iterator < objectFile->size(); iterator++ ) {
		if( objectFile->at( iterator )->nome == nome ) {
			atualizaSCN( objectFile->at( iterator ) );
			return  objectFile->at( iterator );
		}
	}
	std::cout << "[ObjectFile][" << __LINE__<<"]Não encontrou o objeto " << nome << "\n";
	return nullptr;
}
//-----------------------------------------------
void ObjectFile::atualizarObjeto( Objeto * objeto ) {
	atualizaSCN( objeto );
	for( int iterator = 0; iterator < objectFile->size(); iterator++ ) {
		if( objectFile->at( iterator )->nome == objeto->nome ) {
			objectFile->erase( objectFile->begin() + ( iterator ) );
			objectFile->push_back( objeto );
		}
	}
	notify();
}
//-----------------------------------------------
std::vector< Objeto * > ObjectFile::obterObjetos() {
	return std::vector<Objeto *>( *objectFile );
}
//-----------------------------------------------
void ObjectFile::retirarObjeto( Objeto * objeto ) {
	atualizaSCN( objeto );
	for( int iterator = 0; iterator < objectFile->size(); iterator++ ) {
		if( objectFile->at( iterator )->nome == objeto->nome ) {
			objectFile->erase( objectFile->begin() + ( iterator ) );
		}
	}
}
//----------------------------------------------
void ObjectFile::atualizaSCN( Objeto * obj ) {
	
	if( !( window == nullptr ) ) {
		obj->atualizarCoordenadaSCN( window->obterTransformacaoSCN() );

	}
}
//----------------------------------------------
void ObjectFile::atualizaWindow( Window2D * window ) {
	this->window = window;
	atualizaSCNTodosObjetos();
}

//----------------------------------------------
void ObjectFile::atualizaSCNTodosObjetos() {
	cliparObjetos();
	for( Objeto * obj : *objectFile ) {
		obj->atualizarCoordenadaSCN( window->obterTransformacaoSCN() );

	}
}
//-----------------------------------------------
void ObjectFile::cliparObjetos() {
	for( Objeto * obj : *objectFile ) {
		switch( obj->tipoObjeto ) {
			case Objeto::ponto: {
				Ponto * ponto = dynamic_cast <Ponto *>( obj );
				ClipPonto cliper( window );
				Ponto * pontoClipado = dynamic_cast<Ponto *>( cliper.clip( ponto ) );
				ponto->atualizarCoordenadaExibicao( pontoClipado );
				break;
			}
			case Objeto::reta: {
				Reta * reta = dynamic_cast<Reta *>( obj );
				std::cout << "[ObjectFile][" << __LINE__<<"] clipar uma reta (" << reta->obterCoordenadaInicial().x << " , " << reta->obterCoordenadaInicial().y
						  << ")  -->  (" << reta->obterCoordenadaFinal().x << " , " << reta->obterCoordenadaFinal().y << ")\n";
				Reta * retaClipada;
				if( algoritmoClip ) {
					CohenSutherland cliper( window );
					retaClipada = dynamic_cast<Reta *>( cliper.clip( reta ) );
				} else {
					LiangBarsky cliper( window );
					retaClipada = dynamic_cast<Reta *>( cliper.clip( reta ) );
				}
			//	std::cout << "[ObjectFile][" << __LINE__<<"] clipou uma reta (" << retaClipada->obterCoordenadaInicial().x << " , " << retaClipada->obterCoordenadaInicial().y
			//			  << ")  -->  (" << retaClipada->obterCoordenadaFinal().x << " , " << retaClipada->obterCoordenadaFinal().y << ")\n";
				reta->atualizarCoordenadaExibicao( retaClipada );
				break;
			}
			case Objeto::wireframe: {break;};
		}
	}
}





