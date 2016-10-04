#include "bezierclipper.h"
CurvaBezier * BezierClipper::clip( CurvaBezier * curvaOriginal ) {
	if( curvaOriginal->obterPontosCalculados().empty() ) {
		return nullptr;
	}
	listaRetas retasInterpoladas = paraRetas( curvaOriginal );
	listaRetas retasClipadas = cliparRetas( retasInterpoladas );
	listaPontos pontosClipados = paraPontos( retasClipadas );
	if( pontosClipados.empty() ) {
		return nullptr;
	}
	return new CurvaBezier( pontosClipados );
}
//-----------------------------------------------
BezierClipper::listaRetas BezierClipper::paraRetas( CurvaBezier * curva ) {
	listaRetas retasConvertidas;
	for( int i = 0; i < curva->obterPontosCalculados().size() - 1; i++ ) {
		Ponto2D inicial = curva->obterPontosCalculados()[i];
		Ponto2D final = curva->obterPontosCalculados()[i + 1];
		retasConvertidas.push_back( new Reta( "", inicial, final ) );
	}
	return retasConvertidas;
}
//-----------------------------------------------
BezierClipper::listaRetas BezierClipper::cliparRetas( BezierClipper::listaRetas retas ) {
	listaRetas retasClipadas;
	if( !retas.empty() ) {
		for( Reta * reta : retas ) {
			Reta * retaClipada = to_reta( CohenSutherland( janela ).clip( reta ) );
			if( retaClipada != nullptr ) {
				retasClipadas.push_back( retaClipada );
			}
		}
	}
	return retasClipadas;
}
//-----------------------------------------------
BezierClipper::listaPontos BezierClipper::paraPontos( BezierClipper::listaRetas retas ) {
	listaPontos pontos;
	if( !retas.empty() ) {
		pontos.push_back( retas.front()->obterCoordenadaInicial() );
		for( Reta * reta : retas	) {
			pontos.push_back( reta->obterCoordenadaFinal() );
		}
	}
	return pontos;
}
