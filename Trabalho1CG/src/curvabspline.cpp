#include "objeto.h"
#include "matriz.hpp"
#include "tipos.hpp"
#include <math.h>

void CurvaBSpline::calculaPontos(){

	Matriz matrizBSpline(4,4);

	matrizBSpline.at(1,1) = -1.0/6;
	matrizBSpline.at(1,2) = 1.0/2;
	matrizBSpline.at(1,3) = -1.0/2;
	matrizBSpline.at(1,4) = 1.0/6;
	matrizBSpline.at(2,1) = 1.0/2;
	matrizBSpline.at(2,2) = -1;
	matrizBSpline.at(2,3) = 1.0/2;
	matrizBSpline.at(2,4) = 0;
	matrizBSpline.at(3,1) = -1.0/2;
	matrizBSpline.at(3,2) = 0;
	matrizBSpline.at(3,3) = 1.0/2;
	matrizBSpline.at(3,4) = 0;
	matrizBSpline.at(4,1) = 1.0/6;
	matrizBSpline.at(4,2) = 2.0/3;
	matrizBSpline.at(4,3) = 1.0/6;
	matrizBSpline.at(4,4) = 0;

	double delta = 1.0/resolucao;

	Matriz matrizDelta(4,4);

	double deltaCubo = pow(delta,3.0);
	double deltaQuadrado = pow(delta,2.0);

	matrizDelta.at(1,1) = 0;
	matrizDelta.at(1,2) = 0;
	matrizDelta.at(1,3) = 0;
	matrizDelta.at(1,4) = 1;
	matrizDelta.at(2,1) = deltaCubo;
	matrizDelta.at(2,2) = deltaQuadrado;
	matrizDelta.at(2,3) = delta;
	matrizDelta.at(2,4) = 0;
	matrizDelta.at(3,1) = 6*deltaCubo;
	matrizDelta.at(3,2) = 2*deltaQuadrado;
	matrizDelta.at(3,3) = 0;
	matrizDelta.at(3,4) = 0;
	matrizDelta.at(4,1) = 6 * deltaCubo;
	matrizDelta.at(4,2) = 0;
	matrizDelta.at(4,3) = 0;
	matrizDelta.at(4,4) = 0;

	for(int i=0; i + 4 <= pontosDeControle.size(); i++ ){

		Matriz Gx(4,1);
		Matriz Gy(4,1);

		for(int j=1; j < 5; j++){

			Ponto2D pontoControle = pontosDeControle[i+j-1];

			Gx.at(j,1) = pontoControle.x;
			Gy.at(j,1) = pontoControle.y;
		}

		Matriz Cx(4,1);
		Matriz Cy(4,1);

		Cx = matrizBSpline * Gx;
		Cy = matrizBSpline * Gy;

		Matriz diferencasIniciaisX(4,1);
		Matriz diferencasIniciaisY(4,1);

		diferencasIniciaisX = matrizDelta * Cx;
		diferencasIniciaisY = matrizDelta * Cy;

		std::vector<Ponto2D> pontosFwdDiff = calculaPontosFwdDiff(diferencasIniciaisX,diferencasIniciaisY);

		pontosCalculados.insert(pontosCalculados.end(), pontosFwdDiff.begin(), pontosFwdDiff.end());

	}

}

std::vector<Ponto2D> CurvaBSpline::calculaPontosFwdDiff(Matriz diferencasIniciaisX, Matriz diferencasIniciaisY){

	std::vector<Ponto2D> pontosFwdDiff;

	double xvelho,yvelho, x,dx,d2x,d3x,y,dy,d2y,d3y;

	x = diferencasIniciaisX.at(1,1);
	dx = diferencasIniciaisX.at(2,1);
	d2x = diferencasIniciaisX.at(3,1);
	d3x = diferencasIniciaisX.at(4,1);
	y = diferencasIniciaisY.at(1,1);
	dy = diferencasIniciaisY.at(2,1);
	d2y = diferencasIniciaisY.at(3,1);
	d3y = diferencasIniciaisY.at(4,1);

	xvelho = x;
	yvelho = y;

	pontosFwdDiff.push_back(set2DPoint(xvelho,yvelho));

	for(int i=1; i < resolucao; i++){

		x = x + dx;  
		dx = dx + d2x;
		d2x = d2x + d3x;

		y = y + dy;  
		dy = dy + d2y;
		d2y = d2y + d3y;
				
		xvelho = x; 
		yvelho = y; 

		pontosFwdDiff.push_back(set2DPoint(xvelho,yvelho));


	}

	return pontosFwdDiff;

}

//-----------------------------------------------
void CurvaBSpline::atualizarCoordenadaExibicao( Objeto * objeto ) {
	if( objeto == nullptr ) {
		desenhar = false;
		return;
	}
	CurvaBSpline * curva = dynamic_cast<CurvaBSpline *>( objeto );
	if( curva->pontosExibicao.empty() ) {
		desenhar = false;
		return;
	}
	this->pontosExibicao = curva->pontosExibicao;
	desenhar = true;	
}

//----------------------------------------------
void CurvaBSpline::atualizarCoordenadaSCN( Matriz transformacao ) {
	if( desenhar ) {
		std::vector<Ponto2D> pontosSCN;
		for( Ponto2D ponto : this->pontosExibicao ) {
			Matriz matPonto( Tranformadas::ponto2DParaHomogeneo( ponto ) );
			matPonto = matPonto * transformacao;
			Ponto3D novoPontoHomogeneo = Tranformadas::matrizParaPonto3D( matPonto );
			pontosSCN.push_back( Ponto2D( novoPontoHomogeneo.x, novoPontoHomogeneo.y ) );
		}
		this->pontosSCN = pontosSCN;
	}
}
//-----------------------------------------------
std::vector<Ponto2D> CurvaBSpline::obterCoordenadasSCN() {
	return std::vector<Ponto2D> ( pontosSCN );
}