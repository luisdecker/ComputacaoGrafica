
#include "window.h"
//-----------------------------------------------
Window2D::Window2D( Ponto2D inferiorEsquerdo, Ponto2D superiorDireito ) {
    this->ie = inferiorEsquerdo;
    this->sd = superiorDireito;
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
void Window2D::defineXMaximo(int xMax) {
    sd.x = xMax;
}
//-----------------------------------------------
void Window2D::defineXMinimo(int xMin) {
    ie.x = xMin;
}
//-----------------------------------------------
void Window2D::defineYMaximo(int yMax) {
    sd.y = yMax;
}
//-----------------------------------------------
void Window2D::defineYMinimo(int yMin) {
    ie.y = yMin;
}

void Window2D::moverParaEsquerda(int numUnidades) {

    ie.x -= numUnidades;
    sd.x -= numUnidades;

    notify();

}
void Window2D::moverParaDireita(int numUnidades) {

    ie.x += numUnidades;
    sd.x += numUnidades;

    notify();

}
void Window2D::moverParaCima(int numUnidades) {

    ie.y += numUnidades;
    sd.y += numUnidades;

    notify();

}
void Window2D::moverParaBaixo(int numUnidades) {

    ie.y -= numUnidades;
    sd.y -= numUnidades;

    notify();

}

void Window2D::zoomIn(int numUnidades) {

    ie.x += numUnidades, ie.y += numUnidades;
    sd.x -= numUnidades, sd.y -= numUnidades;

    notify();

}
void Window2D::zoomOut(int numUnidades) {

    ie.x -= numUnidades, ie.y -= numUnidades;
    sd.x += numUnidades, sd.y += numUnidades;

    notify();

}