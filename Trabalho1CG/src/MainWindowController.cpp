#include "MainWindowController.hpp"


void MainWindowController::setObjectFile(ObjectFile *obf) {
    this->obf = obf;
}

void MainWindowController::setWindow(Window2D *window) {
    this->window = window;
}

int MainWindowController::obtemTamanhoObjectFile() {
    return this->obf->obterObjetos().size();
}

Objeto * MainWindowController::obtemUltimoObjInserido() {
    return this->obf->obterObjetos().back();
}

void MainWindowController::windowRight() {

    this->window->moverParaDireita(ZOOM);
}

void MainWindowController::windowLeft() {

    this->window->moverParaEsquerda(ZOOM);
}

void MainWindowController::windowUp() {

    this->window->moverParaCima(ZOOM);
}

void MainWindowController::windowDown() {

    this->window->moverParaBaixo(ZOOM);
}

void MainWindowController::windowZoomIn() {

    this->window->zoomIn(ZOOM);
}

void MainWindowController::windowZoomOut() {

    this->window->zoomOut(ZOOM);
}