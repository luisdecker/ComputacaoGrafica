#ifndef TRANSFORMATIONCONTROLLER_H
#define TRANSFORMATIONCONTROLLER_H

#include <string>
#include "objectfile.h"
#include "transformadas.hpp"
#include <iostream>

using namespace std;

class TransformationController {

    ObjectFile * obf;

public:
    void setObjectFile( ObjectFile * obf );
    void aplicarTranslacao( string nomeObj, double x, double y );
    void aplicarEscalonamento( string nomeObj, double x, double y );
    void aplicarRotacaoCentroMundo( string nomeObj, double angulo );
    void aplicarRotacaoCentroObjeto( string nomeObj, double angulo );
    void aplicarRotacaoPontoArbitrario( string nomeObj, double angulo, double x, double y );

};

#endif