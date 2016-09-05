
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
	Ponto2D centro = obterCentro();
	Matriz translacaoOrigem = Tranformadas::gerarMatrizTranslacao( set2DPoint( -centro.x, -centro.y ) );
	Matriz rotacao = Tranformadas::gerarMatrizRotacao( -anguloMundo );
	Matriz operacao = translacaoOrigem * rotacao;
	double largura = sqrt( pow( ie.x - id.x, 2 ) + pow( ( ie.y - id.y ), 2 ) );
	double altura = sqrt( pow( ie.x - se.x, 2 ) + pow( ( ie.y - se.y ), 2 ) );
	double proporcaoX = 1 / largura;
	double proporcaoY = 1 / altura;
	Tranformadas::gerarMatrizRedimensionamento( proporcaoX, proporcaoY );
	this->MatrizSCN = operacao;

}
//-----------------------------------------------
Ponto2D Window2D::obterCentro() {
	double maiorX, maiorY, menorX, menorY;

	maiorX = ie.x;
	maiorX = ( sd.x > maiorX ? sd.x : maiorX );
	maiorX = ( se.x > maiorX ? se.x : maiorX );
	maiorX = ( id.x > maiorX ? id.x : maiorX );

	maiorY = ie.y;
	maiorY = ( sd.y > maiorY ? sd.y : maiorY );
	maiorY = ( se.y > maiorY ? se.y : maiorY );
	maiorY = ( id.y > maiorY ? id.y : maiorY );

	menorX = ie.x;
	menorX = ( sd.x < menorX ? sd.x : menorX );
	menorX = ( se.x < menorX ? se.x : menorX );
	menorX = ( id.x < menorX ? id.x : menorX );

	menorY = ie.y;
	menorY = ( sd.y < menorY ? sd.y : menorY );
	menorY = ( se.y < menorY ? se.y : menorY );
	menorY = ( id.y < menorY ? id.y : menorY );

	return set2DPoint( ( maiorX + menorX ) / 2, ( maiorY + menorY ) / 2 );
}
//-----------------------------------------------
Matriz Window2D::obterTransformacaoSCN() {
	return MatrizSCN;
}


