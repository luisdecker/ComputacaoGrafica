#include "clipponto.h"

ClipPonto::ClipPonto( Window2D * window ): janela( window ) {

}
//-----------------------------------------------
Objeto * ClipPonto::clip( Objeto * objeto ) {
	if( objeto->tipoObjeto != Objeto::ponto ) {
		std::cout << "[WARNING][ClipPonto] tentando clipar algo diferente de um ponto!\n";
	}
	Ponto * ponto = dynamic_cast<Ponto *>( Tranformadas::rotacionar( objeto, janela->obterRotacao(), janela->obterCentro() ) );

	Ponto2D coord = ponto->obterCoordenada();

	if( coord.x >= janela->obterXMinimo() &&
		coord.x <= janela->obterXMaximo() &&
		coord.y >= janela->obterYMinimo() &&
		coord.y <= janela->obterYMaximo() ) {
		return objeto;
	}
	return nullptr;


}
