#include "objeto.h"

//-------------------------------------------
Wireframe::Wireframe( std::string nome, std::vector< Ponto2D > pontos ) {
	this->pontos = pontos, this->nome = nome, this->tipoObjeto = Objeto::wireframe; desenhar = false;
}
//-----------------------------------------------
std::vector< Ponto2D > Wireframe::obterPontos() {
	return std::vector<Ponto2D>( this->pontos );
}
//-----------------------------------------------
std::vector<std::vector< Ponto2D >> Wireframe::obterPontosSCN() {
	return std::vector<std::vector<Ponto2D>>( this->pontosSCN );
}
//-----------------------------------------------
void Wireframe::adicionarPonto( Ponto2D ponto ) {
	this->pontos.push_back( ponto );
}
//-----------------------------------------------
void Wireframe::setPreenchido( bool preenchido ) {
	this->preenchido = preenchido;
}
//-----------------------------------------------
bool Wireframe::ehPreenchido() {
	return this->preenchido;
}
//-----------------------------------------------
void Wireframe::setTodosPontosInclusos( bool todosPontosInclusos ) {
	this->todosPontosInclusos = todosPontosInclusos;
}
//-----------------------------------------------
bool Wireframe::possuiTodosPontosInclusos() {
	return this->todosPontosInclusos;
}


//-----------------------------------------------
Ponto2D Wireframe::obterCentro() {
	double somaX;
	double somaY;
	for( Ponto2D ponto : this->obterPontos() ) {
		somaX += ponto.x;
		somaY += ponto.y;
	}
	double mediaX = somaX / pontos.size();
	double mediaY = somaY / pontos.size();
	return set2DPoint( mediaX, mediaY );
}


//-----------------------------------------------
void Wireframe::atualizarCoordenadaSCN( Matriz transformacao ) {
	if( desenhar ) {
		if( preenchido ) {
			std::vector<std::vector<Ponto2D> > pontosSCN;
			for( Wireframe * wireframe : pontosExibicao ) {
				if( wireframe != nullptr ) {
					std::vector<Ponto2D> pontosMundoObj = wireframe->obterPontos(); // Pontos originais de cada wireframe (subobjeto)
					std::vector<Ponto2D> pontosSCNObjeto;//Pontos convertidos de cada wireframe (subobjeto)
					for( Ponto2D ponto : pontosMundoObj ) {
						Matriz matPonto( Tranformadas::ponto2DParaHomogeneo( ponto ) );
						matPonto = matPonto * transformacao;
						Ponto3D pontoSCNHomogeneo = Tranformadas::matrizParaPonto3D( matPonto );
						Ponto2D novoPonto = set2DPoint( pontoSCNHomogeneo.x, pontoSCNHomogeneo.y ); //Um ponto em coordenadas homogeneas
						pontosSCNObjeto.push_back( novoPonto );
					}//Aqui, completou a lista de um dos subobjetos
					pontosSCN.push_back( pontosSCNObjeto );
				}
			}//Completou a lista de subobjetos

			this->pontosSCN = pontosSCN;
		} else {
			std::vector<Reta *> retasSCN;
			for( Reta * reta : retasWireframe ) {
				reta->atualizarCoordenadaExibicao( reta );
				reta->atualizarCoordenadaSCN( transformacao );

			}
		}
	}

}


//-------------------------------------------
void Wireframe::atualizarCoordenadaExibicao( Objeto * objeto ) {
	if( objeto == nullptr ) {
		this->pontosExibicao = std::vector<Wireframe *>();
		desenhar = false;
		return;
	}
	Wireframe * wireframe = dynamic_cast<Wireframe *>( objeto );
	this-> pontosExibicao = wireframe->pontosExibicao;
	desenhar = true;
}
//-------------------------------------------
void Wireframe::atualizarCoordenadaExibicao( std::vector< Wireframe * > subObjetos ) {
	if( subObjetos.empty() ) {
		this->pontosExibicao = std::vector<Wireframe *>();
		desenhar = false;
		return;
	}
	this->pontosExibicao = subObjetos;
	desenhar = true;
}
//-----------------------------------------------
void Wireframe::atualizarRetas( std::vector< Reta * > retas ) {
	if( retas.empty() ) {
		desenhar = false;

	}
	this->retasWireframe = retas;
	desenhar = true;
}
//-----------------------------------------------
std::vector< Reta * > Wireframe::obterRetas() {
	if( this->retasWireframe.empty() ) {
		return std::vector<Reta *>();
	}
	return std::vector<Reta *>( retasWireframe );
}


