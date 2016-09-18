
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
	Ponto2D vetorMovimento = set2DPoint( -numUnidades, 0 );
	Ponto3D vetorMovimentoHomogeneo = Tranformadas::ponto2DParaHomogeneo( vetorMovimento );
	Matriz matVetor = Tranformadas::ponto3DparaMatriz( vetorMovimentoHomogeneo );
	Matriz rotacao = Tranformadas::gerarMatrizRotacao( anguloMundo );
	matVetor = matVetor * rotacao;
	vetorMovimentoHomogeneo = Tranformadas::matrizParaPonto3D( matVetor );
	Matriz operacao = Tranformadas::gerarMatrizTranslacao( set2DPoint( vetorMovimentoHomogeneo.x, vetorMovimentoHomogeneo.y ) );

	Matriz matIE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( ie ) );
	Matriz matID = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( id ) );
	Matriz matSE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( se ) );
	Matriz matSD = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( sd ) );

	matIE = matIE * operacao;
	matID = matID * operacao;
	matSE = matSE * operacao;
	matSD = matSD * operacao;

	Ponto3D novoIE = Tranformadas::matrizParaPonto3D( matIE );
	Ponto3D novoID = Tranformadas::matrizParaPonto3D( matID );
	Ponto3D novoSE = Tranformadas::matrizParaPonto3D( matSE );
	Ponto3D novoSD = Tranformadas::matrizParaPonto3D( matSD );

	this->ie = set2DPoint( novoIE.x, novoIE.y );
	this->id = set2DPoint( novoID.x, novoID.y );
	this->se = set2DPoint( novoSE.x, novoSE.y );
	this->sd = set2DPoint( novoSD.x, novoSD.y );
	this->criarMatrizSCN();
	notify();

}
//-----------------------------------------------
void Window2D::moverParaDireita( int numUnidades ) {
	Ponto2D vetorMovimento = set2DPoint( numUnidades , 0 );
	Ponto3D vetorMovimentoHomogeneo = Tranformadas::ponto2DParaHomogeneo( vetorMovimento );
	Matriz matVetor = Tranformadas::ponto3DparaMatriz( vetorMovimentoHomogeneo );
	Matriz rotacao = Tranformadas::gerarMatrizRotacao( anguloMundo );
	matVetor = matVetor * rotacao;
	vetorMovimentoHomogeneo = Tranformadas::matrizParaPonto3D( matVetor );
	Matriz operacao = Tranformadas::gerarMatrizTranslacao( set2DPoint( vetorMovimentoHomogeneo.x, vetorMovimentoHomogeneo.y ) );

	Matriz matIE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( ie ) );
	Matriz matID = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( id ) );
	Matriz matSE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( se ) );
	Matriz matSD = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( sd ) );

	matIE = matIE * operacao;
	matID = matID * operacao;
	matSE = matSE * operacao;
	matSD = matSD * operacao;

	Ponto3D novoIE = Tranformadas::matrizParaPonto3D( matIE );
	Ponto3D novoID = Tranformadas::matrizParaPonto3D( matID );
	Ponto3D novoSE = Tranformadas::matrizParaPonto3D( matSE );
	Ponto3D novoSD = Tranformadas::matrizParaPonto3D( matSD );

	this->ie = set2DPoint( novoIE.x, novoIE.y );
	this->id = set2DPoint( novoID.x, novoID.y );
	this->se = set2DPoint( novoSE.x, novoSE.y );
	this->sd = set2DPoint( novoSD.x, novoSD.y );
	this->criarMatrizSCN();

	notify();

}
//-----------------------------------------------
void Window2D::moverParaCima( int numUnidades ) {
	Ponto2D vetorMovimento = set2DPoint( 0, numUnidades );
	Ponto3D vetorMovimentoHomogeneo = Tranformadas::ponto2DParaHomogeneo( vetorMovimento );
	Matriz matVetor = Tranformadas::ponto3DparaMatriz( vetorMovimentoHomogeneo );
	Matriz rotacao = Tranformadas::gerarMatrizRotacao( anguloMundo );
	matVetor = matVetor * rotacao;
	vetorMovimentoHomogeneo = Tranformadas::matrizParaPonto3D( matVetor );
	Matriz operacao = Tranformadas::gerarMatrizTranslacao( set2DPoint( vetorMovimentoHomogeneo.x, vetorMovimentoHomogeneo.y ) );

	Matriz matIE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( ie ) );
	Matriz matID = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( id ) );
	Matriz matSE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( se ) );
	Matriz matSD = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( sd ) );

	matIE = matIE * operacao;
	matID = matID * operacao;
	matSE = matSE * operacao;
	matSD = matSD * operacao;

	Ponto3D novoIE = Tranformadas::matrizParaPonto3D( matIE );
	Ponto3D novoID = Tranformadas::matrizParaPonto3D( matID );
	Ponto3D novoSE = Tranformadas::matrizParaPonto3D( matSE );
	Ponto3D novoSD = Tranformadas::matrizParaPonto3D( matSD );

	this->ie = set2DPoint( novoIE.x, novoIE.y );
	this->id = set2DPoint( novoID.x, novoID.y );
	this->se = set2DPoint( novoSE.x, novoSE.y );
	this->sd = set2DPoint( novoSD.x, novoSD.y );
	this->criarMatrizSCN();

	notify();

}
//-----------------------------------------------
void Window2D::moverParaBaixo( int numUnidades ) {

	Ponto2D vetorMovimento = set2DPoint( 0, -numUnidades );
	Ponto3D vetorMovimentoHomogeneo = Tranformadas::ponto2DParaHomogeneo( vetorMovimento );
	Matriz matVetor = Tranformadas::ponto3DparaMatriz( vetorMovimentoHomogeneo );
	Matriz rotacao = Tranformadas::gerarMatrizRotacao( anguloMundo );
	matVetor = matVetor * rotacao;
	vetorMovimentoHomogeneo = Tranformadas::matrizParaPonto3D( matVetor );
	Matriz operacao = Tranformadas::gerarMatrizTranslacao( set2DPoint( vetorMovimentoHomogeneo.x, vetorMovimentoHomogeneo.y ) );

	Matriz matIE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( ie ) );
	Matriz matID = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( id ) );
	Matriz matSE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( se ) );
	Matriz matSD = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( sd ) );

	matIE = matIE * operacao;
	matID = matID * operacao;
	matSE = matSE * operacao;
	matSD = matSD * operacao;

	Ponto3D novoIE = Tranformadas::matrizParaPonto3D( matIE );
	Ponto3D novoID = Tranformadas::matrizParaPonto3D( matID );
	Ponto3D novoSE = Tranformadas::matrizParaPonto3D( matSE );
	Ponto3D novoSD = Tranformadas::matrizParaPonto3D( matSD );

	this->ie = set2DPoint( novoIE.x, novoIE.y );
	this->id = set2DPoint( novoID.x, novoID.y );
	this->se = set2DPoint( novoSE.x, novoSE.y );
	this->sd = set2DPoint( novoSD.x, novoSD.y );
	this->criarMatrizSCN();

	notify();

}
//-----------------------------------------------
void Window2D::zoomIn( int numUnidades ) {
	Ponto2D centro = obterCentro();
	Matriz translacaoOrigem = Tranformadas::gerarMatrizTranslacao( set2DPoint( -centro.x, -centro.y ) );
	Matriz redimensao = Tranformadas::gerarMatrizRedimensionamento( 1 / ( 1 + ( numUnidades / 100. ) ), 1 / ( 1 + ( numUnidades / 100. ) ) );
	Matriz translacaoVolta = Tranformadas::gerarMatrizTranslacao( set2DPoint( centro.x, centro.y ) );
	Matriz operacao = translacaoOrigem * redimensao * translacaoVolta;

	Matriz matIE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( ie ) );
	Matriz matID = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( id ) );
	Matriz matSE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( se ) );
	Matriz matSD = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( sd ) );

	matIE = matIE * operacao;
	matID = matID * operacao;
	matSE = matSE * operacao;
	matSD = matSD * operacao;

	Ponto3D novoIE = Tranformadas::matrizParaPonto3D( matIE );
	Ponto3D novoID = Tranformadas::matrizParaPonto3D( matID );
	Ponto3D novoSE = Tranformadas::matrizParaPonto3D( matSE );
	Ponto3D novoSD = Tranformadas::matrizParaPonto3D( matSD );

	this->ie = set2DPoint( novoIE.x, novoIE.y );
	this->id = set2DPoint( novoID.x, novoID.y );
	this->se = set2DPoint( novoSE.x, novoSE.y );
	this->sd = set2DPoint( novoSD.x, novoSD.y );
	this->criarMatrizSCN();
	notify();

}
//-----------------------------------------------
void Window2D::zoomOut( int numUnidades ) {
	Ponto2D centro = obterCentro();
	Matriz translacaoOrigem = Tranformadas::gerarMatrizTranslacao( set2DPoint( -centro.x, -centro.y ) );
	Matriz redimensao = Tranformadas::gerarMatrizRedimensionamento( ( 1 + ( numUnidades / 100. ) ), ( 1 + ( numUnidades / 100. ) ) );
	Matriz translacaoVolta = Tranformadas::gerarMatrizTranslacao( set2DPoint( centro.x, centro.y ) );
	Matriz operacao = translacaoOrigem * redimensao * translacaoVolta;

	Matriz matIE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( ie ) );
	Matriz matID = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( id ) );
	Matriz matSE = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( se ) );
	Matriz matSD = Tranformadas::ponto3DparaMatriz( Tranformadas::ponto2DParaHomogeneo( sd ) );

	matIE = matIE * operacao;
	matID = matID * operacao;
	matSE = matSE * operacao;
	matSD = matSD * operacao;

	Ponto3D novoIE = Tranformadas::matrizParaPonto3D( matIE );
	Ponto3D novoID = Tranformadas::matrizParaPonto3D( matID );
	Ponto3D novoSE = Tranformadas::matrizParaPonto3D( matSE );
	Ponto3D novoSD = Tranformadas::matrizParaPonto3D( matSD );

	this->ie = set2DPoint( novoIE.x, novoIE.y );
	this->id = set2DPoint( novoID.x, novoID.y );
	this->se = set2DPoint( novoSE.x, novoSE.y );
	this->sd = set2DPoint( novoSD.x, novoSD.y );
	this->criarMatrizSCN();
	notify();

}
//-----------------------------------------------
void Window2D::criarMatrizSCN() {
	Ponto2D centro = this->obterCentro();
	Matriz translacaoOrigem = Tranformadas::gerarMatrizTranslacao( set2DPoint( -centro.x, -centro.y ) );
	Matriz rotacao = Tranformadas::gerarMatrizRotacao( anguloMundo );
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
//-----------------------------------------------
void Window2D::rotacionar( double graus ) {
	this->anguloMundo += graus;
	this->criarMatrizSCN();
	std::cout << "[Window] angulo em " << anguloMundo << "\n";
	notify();
}




