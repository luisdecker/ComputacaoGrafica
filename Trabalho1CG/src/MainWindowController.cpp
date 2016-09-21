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

	this->window->moverParaDireita( ZOOM );
	this->obf->atualizaSCNTodosObjetos();
}

void MainWindowController::windowLeft() {

	this->window->moverParaEsquerda( ZOOM );
	this->obf->atualizaSCNTodosObjetos();

}

void MainWindowController::windowUp() {

	this->window->moverParaCima( ZOOM );
	this->obf->atualizaSCNTodosObjetos();

}

void MainWindowController::windowDown() {

	this->window->moverParaBaixo( ZOOM );
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
	this->window->rotacionar( -ANGULO / 57.2957795131 );
	this->obf->atualizaWindow( window );
	this->obf->atualizaSCNTodosObjetos();

}
void MainWindowController::windowRodaHorario() {
	this->window->rotacionar( ANGULO / 57.2957795131 );
	this->obf->atualizaWindow( window );
	this->obf->atualizaSCNTodosObjetos();

}
