/*
 * Objeto de mundo de um Sistema Gráfico Interativo
 * Copyright (C) 2016  <Luís Gustavo Lorgus Decker> <decker@incod.ufsc.br>
 * 		       <Cesar Smaniotto Júnior>     <cesarsjb@gmail.com>
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

#ifndef OBJETO_H
#define OBJETO_H

//Global Includes
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <list>
#include <vector>
//Local Includes
#include "tipos.hpp"
//#include "window.h" //Circular
#include "matriz.hpp"
#include "transformadas.hpp"
#define to_ponto(x) dynamic_cast<Ponto*>(x)
#define to_reta(x) dynamic_cast<Reta*>(x)
#define to_wireframe(x) dynamic_cast<Wireframe*>(x)


class Tranformadas;
class Objeto {
public:
	enum tipo {ponto, reta, wireframe, bezier}; //Enumerador com os tipos de objeto
	//-----------------------------------------------
	std::string nome;//O nome do objeto
	//-----------------------------------------------
	tipo tipoObjeto;//O tipo do objeto
	//-----------------------------------------------

	Objeto() {}; //Construtor padrão
	//-----------------------------------------------
	virtual ~Objeto() {}; //Destrutor

	Ponto2D obterCentro() {
		return set2DPoint( 0, 0 );
	}

	virtual void atualizarCoordenadaSCN( Matriz transformacao ) = 0;

	virtual void atualizarCoordenadaExibicao( Objeto * objeto ) = 0;

	bool desenhar;
private:

};
//-----------------------------------------------------------------------------------------------------
class Ponto : public Objeto {
public:
	//-----------------------------------------------
	//Contrutor padrão
	Ponto( std::string nome ) {
		coordenada = set2DPoint( 0, 0 );
		tipoObjeto = Objeto::ponto;
		this->nome = nome;
		desenhar = false;
	};
	//-----------------------------------------------

	Ponto( std::string nome, Ponto2D coordenada );  //Contrutor parametrizado

	//-----------------------------------------------
	Ponto2D obterCoordenada(); //Retorna a coordenada do ponto.
	//-----------------------------------------------
	//void atualizarCoordenadaSCN( Ponto2D coordenada );
	//-----------------------------------------------
	Ponto2D obterCentro();
	//-----------------------------------------------
	virtual void atualizarCoordenadaSCN( Matriz transformacao );
	//-----------------------------------------------
	Ponto2D obterCoordenadaSCN();//Retorna a coordenada do ponto em SCN
	//-----------------------------------------------
	virtual void atualizarCoordenadaExibicao( Objeto * objeto );
private:

	Ponto2D coordenada; //coordenada do ponto no mundo;
	//-----------------------------------------------
	Ponto2D coordenadaSCN;//Coordenada no SCN;
	//-----------------------------------------------
	Ponto2D coordenadaExibicao;//Coordenada no mundo apos clip
};
//-----------------------------------------------------------------------------------------------------

class Reta : public Objeto {
public:
	//-----------------------------------------------
	//Cosntrutor padrão
	Reta( std::string nome ) {
		pontoInicial = set2DPoint( 0, 0 );
		pontoFinal = set2DPoint( 0, 0 );
		tipoObjeto = Objeto::reta;
		this->nome = nome;
		desenhar = false;
	}
	//-----------------------------------------------
	Reta( std::string nome, Ponto2D pontoInicial, Ponto2D pontoFinal );  //Contrutor parametrizado
	//-----------------------------------------------
	Ponto2D obterCoordenadaInicial();//Retorna o ponto inicial da reta.
	//-----------------------------------------------
	Ponto2D obterCoordenadaInicialSCN();
	//-----------------------------------------------
	Ponto2D obterCoordenadaFinal();//Retorna o ponto final da reta.
	//-----------------------------------------------
	Ponto2D obterCoordenadaFinalSCN();
	//-----------------------------------------------
	Ponto2D obterCentro();
	//-----------------------------------------------
	virtual void atualizarCoordenadaSCN( Matriz transformacao );
	//-----------------------------------------------
	virtual void atualizarCoordenadaExibicao( Objeto * objeto );
private:
	Ponto2D pontoInicial, pontoInicialSCN;
	//-----------------------------------------------
	Ponto2D pontoFinal, pontoFinalSCN;
	//-----------------------------------------------
	Ponto2D pontoInicialExibicao, pontoFinalExibicao;

};
//-----------------------------------------------------------------------------------------------------

class Wireframe: public Objeto {
public:
	//-----------------------------------------------
	//Construtor padrão
	Wireframe( std::string nome ) {
		this->pontos.clear();
		this->pontosSCN.clear();
		this->pontosExibicao.clear();
		//this->pontos.push_back( set2DPoint( 0, 0 ) );
		this->nome = nome;
		this->tipoObjeto = Objeto::wireframe;
		this->preenchido = false;
		this->todosPontosInclusos = false;
		desenhar = false;
	}
	//-----------------------------------------------
	Wireframe( std::string nome, std::vector<Ponto2D> pontos ); //Contrutor parametrizado
	//-----------------------------------------------
	std::vector<Ponto2D> obterPontos();//Retorna um vetor com os pontos do poligono.
	//-----------------------------------------------
	std::vector<std::vector< Ponto2D>> obterPontosSCN();//Retorna um vetor com os pontos SCN do poligono.
	//-----------------------------------------------
	void adicionarPonto( Ponto2D ponto ); //Adiciona um ponto a lista.
	//-----------------------------------------------
	Ponto2D obterCentro();
	//-----------------------------------------------
	virtual void atualizarCoordenadaSCN( Matriz transformacao );
	//-----------------------------------------------
	virtual void atualizarCoordenadaExibicao( Objeto * objeto );
	//-----------------------------------------------
	void atualizarCoordenadaExibicao( std::vector<Wireframe *> subObjetos );
	//-----------------------------------------------
	void setPreenchido( bool preenchido );
	//-----------------------------------------------
	bool ehPreenchido();
	//-----------------------------------------------
	void setTodosPontosInclusos( bool todosPontosInclusos );
	//-----------------------------------------------
	bool possuiTodosPontosInclusos();
	//-----------------------------------------------
	void atualizarRetas( std::vector<Reta *> retas );
	//-----------------------------------------------
	std::vector<Reta *> obterRetas();
	//-----------------------------------------------


private:
	bool preenchido;
	//-----------------------------------------------
	bool todosPontosInclusos;
	//-----------------------------------------------
	std::vector<Ponto2D> pontos;//Vetor de pontos ordenados. O poligono é ligado seguinto a ordem desta lista.
	//-----------------------------------------------
	std::vector<std::vector<Ponto2D>> pontosSCN;//Pontos na SCN.
	//-----------------------------------------------
	std::vector<Reta *> retasWireframeSCN; //Retas para o desenho de um wireframe em SCN
	//-----------------------------------------------
	std::vector<Wireframe *> pontosExibicao;//Pontos apos clip.
	//-----------------------------------------------
	std::vector<Reta * >retasWireframe; //Retas para o desenho de um wireframe.

};
class CurvaBezier : public Objeto {
public:
	//Construtor padrao
	CurvaBezier( std::string nome ) {
		resolucao = 20;
		this->nome = nome;
		this->pontosDeControle.clear();
		this->desenhar = false;
		this->tipoObjeto = bezier;
	}
	//-----------------------------------------------
	//Construtor para passagem de pontos de exibicao
	CurvaBezier( std::vector<Ponto2D>pontosExibicao ) {
		resolucao = 20;
		this->nome = "Temporario";
		this->pontosExibicao = pontosExibicao;
		this->tipoObjeto = bezier;
	}
	//-----------------------------------------------
	//Construtor com passagem de pontos de controle;
	CurvaBezier( std::string nome, std::vector<Ponto2D> pontosControle ) {
		resolucao = 20;
		this->nome = nome;
		this->pontosDeControle = pontosControle;
		this->desenhar = false;
		this->tipoObjeto = bezier;
		this->pontosCalculados = caculaPontos( resolucao );
	}
	//-----------------------------------------------
	//Atualiza coordenadas de exibicao (Clipadas)
	virtual void atualizarCoordenadaExibicao( Objeto * objeto );
	//-----------------------------------------------
	//Atualiza as cordanadas no Sistema de Coordenadas Normalizadas
	virtual void atualizarCoordenadaSCN( Matriz transformacao );
	//-----------------------------------------------
	//Calculas n pontos para a curva
	std::vector<Ponto2D> caculaPontos( int numeroPontos );
	//-----------------------------------------------
	//Atualiza as coordenaadas de controle;
	void atualizaCoordenadasControle( std::vector<Ponto2D> coordenadas );
	//-----------------------------------------------
	//Atualiza a resolucao da curva
	void atualizaResolucao( int numeroPontos ) {this->resolucao = numeroPontos;}
	//-----------------------------------------------
	//Obtem os pontos SCN
	std::vector<Ponto2D> obterCoordenadasSCN();
	//-----------------------------------------------
	//Obtem os pontos calculados
	std::vector<Ponto2D> obterPontosCalculados() {return std::vector<Ponto2D>( pontosCalculados );}
	//-----------------------------------------------
	//Obtem as coordenadas de exibicao
	std::vector<Ponto2D> obterCoordenadasExibicao() {return std::vector<Ponto2D> ( pontosExibicao );}

private:
	//Pontos de controle da curva de bezier
	std::vector<Ponto2D> pontosDeControle;
	//-----------------------------------------------
	//Pontos interpolados da curva
	std::vector<Ponto2D> pontosCalculados;
	//-----------------------------------------------
	//Pontos de exibicao (clipados) da curva
	std::vector<Ponto2D> pontosExibicao;
	//-----------------------------------------------
	//Pontos SCN da curva;
	std::vector<Ponto2D> pontosSCN;
	//-----------------------------------------------
	//Resolucao da curva (Numero de pontos)
	int resolucao;
	//-----------------------------------------------
	//Gera o elemento Bk[L]
	double gerarBk( double l, double k, double t );
	//-----------------------------------------------
	//Calcula um ponto da curva, para dado t
	Ponto2D calculaPonto( double t );

};

#endif // OBJETO_H

