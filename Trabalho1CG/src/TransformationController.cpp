#include "TransformationController.hpp"

void TransformationController::setObjectFile(ObjectFile *obf) {
    this->obf = obf;
}

void TransformationController::aplicarTranslacao(string nomeObj, double x, double y) {
    Objeto * obj = this->obf->obterObjetoNome(nomeObj);

    // faz o que tem que fazer...

    this->obf->atualizarObjeto(obj);
}

void TransformationController::aplicarEscalonamento(string nomeObj, double x, double y) {

    Objeto * obj = this->obf->obterObjetoNome(nomeObj);

    // faz o que tem que fazer...

    this->obf->atualizarObjeto(obj);

}

void TransformationController::aplicarRotacaoCentroMundo(string nomeObj, double angulo) {

    Objeto * obj = this->obf->obterObjetoNome(nomeObj);

    // faz o que tem que fazer...

    this->obf->atualizarObjeto(obj);

}

void TransformationController::aplicarRotacaoCentroObjeto(string nomeObj, double angulo) {

    Objeto * obj = this->obf->obterObjetoNome(nomeObj);

    // faz o que tem que fazer...

    this->obf->atualizarObjeto(obj);

}

void TransformationController::aplicarRotacaoPontoArbitrario(string nomeObj, double angulo, double x, double y) {

    Objeto * obj = this->obf->obterObjetoNome(nomeObj);

    // faz o que tem que fazer...

    this->obf->atualizarObjeto(obj);

}