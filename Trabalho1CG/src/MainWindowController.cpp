#include "MainWindowController.hpp"


void MainWindowController::setObjectFile( ObjectFile * obf ) {
	this->obf = obf;
}

void MainWindowController::setWindow( Window2D * window ) {
	this->window = window;

}

int MainWindowController::obtemTamanhoObjectFile() {
	return this->obf->obterObjetos().size();
}

Objeto * MainWindowController::obtemUltimoObjInserido() {
	return this->obf->obterObjetos().back();
}

void MainWindowController::windowRight() {

	this->window->moverParaDireita( PASSO);
	this->obf->atualizaSCNTodosObjetos();
}

void MainWindowController::windowLeft() {

	this->window->moverParaEsquerda( PASSO );
	this->obf->atualizaSCNTodosObjetos();

}

void MainWindowController::windowUp() {

	this->window->moverParaCima( PASSO );
	this->obf->atualizaSCNTodosObjetos();

}

void MainWindowController::windowDown() {

	this->window->moverParaBaixo( PASSO );
	this->obf->atualizaSCNTodosObjetos();

}

void MainWindowController::windowZoomIn() {

	this->window->zoomIn( ZOOM );
	this->obf->atualizaSCNTodosObjetos();

}

void MainWindowController::windowZoomOut() {

	this->window->zoomOut( ZOOM );
	this->obf->atualizaSCNTodosObjetos();

}

void MainWindowController::windowRodaAntiHorario() {
	this->window->rotacionar( ANGULO );
	//this->obf->atualizaWindow( window );
	this->obf->atualizaSCNTodosObjetos();

}
void MainWindowController::windowRodaHorario() {
	this->window->rotacionar( -ANGULO );
	//this->obf->atualizaWindow( window );
	this->obf->atualizaSCNTodosObjetos();

}
