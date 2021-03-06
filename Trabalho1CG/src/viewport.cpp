/*
 * ViewPort de um Sistema Gráfico Interativo
 * Copyright (C) 2016  <Luís Gustavo Lorgus Decker> <decker@incod.ufsc.br>
 * 		               <Cesar Smaniotto Júnior>     <cesarsjb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "viewport.h"

//-----------------------------------------------
ViewPort::ViewPort( Ponto2D superiorEsquerdo, Ponto2D inferiorDireito ) {
	this->se = superiorEsquerdo, this->id = inferiorDireito;
}
//-----------------------------------------------
int ViewPort::obterXMaximo() {
	return id.x;
}
//-----------------------------------------------
int ViewPort::obterXMinimo() {
	return se.x;
}
//-----------------------------------------------
int ViewPort::obterYMaximo() {
	return id.y;
}
//-----------------------------------------------
int ViewPort::obterYMinimo() {
	return se.y;
}
//-----------------------------------------------
int ViewPort::obterAltura() {
	return obterYMaximo() - obterYMinimo();
}
//-----------------------------------------------
int ViewPort::obterLargura() {
	return obterXMaximo() - obterXMinimo();
}

//-----------------------------------------------
Ponto2D ViewPort::tranformarCoordenadas( Window2D window, Ponto2D ponto ) {// Confia que essa tripa ta certa.
	double xvp = ( ( ponto.x - window.obterXMinimo() ) / ( window.obterXMaximo() - window.obterXMinimo() ) ) * ( obterXMaximo() - obterXMinimo() );
	double yvp = ( 1 - ( ( ponto.y - window.obterYMinimo() ) / ( window.obterYMaximo() - window.obterYMinimo() ) ) ) * ( obterYMaximo() - obterYMinimo() );
	return set2DPoint( xvp, yvp );
}
//-----------------------------------------------
Ponto2D ViewPort::tranformarCoordenadasSCN( Window2D window, Ponto2D ponto ) {

	//A idéia é primeiro "expandir" (redimensinando para um vetor de tamanho largura/2, altura/2),
	//isso vai dar os objetos com o centro no canto da viewport. Após isso, tranladar todos os objetos para largura/2, altura/2
	//(para compensar o fato da window ter seu centro no centro da window, e não num dos cantos)
	Ponto3D pontoHomogeneo = Tranformadas::ponto2DParaHomogeneo( ponto );
	Matriz matPonto = Tranformadas::ponto3DparaMatriz( pontoHomogeneo );
	Matriz matExpansao = Tranformadas::gerarMatrizRedimensionamento( obterLargura(), obterAltura() );
	Matriz matTranslacao = Tranformadas::gerarMatrizTranslacao( set2DPoint( obterLargura() / 2, obterAltura() / 2 ) );
	Matriz operacao = matExpansao * matTranslacao;
	matPonto = matPonto * operacao;
	Ponto3D pontoTranformadoHomogeneo = Tranformadas::matrizParaPonto3D( matPonto );
	Ponto2D pontoTranformado = set2DPoint( pontoTranformadoHomogeneo.x, pontoTranformadoHomogeneo.y );
	pontoTranformado.y = obterAltura() - pontoTranformado.y;
	return pontoTranformado;
}








