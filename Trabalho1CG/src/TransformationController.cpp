#include "TransformationController.hpp"

void TransformationController::setObjectFile( ObjectFile * obf ) {
	this->obf = obf;
}

void TransformationController::aplicarTranslacao( string nomeObj, double x, double y ) {
	Objeto * obj = this->obf->obterObjetoNome( nomeObj );

	obj = Tranformadas::transladar( obj, set2DPoint( x, y ) );

	this->obf->atualizarObjeto( obj );
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

	Ponto2D centro = obj->obterCentro();

	obj = Tranformadas::rotacionar( obj, angulo, centro );

	this->obf->atualizarObjeto( obj );

}

void TransformationController::aplicarRotacaoPontoArbitrario( string nomeObj, double angulo, double x, double y ) {

	Objeto * obj = this->obf->obterObjetoNome( nomeObj );

	obj = Tranformadas::rotacionar( obj, angulo, set2DPoint( x, y ) );

	this->obf->atualizarObjeto( obj );

}