#include "transformadas.hpp"

Ponto2D Tranformadas::matrizParaPonto2D( Matriz matriz ) {
	assert( matriz.numLinhas() == 1 );
	assert( matriz.numColunas() == 2 );
	return set2DPoint( matriz.at( 1, 1 ), matriz.at( 1, 2 ) );

}
//-----------------------------------------------
Ponto3D Tranformadas::matrizParaPonto3D( Matriz matriz ) {
	assert( matriz.numLinhas() == 1 );
	assert( matriz.numColunas() == 3 );
	return set3DPoint(
			   matriz.at( 1, 1 ),
			   matriz.at( 1, 2 ),
			   matriz.at( 1, 3 )
		   );

}
//-----------------------------------------------
Ponto3D Tranformadas::ponto2DParaHomogeneo( Ponto2D ponto ) {
	return set3DPoint( ponto.x, ponto.y, 1 );

}
//-----------------------------------------------
Matriz Tranformadas::ponto2DparaMatriz( Ponto2D ponto ) {
	Matriz novaMat( 1, 2 );
	novaMat.at( 1, 1 ) = ponto.x;
	novaMat.at( 1, 2 ) = ponto.y;
	return novaMat;

}
//-----------------------------------------------
Matriz Tranformadas::ponto3DparaMatriz( Ponto3D ponto ) {
	Matriz novaMat( 1, 3 );
	novaMat.at( 1, 1 ) = ponto.x;
	novaMat.at( 1, 2 ) = ponto.y;
	novaMat.at( 1, 3 ) = ponto.z;
	std::cout << "[Transformadas]Converteu ponto 3D - " << novaMat.numLinhas() << "x" << novaMat.numColunas() << std::endl;
	return novaMat;

}
//-----------------------------------------------
Objeto * Tranformadas::redimensionar( Objeto * obj, Ponto2D escala ) {
	switch( obj->tipoObjeto ) {
		case Objeto::ponto: {
			Ponto * ponto = dynamic_cast<Ponto *>( obj );
			return new Ponto( obj->nome, set2DPoint( ponto->obterCoordenada().x * escala.x, ponto->obterCoordenada().y * escala.y ) );
			break;
		}
		case Objeto::reta: {
			Reta * reta = dynamic_cast<Reta *>( obj );
			//Obtencao do centro da reta
			double somaX = reta->obterCoordenadaInicial().x + reta->obterCoordenadaFinal().x;
			double somaY = reta->obterCoordenadaInicial().y + reta->obterCoordenadaFinal().y;
			Ponto2D centro = set2DPoint( somaX / 2, somaY / 2 );
			//Criação da matriz de translacao para a origem
			Matriz translacaoOrigem = gerarMatrizTranslacao( set2DPoint( -centro.x, -centro.y ) );
			//Criação da matriz de gerarMatrizRedimensionamento
			Matriz redimensao = gerarMatrizRedimensionamento( escala.x, escala.y );
			//Criação da matriz de translacao para ponto original
			Matriz translacaoRetorno = gerarMatrizTranslacao( set2DPoint( centro.x, centro.y ) );
			//Multiplicação das matrizes
			Matriz operacao = translacaoOrigem * redimensao;
			operacao = operacao * translacaoRetorno;
			//Converte os pontos da reta
			Matriz pontoInicial = ponto3DparaMatriz( ponto2DParaHomogeneo( reta->obterCoordenadaInicial() ) );
			Matriz pontoFinal = ponto3DparaMatriz( ponto2DParaHomogeneo( reta->obterCoordenadaFinal() ) );
			//Aplica a tranformada nos pontos
			pontoInicial = pontoInicial * operacao;
			pontoFinal = pontoFinal * operacao;
			Ponto3D inicial = matrizParaPonto3D( pontoInicial );
			Ponto3D final = matrizParaPonto3D( pontoFinal );
			return new Reta( obj->nome, set2DPoint( inicial.x, inicial.y ), set2DPoint( final.x, final.y ) );
			break;
		}
		case Objeto::wireframe: {
			Wireframe * wireframe = dynamic_cast<Wireframe *>( obj );
			std::vector<Ponto2D>pontos = wireframe->obterPontos();
			double somaX, somaY;
			for( Ponto2D ponto : pontos ) {
				somaX += ponto.x;
				somaY += ponto.y;
			}
			Ponto2D centro = set2DPoint( somaX / pontos.size(), somaY / pontos.size() );
			//Criação da matriz de translacao para a origem
			Matriz translacaoOrigem = gerarMatrizTranslacao( set2DPoint( -centro.x, -centro.y ) );
			//Criação da matriz de gerarMatrizRedimensionamento
			Matriz redimensao = gerarMatrizRedimensionamento( escala.x, escala.y );
			//Criação da matriz de translacao para ponto original
			Matriz translacaoRetorno = gerarMatrizTranslacao( set2DPoint( centro.x, centro.y ) );
			//Multiplicação das matrizes
			Matriz operacao = translacaoOrigem * redimensao;
			operacao = operacao * translacaoRetorno;
			//Aplica sobre cada ponto
			std::vector<Ponto2D> pontosTranformados( pontos.size() );
			for( Ponto2D ponto : pontos ) {
				Matriz matPonto = ponto3DparaMatriz( ponto2DParaHomogeneo( ponto ) );
				matPonto = matPonto * operacao;
				Ponto3D pontoTransformadoHomogeneo = matrizParaPonto3D( matPonto );
				Ponto2D pontoTranformado = set2DPoint( pontoTransformadoHomogeneo.x, pontoTransformadoHomogeneo.y );
				pontosTranformados.push_back( pontoTranformado );

			}
			pontosTranformados.erase( pontosTranformados.begin() );
			return new Wireframe( obj->nome, pontosTranformados );
			break;
		}
	}
}
//-----------------------------------------------
Objeto * Tranformadas::rotacionar( Objeto * obj, double graus, Ponto2D pontoReferencia ) {
	graus = graus / 57.2957795131	;
	switch( obj->tipoObjeto ) {
		case Objeto::ponto: {
			Ponto * ponto = dynamic_cast<Ponto *>( obj );
			//O centro do ponto é ele mesmo(Não usa pra nada centro hue)

			//translada o ponto de referencia para o origem
			Matriz translacaoOrigem = gerarMatrizTranslacao( set2DPoint( - pontoReferencia.x, -pontoReferencia.y ) );
			//rotaciona o ponto
			Matriz rotacao = gerarMatrizRotacao( graus );
			//translada pra posicao original
			Matriz transacaoVolta = gerarMatrizTranslacao( pontoReferencia );
			//Gera a matriz de operacao;
			Matriz operacao = translacaoOrigem * rotacao;
			operacao = operacao * transacaoVolta;
			//Gera a matriz do ponto
			Ponto3D pontoHomogeneo = ponto2DParaHomogeneo( ponto->obterCoordenada() );
			Matriz matPonto = ponto3DparaMatriz( pontoHomogeneo );
			//Aplica a transformacao
			matPonto = matPonto * operacao;
			Ponto3D pontoTransformadoHomogeneo = matrizParaPonto3D( matPonto );
			return new Ponto( obj->nome, set2DPoint( pontoTransformadoHomogeneo.x, pontoTransformadoHomogeneo.y ) );


			break;
		}
		case Objeto::reta: {
			Reta * reta = dynamic_cast<Reta *>( obj );
			//translada o ponto de referencia para o origem
			Matriz translacaoOrigem = gerarMatrizTranslacao( set2DPoint( - pontoReferencia.x, -pontoReferencia.y ) );
			//rotaciona o ponto
			Matriz rotacao = gerarMatrizRotacao( graus );
			//translada pra posicao original
			Matriz transacaoVolta = gerarMatrizTranslacao( pontoReferencia );
			//Gera a matriz de operacao;
			Matriz operacao = translacaoOrigem * rotacao;
			operacao = operacao * transacaoVolta;
			//Aplica a operacao aos dois pontos
			Matriz pontoInicial = ponto3DparaMatriz( ponto2DParaHomogeneo( reta->obterCoordenadaInicial() ) );
			Matriz pontoFinal = ponto3DparaMatriz( ponto2DParaHomogeneo( reta->obterCoordenadaFinal() ) );
			pontoInicial = pontoInicial * operacao;
			pontoFinal = pontoFinal * operacao;
			Ponto3D inicial = matrizParaPonto3D( pontoInicial );
			Ponto3D final = matrizParaPonto3D( pontoFinal );
			return new Reta( obj->nome, set2DPoint( inicial.x, inicial.y ), set2DPoint( final.x, final.y ) );
			break;

		}
		case Objeto::wireframe: {
			Wireframe * wireframe = dynamic_cast<Wireframe *>( obj );
			//translada o ponto de referencia para o origem
			Matriz translacaoOrigem = gerarMatrizTranslacao( set2DPoint( - pontoReferencia.x, -pontoReferencia.y ) );
			//rotaciona o ponto
			Matriz rotacao = gerarMatrizRotacao( graus );
			//translada pra posicao original
			Matriz transacaoVolta = gerarMatrizTranslacao( pontoReferencia );
			//Gera a matriz de operacao;
			Matriz operacao = translacaoOrigem * rotacao;
			operacao = operacao * transacaoVolta;
			//Aplica a operacao a todos os pontos
			std::vector<Ponto2D> pontos = wireframe->obterPontos();
			std::vector<Ponto2D> pontosTranformados( pontos.size() );
			for( Ponto2D ponto : pontos ) {
				Matriz matPonto = ponto3DparaMatriz( ponto2DParaHomogeneo( ponto ) );
				matPonto = matPonto * operacao;
				Ponto3D pontoTransformadoHomogeneo = matrizParaPonto3D( matPonto );
				Ponto2D pontoTranformado = set2DPoint( pontoTransformadoHomogeneo.x, pontoTransformadoHomogeneo.y );
				pontosTranformados.push_back( pontoTranformado );


			}
			pontosTranformados.erase( pontosTranformados.begin() );
			return new Wireframe( obj->nome, pontosTranformados );
			break;

		}
	}
}

