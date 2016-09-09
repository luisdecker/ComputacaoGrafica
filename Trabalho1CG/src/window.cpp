
#include "window.h"
//-----------------------------------------------
Window2D::Window2D( Ponto2D inferiorEsquerdo, Ponto2D superiorDireito ) {
	this->ie = inferiorEsquerdo;
	this->sd = superiorDireito;
	this->id = set2DPoint( superiorDireito.x, inferiorEsquerdo.y );
	this->se = set2DPoint( ie.x, sd.y );
	this->anguloMundo  = 0;
}
//-----------------------------------------------
int Window2D::obterXMaximo() {
	return sd.x;
}
//-----------------------------------------------
int Window2D::obterXMinimo() {
	return ie.x;
}
//-----------------------------------------------
int Window2D::obterYMaximo() {
	return sd.y;
}
//-----------------------------------------------
int Window2D::obterYMinimo() {
	return ie.y;
}
//-----------------------------------------------
void Window2D::defineXMaximo( int xMax ) {
	sd.x = xMax;
}
//-----------------------------------------------
void Window2D::defineXMinimo( int xMin ) {
	ie.x = xMin;
}
//-----------------------------------------------
void Window2D::defineYMaximo( int yMax ) {
	sd.y = yMax;
}
//-----------------------------------------------
void Window2D::defineYMinimo( int yMin ) {
	ie.y = yMin;
}
//-----------------------------------------------

void Window2D::moverParaEsquerda( int numUnidades ) {

	ie.x -= numUnidades;
	sd.x -= numUnidades;

	notify();

}
//-----------------------------------------------
void Window2D::moverParaDireita( int numUnidades ) {

	ie.x += numUnidades;
	sd.x += numUnidades;

	notify();

}
//-----------------------------------------------
void Window2D::moverParaCima( int numUnidades ) {

	ie.y += numUnidades;
	sd.y += numUnidades;

	notify();

}
//-----------------------------------------------
void Window2D::moverParaBaixo( int numUnidades ) {

	ie.y -= numUnidades;
	sd.y -= numUnidades;

	notify();

}
//-----------------------------------------------
void Window2D::zoomIn( int numUnidades ) {

	ie.x += numUnidades, ie.y += numUnidades;
	sd.x -= numUnidades, sd.y -= numUnidades;

	notify();

}
//-----------------------------------------------
void Window2D::zoomOut( int numUnidades ) {

	ie.x -= numUnidades, ie.y -= numUnidades;
	sd.x += numUnidades, sd.y += numUnidades;

	notify();

}
//-----------------------------------------------
void Window2D::criarMatrizSCN() {
	Ponto2D centro = this->obterCentro();
	Matriz translacaoOrigem = Tranformadas::gerarMatrizTranslacao( set2DPoint( -centro.x, -centro.y ) );
	Matriz rotacao = Tranformadas::gerarMatrizRotacao( -anguloMundo );
	Matriz operacao = translacaoOrigem * rotacao;
	double largura = sqrt( pow( ie.x - id.x, 2 ) + pow( ( ie.y - id.y ), 2 ) );
	double altura = sqrt( pow( ie.x - se.x, 2 ) + pow( ( ie.y - se.y ), 2 ) );
	double proporcaoX = 1 / largura;
	double proporcaoY = 1 / altura;
	Matriz redimensao = Tranformadas::gerarMatrizRedimensionamento( proporcaoX, proporcaoY );
	operacao = operacao * redimensao;
	this->MatrizSCN = operacao;

}
//-----------------------------------------------
Ponto2D Window2D::obterCentro() {
	double maiorX;
	double maiorY;
	double menorX;
	double menorY;

	maiorX = this->ie.x;
	maiorX = ( this->sd.x > maiorX ? this->sd.x : maiorX );
	maiorX = ( this->se.x > maiorX ? this->se.x : maiorX );
	maiorX = ( this->id.x > maiorX ? this->id.x : maiorX );

	maiorY = this->ie.y;
	maiorY = ( this->sd.y > maiorY ? this->sd.y : maiorY );
	maiorY = ( this->se.y > maiorY ? this->se.y : maiorY );
	maiorY = ( this->id.y > maiorY ? this->id.y : maiorY );

	menorX = this->ie.x;
	menorX = ( this->sd.x < menorX ? this->sd.x : menorX );
	menorX = ( this->se.x < menorX ? this->se.x : menorX );
	menorX = ( this->id.x < menorX ? this->id.x : menorX );

	menorY = this->ie.y;
	menorY = ( this->sd.y < menorY ? this->sd.y : menorY );
	menorY = ( this->se.y < menorY ? this->se.y : menorY );
	menorY = ( this->id.y < menorY ? this->id.y : menorY );

	return set2DPoint( ( maiorX + menorX ) / 2, ( maiorY + menorY ) / 2 );
}
//-----------------------------------------------
Matriz Window2D::obterTransformacaoSCN() {
	criarMatrizSCN();
	return MatrizSCN;
}


