#include "clipper.h"

Clipper::Clipper( Window2D * janela ) {
    this->janela = janela;//Vai precisar por causa das coordenadas SCN.
}
//-----------------------------------------------
Clipper::~Clipper() {

}
//-----------------------------------------------
Objeto * Clipper::clip( Objeto * objeto ) {
    switch( objeto->tipoObjeto ) {
    case Objeto::ponto: {
        Ponto * ponto = dynamic_cast<Ponto *>( objeto );
        return clipPonto( ponto );
        break;
    }
    case Objeto::reta: {
        Reta * reta  = dynamic_cast<Reta *>( objeto );
        return clipReta( reta );
        break;
    }
    case Objeto::wireframe: {
        Wireframe * wireframe = dynamic_cast<Wireframe *>( objeto );
        return clipPoligono( wireframe );
        break;
    }

    }
}
//-----------------------------------------------
Wireframe * Clipper::clipPoligono( Wireframe * wireframe ) {

}
//-----------------------------------------------
Ponto * Clipper::clipPonto( Ponto * ponto ) {

}
//-----------------------------------------------
Reta * Clipper::clipReta( Reta * reta ) {

}
//-----------------------------------------------
Objeto * Clipper::operator()( Objeto * obj ) {
    return clip( obj );
}
//-----------------------------------------------