#include "curveclipper.h"
#include "objeto.h"
Objeto * CurveClipper::clip( Objeto * curvaOriginal ) {
	switch( curvaOriginal->tipoObjeto ) {
		case Objeto::bezier: {
			CurvaBezier * curva = dynamic_cast<CurvaBezier *>( curvaOriginal );
			if( curva->obterPontosCalculados().empty() ) {
				return nullptr;
			}
			listaRetas retasInterpoladas = paraRetas( curva );
			listaRetas retasClipadas = cliparRetas( retasInterpoladas );
			listaPontos pontosClipados = paraPontos( retasClipadas );
			if( pontosClipados.empty() ) {
				return nullptr;
			}
			return new CurvaBezier( pontosClipados );

		}
		case Objeto::bspline: {
			CurvaBSpline * curva = dynamic_cast<CurvaBSpline *>( curvaOriginal );
			if( curva->obterPontosCalculados().empty() ) {
				return nullptr;
			}
			listaRetas retasInterpoladas = paraRetas( curva );
			listaRetas retasClipadas = cliparRetas( retasInterpoladas );
			listaPontos pontosClipados = paraPontos( retasClipadas );
			if( pontosClipados.empty() ) {
				return nullptr;
			}
			return new CurvaBSpline( pontosClipados );
		}
		default: {
			std::cout << "[CurveClipper][" << __LINE__ << "] Tentou clipar algo nao curvelineo!" << std::endl;
			return nullptr;
			break;
		}
	}

}
//-----------------------------------------------
CurveClipper::listaRetas CurveClipper::paraRetas( CurvaBezier * curva ) {
	listaRetas retasConvertidas;
	for( int i = 0; i < curva->obterPontosCalculados().size() - 1; i++ ) {
		Ponto2D inicial = curva->obterPontosCalculados()[i];
		Ponto2D final = curva->obterPontosCalculados()[i + 1];
		retasConvertidas.push_back( new Reta( "", inicial, final ) );
	}
	return retasConvertidas;
}
//-----------------------------------------------
CurveClipper::listaRetas CurveClipper::paraRetas( CurvaBSpline * curva ) {
	listaRetas retasConvertidas;
	for( int i = 0; i < curva->obterPontosCalculados().size() - 1; i++ ) {
		Ponto2D inicial = curva->obterPontosCalculados()[i];
		Ponto2D final = curva->obterPontosCalculados()[i + 1];
		retasConvertidas.push_back( new Reta( "", inicial, final ) );
	}
	return retasConvertidas;
}
//-----------------------------------------------
CurveClipper::listaRetas CurveClipper::cliparRetas( CurveClipper::listaRetas retas ) {
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
CurveClipper::listaPontos CurveClipper::paraPontos( CurveClipper::listaRetas retas ) {
	listaPontos pontos;
	if( !retas.empty() ) {
		pontos.push_back( retas.front()->obterCoordenadaInicial() );
		bool incluirProximoInicial = false;
		for( Reta * reta : retas	) {
			if( incluirProximoInicial ) {
				pontos.push_back( reta->obterCoordenadaInicial() );
				incluirProximoInicial = false;
			}
			pontos.push_back( reta->obterCoordenadaFinal() );
			if( pontoNaBorda( reta->obterCoordenadaFinal() , janela ) ) {
				incluirProximoInicial = true;
			}

		}
	}
	return pontos;
}
//-----------------------------------------------
bool CurveClipper::pontoNaBorda( Ponto2D ponto, Window2D * janela ) {
	Ponto * pontoRodado = dynamic_cast<Ponto *>( Tranformadas::rotacionar( new Ponto( "", ponto ), -janela->obterRotacao(), janela->obterCentro() ) );
	Ponto2D novaCoordenada = pontoRodado->obterCoordenada();
	if( novaCoordenada.x == janela->obterXMinimo() ||
		novaCoordenada.x == janela->obterXMaximo() ||
		novaCoordenada.y == janela->obterXMinimo() ||
		novaCoordenada.y == janela->obterYMaximo() ) {
		return true;
	}
	return false;
}