//-----------------------------------------------
Objeto * Tranformadas::transladar( Objeto * obj, Ponto2D direcao ) {
	switch( obj->tipoObjeto ) {
		case Objeto::ponto: {
			Ponto * ponto = dynamic_cast<Ponto *>( obj );
			return new Ponto( obj->nome, set2DPoint( ponto->obterCoordenada().x + direcao.x, ponto->obterCoordenada().y + direcao.y ) );
			break;
		}
		case Objeto::reta: {
			Reta * reta = dynamic_cast<Reta *>( obj );

			//Criação da matriz de translacao
			Matriz translacaoOrigem = gerarMatrizTranslacao( set2DPoint( direcao.x, direcao.y ) );

			Matriz operacao = translacaoOrigem ;

			//Converte os pontos da reta
			Ponto2D coordenadaInicial = reta->obterCoordenadaInicial();
			Ponto3D coordenadaInicialHomogenea = ponto2DParaHomogeneo( coordenadaInicial );
			Matriz pontoInicial( 1, 3 );
			pontoInicial = ponto3DparaMatriz( ponto2DParaHomogeneo( reta->obterCoordenadaInicial() ) );
			Matriz pontoFinal = ponto3DparaMatriz( ponto2DParaHomogeneo( reta->obterCoordenadaFinal() ) );
			std::cout << "[Transformadas]Ponto inicial tem " << pontoInicial.numLinhas() << "x" << pontoInicial.numColunas() << std::endl;
			std::cout << "[Transformadas]Ponto final tem " << pontoFinal.numLinhas() << "x" << pontoFinal.numColunas() << std::endl;
			//Aplica a tranformada nos pontos

			Matriz pontoInicialTranformado = pontoInicial * operacao;
			Matriz pontoFinalTransformado = pontoFinal * operacao;
			Ponto3D inicial = matrizParaPonto3D( pontoInicialTranformado );
			Ponto3D final = matrizParaPonto3D( pontoFinalTransformado );
			return new Reta( obj->nome, set2DPoint( inicial.x, inicial.y ), set2DPoint( final.x, final.y ) );
			break;
		}
		case Objeto::wireframe: {
			Wireframe * wireframe = dynamic_cast<Wireframe *>( obj );
			std::vector<Ponto2D>pontos = wireframe->obterPontos();

			//Criação da matriz de translacao para a origem
			Matriz translacaoOrigem = gerarMatrizTranslacao( set2DPoint( direcao.x, direcao.y ) );

			Matriz operacao = translacaoOrigem;

			//Aplica sobre cada ponto
			std::vector<Ponto2D> pontosTranformados( pontos.size() );
			for( Ponto2D ponto : pontos ) {
				Matriz matPonto = ponto3DparaMatriz( ponto2DParaHomogeneo( ponto ) );
				matPonto = matPonto * operacao;
				Ponto3D pontoTransformadoHomogeneo = matrizParaPonto3D( matPonto );
				Ponto2D pontoTranformado = set2DPoint( pontoTransformadoHomogeneo.x, pontoTransformadoHomogeneo.y );
				pontosTranformados.push_back( pontoTranformado );

			}
			pontosTranformados.erase( pontosTranformados.begin() );
			return new Wireframe( obj->nome, pontosTranformados );
			break;
		}
	}
}
//-----------------------------------------------
Matriz Tranformadas::gerarMatrizTranslacao( Ponto2D direcao ) {
	Matriz translacao( 3, 3 );
	translacao.at( 1, 1 ) = 1.;	   translacao.at( 1, 2 ) = 0;         translacao.at( 1, 3 ) = 0;

	translacao.at( 2, 1 ) = 0;	   translacao.at( 2, 2 ) = 1.;        translacao.at( 2, 3 ) = 0;

	translacao.at( 3, 1 ) = direcao.x; translacao.at( 3, 2 ) = direcao.y; translacao.at( 3, 3 ) = 1.;


	return translacao;
}
//-----------------------------------------------	
Matriz Tranformadas::gerarMatrizRedimensionamento( double escalaX, double escalaY ) {
	Matriz redimensao( 3, 3 );
	redimensao.at( 1, 1 ) = escalaX;	redimensao.at( 1, 2 ) = 0;		redimensao.at( 1, 3 ) = 0;
	redimensao.at( 2, 1 ) = 0;		redimensao.at( 2, 2 ) = escalaY;	redimensao.at( 2, 3 ) = 0;	
	redimensao.at( 3, 1 ) = 0;		redimensao.at( 3, 2 ) = 0;		redimensao.at( 3, 3 ) = 1.;
	
	return redimensao;
}
//-----------------------------------------------
Matriz Tranformadas::gerarMatrizRotacao( double graus ) {
	Matriz rotacao( 3, 3 );
	rotacao.at( 1, 1 ) = cos( graus );  rotacao.at( 1, 2 ) = -sin( graus );   rotacao.at( 1, 3 ) = 0;
	rotacao.at( 2, 1 ) = sin( graus );  rotacao.at( 2, 2 ) = cos( graus );    rotacao.at( 2, 3 ) = 0;
	rotacao.at( 3, 1 ) = 0;             rotacao.at( 3, 2 ) = 0;		  rotacao.at( 3, 3 ) = 1.;





	return rotacao;

}



















