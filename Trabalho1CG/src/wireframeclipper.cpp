#include "wireframeclipper.h"

Objeto * WireframeClipper::clip( Objeto * objeto ) {
	if( objeto->tipoObjeto != Objeto::wireframe ) {
		std::cout << "[WireframeClipper][" << __LINE__ << "] Tentou clipar algo diferente de um wireframe!" << std::endl;
		return nullptr;
	}
	objeto = Tranformadas::rotacionar( objeto, -( janela->obterRotacao() ), janela->obterCentro() );
	Wireframe * wireframe = to_wireframe( objeto );
	RetasWireframe retasOriginais = converterParaRetas( wireframe );
	RetasWireframe retasClipadas = cliparRetas( retasOriginais );
	if( retasClipadas.empty() ) {return nullptr;}
	ListaPontos novosPontos = LigarRetas( retasClipadas );
	Wireframe * novoWireframe = new Wireframe( objeto->nome, novosPontos );
	novoWireframe = to_wireframe( Tranformadas::rotacionar( novoWireframe, janela->obterRotacao(), janela->obterCentro() ) );
	return novoWireframe;

}
//-----------------------------------------------
WireframeClipper::RetasWireframe WireframeClipper::converterParaRetas( Wireframe * wireframe ) {
	RetasWireframe retas;
	ListaPontos pontos = wireframe->obterPontos();
	for( int indice = 0; indice < pontos.size(); indice++ ) {
		Ponto2D ponto1 = pontos.at( indice ) , ponto2;
		if( indice != pontos.size() - 1 ) {
			ponto2 = pontos.at( indice + 1 );
		} else {
			ponto2 = pontos.at( 0 );
		}
		retas.push_back( new Reta( "Uma reta", ponto1, ponto2 ) );
	}
	return retas;
}
//-----------------------------------------------
WireframeClipper::RetasWireframe WireframeClipper::cliparRetas( WireframeClipper::RetasWireframe retas ) {
	RetasWireframe retasClipadas;
	Window2D janelazerada( janela->inferiorEsquerdo(), janela->superiorDireito() );
	for( Reta * reta : retas ) {

		reta = to_reta( CohenSutherland( &janelazerada ).clip( reta ) );
		if( reta != nullptr ) retasClipadas.push_back( reta );
	}
	return retasClipadas;
}
//-----------------------------------------------
WireframeClipper::ListaPontos WireframeClipper::LigarRetas( WireframeClipper::RetasWireframe retasClipadas ) {
	ListaPontos lista;
	if( retasClipadas.size() == 0 )return lista;
	Ponto2D ultimoPonto = retasClipadas.front()->obterCoordenadaInicial();
	lista.push_back( ultimoPonto );
	for( Reta * reta : retasClipadas ) {
		if( !( ultimoPonto == reta->obterCoordenadaInicial() ) ) {
			lista.push_back( reta->obterCoordenadaInicial() );
		}
		lista.push_back( reta->obterCoordenadaFinal() );
	}
	return lista;
}