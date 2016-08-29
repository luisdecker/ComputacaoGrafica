#include "matriz.hpp"
//-----------------------------------------------
Matriz::Matriz( int linhas, int colunas ) {
	assert( linhas >= 1 );
	assert( colunas >= 1 );
	double ** newMat = new double * [linhas];
	int linhaOrg = linhas;
	for( linhas; linhas > 0; linhas-- ) {
		newMat[linhas - 1] = new double[colunas];
	}
	this->data = newMat;
	this->linhas = linhaOrg;
	this->colunas = colunas;
	std::cout << "[Matriz]Criou uma matriz tamanho " << this->linhas << "x" << colunas << std::endl;

}

//-----------------------------------------------
double & Matriz::at( int linha, int coluna ) {
	return data[linha - 1][coluna - 1];
}
//-----------------------------------------------
Matriz Matriz::multiplicar( Matriz outra )  {
	std::cout << "[Matriz]Vai multiplicar matrizes " << this->linhas << "x" << this->colunas << " e " << outra.linhas << "x" << outra.colunas << std::endl;
	assert( this->colunas == outra.linhas );
	Matriz resposta( this->linhas, outra.colunas );
	for( int linha1 = 1; linha1 <= this->linhas; linha1++ ) {
		for( int coluna2 = 0; coluna2 <= outra.colunas; coluna2++ ) {
			double soma = 0;
			for( int coluna1 = 1;  coluna1 <= this->colunas; coluna1++ ) {
				soma += this->at( linha1, coluna1 ) * outra.at( coluna1, coluna2 );
			}
			resposta.at( linha1, coluna2 ) = soma;
		}
	}
	std::cout << "[Matriz]Multiplicou!" << std::endl;
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

