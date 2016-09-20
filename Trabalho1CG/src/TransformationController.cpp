#include "TransformationController.hpp"

void TransformationController::setObjectFile( ObjectFile * obf ) {
	this->obf = obf;
}

void TransformationController::aplicarTranslacao( string nomeObj, double x, double y ) {
	Objeto * obj = this->obf->obterObjetoNome( nomeObj );

	Objeto * novoObjeto = Tranformadas::transladar( obj, set2DPoint( x, y ) );
	this->obf->atualizarObjeto( novoObjeto );
}

void TransformationController::aplicarEscalonamento( string nomeObj, double x, double y ) {

	Objeto * obj = this->obf->obterObjetoNome( nomeObj );

	obj = Tranformadas::redimensionar( obj, set2DPoint( x, y ) );

	this->obf->atualizarObjeto( obj );

}

void TransformationController::aplicarRotacaoCentroMundo( string nomeObj, double angulo ) {

	Objeto * obj = this->obf->obterObjetoNome( nomeObj );

	obj = Tranformadas::rotacionar( obj, angulo, set2DPoint( 0, 0 ) );

	this->obf->atualizarObjeto( obj );

}

void TransformationController::aplicarRotacaoCentroObjeto( string nomeObj, double angulo ) {

	Objeto * obj = this->obf->obterObjetoNome( nomeObj );

	Ponto2D centro ;
	switch( obj->tipoObjeto ) {
		case Objeto::ponto: {

			Ponto * ponto = dynamic_cast<Ponto *>( obj );
			std::cout << "[TransformationController] Ponto rodando em volta de si mesmo\n";
			centro = ponto->obterCoordenada();
			break;
		}
		case Objeto::reta: {
			Reta * reta = dynamic_cast<Reta *>( obj );
			std::cout << "[TransformationController] Reta rodando em volta de si mesmo\n";
			double mediaX = ( reta->obterCoordenadaInicial().x + reta->obterCoordenadaFinal().x ) / 2;
			double mediaY = ( reta->obterCoordenadaInicial().y + reta->obterCoordenadaFinal().y ) / 2;
			centro = set2DPoint( mediaX, mediaY );
			break;
		}
		case Objeto::wireframe: {
			Wireframe * wireframe = dynamic_cast<Wireframe *>( obj );
			std::cout << "[TransformationController] Wireframe rodando em volta de si mesmo\n";
			double somaX;
			double somaY;
			for( Ponto2D ponto : wireframe->obterPontos() ) {
				somaX += ponto.x;
				somaY += ponto.y;
			}
			double mediaX = somaX / wireframe->obterPontos() .size();
			double mediaY = somaY / wireframe->obterPontos() .size();
			centro = set2DPoint( mediaX, mediaY );
			break;
		}
	}

	obj = Tranformadas::rotacionar( obj, angulo, centro );

	this->obf->atualizarObjeto( obj );

}

void TransformationController::aplicarRotacaoPontoArbitrario( string nomeObj, double angulo, double x, double y ) {

	Objeto * obj = this->obf->obterObjetoNome( nomeObj );

	obj = Tranformadas::rotacionar( obj, angulo, set2DPoint( x, y ) );

	this->obf->atualizarObjeto( obj );

}