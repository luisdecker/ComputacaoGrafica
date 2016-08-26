#include "IncludeObjectController.hpp"

void IncludeObjectController::setObjectFile(ObjectFile *obf) {
    this->obf = obf;
}

bool IncludeObjectController::incluirPonto(string nome, double x, double y) {

    Ponto * p = new Ponto( nome, set2DPoint( x, y ) );
    if( !obf->contemObjeto( nome ) ) {
        obf->inserirObjeto( p );
    } else {
        obf->atualizarObjeto( p );
    }

    return true;

}

bool IncludeObjectController::incluirReta(string nome, double x0, double y0, double x1, double y1) {
    Reta * r = new Reta( nome, set2DPoint( x0, y0 ), set2DPoint( x1, y1 ) );
    if( !obf->contemObjeto( nome ) ) {
        obf->inserirObjeto( r );
    } else {
        obf->atualizarObjeto( r );
    }

    return true;
}

bool IncludeObjectController::incluirPontoWireframe(string nome, double x, double y) {
    if( obf->contemObjeto( nome ) ) {
        Wireframe * wire = dynamic_cast<Wireframe * > (obf->obterObjetoNome( nome ));
        wire->adicionarPonto(set2DPoint(x,y));
        obf->atualizarObjeto( wire );

    } else {
        Wireframe * wire = new Wireframe(nome);
        wire->adicionarPonto(set2DPoint(x,y));
        obf->inserirObjeto( wire );
    }

    return true;
}