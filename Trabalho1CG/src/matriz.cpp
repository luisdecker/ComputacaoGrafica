#include "matriz.hpp"
//-----------------------------------------------
//Constroi uma matriz linhas x colunas
Matriz::Matriz( int linhas, int colunas ) {
	assert( linhas >= 1 );
	assert( colunas >= 1 );
	double * newMat = new double [linhas * colunas];

	this->data = newMat;
	this->linhas = linhas;
	this->colunas = colunas;
	std::cout;// << "[Matriz]Criou uma matriz tamanho " << this->linhas << "x" << colunas << std::endl;
}
//-----------------------------------------------
//Constroi uma matriz a partir de um ponto 3D;
Matriz::Matriz( Ponto3D ponto ) {
	this->linhas = 1;
	this->colunas = 3;

	double * newMat = new double [3];
	newMat[0] = ponto.x;
	newMat[1] = ponto.y;
	newMat[2] = ponto.z;
	this-> data = newMat;
}

//-----------------------------------------------
double & Matriz::at( int linha, int coluna ) {
	assert( linha > 0 );
	assert( linha <= this->linhas );
	assert( coluna > 0 );
	assert( coluna <= this->colunas );
	linha -= 1;
	coluna -= 1;
//	std::cout;// << "[Matriz] acessando dado " << linha * this->colunas + coluna << std::endl;
	return data[linha * this->colunas + coluna];
}
//-----------------------------------------------
Matriz Matriz::multiplicar( Matriz outra )  {
	std::cout;// << "[Matriz]Vai multiplicar matrizes " << this->linhas << "x" << this->colunas << " e " << outra.linhas << "x" << outra.colunas << std::endl;
	assert( this->colunas == outra.linhas );
	Matriz resposta( this->linhas, outra.colunas );

	for( int linha1 = 1; linha1 <= this->linhas; linha1++ ) {
		for( int coluna2 = 1; coluna2 <= outra.colunas; coluna2++ ) {
			double soma = 0;

			for( int coluna1 = 1;  coluna1 <= this->colunas; coluna1++ ) {
				soma += this->at( linha1, coluna1 ) * outra.at( coluna1, coluna2 );

			}
			resposta.at( linha1, coluna2 ) = soma;
		}
	}

	std::cout;// << "[Matriz]Multiplicou!" << std::endl;
	return resposta;
}
//-----------------------------------------------
Matriz Matriz::somar( Matriz outra ) {

	assert( this->linhas == outra.linhas );
	assert( this->colunas == outra.colunas );

	Matriz retorno( this->linhas, this->colunas );

	for( int linha = 1; linha <= this->linhas; linha++ ) {
		for( int coluna = 1; coluna <= this->colunas; coluna++ ) {
			retorno.at( linha, coluna ) = this->at( linha, coluna ) + outra.at( linha, coluna );
		}
	}

	return retorno;

}
//-----------------------------------------------
Matriz Matriz::subtrair( Matriz outra )  {

	assert( this->linhas == outra.linhas );
	assert( this->colunas == outra.colunas );

	Matriz retorno( this->linhas, this->colunas );

	for( int linha = 1; linha <= this->linhas; linha++ ) {
		for( int coluna = 1; coluna <= this->colunas; coluna++ ) {
			retorno.at( linha, coluna ) = this->at( linha, coluna ) - outra.at( linha, coluna );
		}
	}

	return retorno;
}
//-----------------------------------------------
bool Matriz::igual( Matriz outra ) {
	if( this->colunas != outra.colunas || this->linhas != outra.linhas ) {
		return false;
	}

	bool retorno = true;

	for( int linha = 1; linha <= this->linhas; linha++ ) {
		for( int coluna = 1; coluna <= this->colunas; coluna++ ) {
			if( this->at( linha, coluna ) != outra.at( linha, coluna ) ) {
				retorno = false;
			}
		}
	}

	return retorno;
}
//-----------------------------------------------
Matriz Matriz::transpor() {
	Matriz transposta( colunas, linhas );

	for( int linha = 1; linha <= this->linhas; linha++ ) {
		for( int coluna = 1; coluna <= this->colunas; coluna++ ) {
			transposta.at( coluna, linha ) = this->at( linha, coluna );
		}
	}
}
void Matriz::print() {
	for( int linha = 1 ; linha <= this->linhas; linha++ ) {
		for( int coluna = 1 ; coluna <= this->colunas; coluna++ ) {
			std::cout << this->at( linha, coluna ) << " ";
		}

		std::cout << "\n";

	}
}



