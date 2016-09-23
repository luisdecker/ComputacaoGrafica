#include "WeilerAtherton.hpp"

WeilerAtherton::WeilerAtherton( Window2D * window ) {
	this->window = window;


	Ponto2D * supEsq = new Ponto2D();
	supEsq->x = window->superiorEsquerdo().x;
	supEsq->y = window->superiorEsquerdo().y;
	clipPoints.push_back( supEsq );

	Ponto2D * supDir = new Ponto2D();
	supDir->x = window->superiorDireito().x;
	supDir->y = window->superiorDireito().y;
	clipPoints.push_back( supDir );

	Ponto2D * infDir = new Ponto2D();
	infDir->x = window->inferiorDireito().x;
	infDir->y = window->inferiorDireito().y;
	clipPoints.push_back( infDir );

	Ponto2D * infEsq = new Ponto2D();
	infEsq->x = window->inferiorEsquerdo().x;
	infEsq->y = window->inferiorEsquerdo().y;
	clipPoints.push_back( infEsq );


}

Ponto2D * WeilerAtherton::calculaInterseccaoEntreRetas( Ponto2D a, Ponto2D b, Ponto2D c, Ponto2D d ) {

	double a1 = b.y - a.y;
	double b1 = a.x - b.x;
	double c1 = a1 * a.x + b1 * a.y;

	double a2 = d.y - c.y;
	double b2 = c.x - d.x;
	double c2 = a2 * c.x + b2 * c.y;

	double det = a1 * b2 - a2 * b1;
	double x = ( b2 * c1 - b1 * c2 ) / det;
	double y = ( a1 * c2 - a2 * c1 ) / det;

	Ponto2D * newPoint = new Ponto2D();
	newPoint->x = x;
	newPoint->y = y;
	return newPoint;

}


//dados três pontos p, q, r, a função verifica se q está sobre o segmento pr.

bool  WeilerAtherton::onSegment( Ponto2D p, Ponto2D q, Ponto2D r ) {
	if( q.x <= std::max( p.x, r.x ) && q.x >= std::min( p.x, r.x ) &&
		q.y <= std::max( p.y, r.y ) && q.y >= std::min( p.y, r.y ) )
		return true;

	return false;
}

// Encontra a orientação para uma tripla de pontos (p, q, r).
// A função retorna os seguintes valores:
// 0 --> p, q and r são colineares
// 1 --> sentido horário
// 2 --> sentido anti-horário
int  WeilerAtherton::orientation( Ponto2D p, Ponto2D q, Ponto2D r ) {

	int val = ( q.y - p.y ) * ( r.x - q.x ) -
			  ( q.x - p.x ) * ( r.y - q.y );

	if( val == 0 ) return 0;

	return ( val > 0 ) ? 1 : 2;
}

//determina interseccção entre duas retas, especificadas por suas coordenadas cartesianas
//explicação em detalhes no livro de algoritmos do cormen.
bool  WeilerAtherton::doIntersect( Ponto2D p1, Ponto2D q1, Ponto2D p2, Ponto2D q2 ) {

	int o1 = orientation( p1, q1, p2 );
	int o2 = orientation( p1, q1, q2 );
	int o3 = orientation( p2, q2, p1 );
	int o4 = orientation( p2, q2, q1 );


	if( o1 != o2 && o3 != o4 )
		return true;


	if( o1 == 0 && onSegment( p1, p2, q1 ) ) return true;


	if( o2 == 0 && onSegment( p1, q2, q1 ) ) return true;


	if( o3 == 0 && onSegment( p2, p1, q2 ) ) return true;


	if( o4 == 0 && onSegment( p2, q1, q2 ) ) return true;

	return false;
}

std::vector<Wireframe *> WeilerAtherton::clip( Wireframe * obj ) {

	std::vector<Ponto2D *> inClipPoints, inSubjectPoints;

	inClipPoints = clipPoints;
//Rotaciona os pontos para ficar de acordo com a window.
	obj = dynamic_cast<Wireframe * >( Tranformadas::rotacionar( obj, -( window->obterRotacao() ), window->obterCentro() ) );

	std::vector<Ponto2D> objPoints = obj->obterPontos();

	for( int i = 0; i < objPoints.size(); i++ ) {

		Ponto2D * auxPoint = new Ponto2D();
		auxPoint->x = objPoints[i].x;
		auxPoint->y = objPoints[i].y;

		subjectPoints.push_back( auxPoint );
		inSubjectPoints.push_back( auxPoint );
	}


	int lenClipPoints = inClipPoints.size();

	for( int i = 0; i < lenClipPoints; i++ ) {

		Ponto2D * A = inClipPoints[( i + lenClipPoints - 1 ) % lenClipPoints];
		Ponto2D * B = inClipPoints[i];

		int lenSubjPoints = inSubjectPoints.size();

		for( int j = 0; j < lenSubjPoints; j++ ) {

			Ponto2D * P = inSubjectPoints[( j + lenSubjPoints - 1 ) % lenSubjPoints];
			Ponto2D * Q =  inSubjectPoints[j];

			if( doIntersect( *A, *B, *P, *Q ) ) {

				Ponto2D * pontoInterseccao = calculaInterseccaoEntreRetas( *A, *B, *P, *Q );
				pontoInterseccao->interseccao = true;

				std::vector<Ponto2D *>::iterator itP = procuraPonto( subjectPoints, *P );


				if( pontoInterseccao->x > P->x ) {

					itP++;
					Ponto2D * aux = *itP;

					while( pontoInterseccao->x > aux->x ) {
						itP++;
						aux = *itP;
					}

					subjectPoints.insert( itP, pontoInterseccao );

				} else if( pontoInterseccao->x < P->x ) {
					itP++;
					Ponto2D * aux = *itP;

					while( pontoInterseccao->x < aux->x ) {
						itP++;
						aux = *itP;
					}

					subjectPoints.insert( itP, pontoInterseccao );
				} else if( pontoInterseccao->x == P->x ) {
					if( pontoInterseccao->y > P->y ) {

						itP++;
						Ponto2D * aux = *itP;

						while( pontoInterseccao->y > aux->y ) {
							itP++;
							aux = *itP;
						}

						subjectPoints.insert( itP, pontoInterseccao );

					} else {
						itP++;
						Ponto2D * aux = *itP;

						while( pontoInterseccao->y < aux->y ) {
							itP++;
							aux = *itP;
						}

						subjectPoints.insert( itP, pontoInterseccao );
					}

				}

				std::vector<Ponto2D *>::iterator itA = procuraPonto( clipPoints, *A );

				if( pontoInterseccao->x > A->x ) {
					itA++;
					Ponto2D * aux = *itA;

					while( pontoInterseccao->x > aux->x ) {
						itA++;
						aux = *itA;
					}

					clipPoints.insert( itA, pontoInterseccao );

				} else if( pontoInterseccao->y < A->y ) {

					itA++;

					Ponto2D * aux = *itA;

					while( pontoInterseccao->y < aux->y ) {
						itA++;
						aux = *itA;
					}

					clipPoints.insert( itA, pontoInterseccao );

				} else if( pontoInterseccao->x < A->x ) {

					itA++;

					Ponto2D * aux = *itA;

					while( pontoInterseccao->x < aux->x ) {
						itA++;
						aux = *itA;
					}

					clipPoints.insert( itA, pontoInterseccao );

				} else {

					itA++;

					if( itA == clipPoints.end() ) {
						itA = clipPoints.begin();
					}

					Ponto2D * aux = *itA;

					while( pontoInterseccao->y > aux->y ) {
						itA++;

						aux = *itA;
					}

					clipPoints.insert( itA, pontoInterseccao );
				}


			}
		}
	}

	definePontosDeEntrada();

	std::vector<Wireframe *> objs;

	while( !todosPontosEntradaVisitados() ) {

		Wireframe * wf = new Wireframe( "teste" );
		objs.push_back( wf );

		std::vector<Ponto2D *>::iterator iterSubj = proximoPontoEntrada();
		Ponto2D * primeiro = *iterSubj;
		wf->adicionarPonto( *primeiro );

		iterSubj++;
		bool objRecortado = false;

		while( !objRecortado ) {

			if( iterSubj == subjectPoints.end() ) {
				iterSubj = subjectPoints.begin();
			}

			Ponto2D * auxPoint = *iterSubj;
			auxPoint->visitado = true;
			wf->adicionarPonto( *auxPoint );

			if( auxPoint->interseccao ) {

				std::vector<Ponto2D *>::iterator iterClip = procuraPonto( clipPoints, *auxPoint );

				iterClip++;

				while( !objRecortado ) {

					if( iterClip == clipPoints.end() ) {
						iterClip = clipPoints.begin();
					}
					Ponto2D * auxPoint2 = *iterClip;
					auxPoint2->visitado = true;

					if( *iterClip == primeiro ) {
						objRecortado = true;
					} else if( auxPoint2->interseccao ) {
						wf->adicionarPonto( *auxPoint2 );
						iterSubj = procuraPonto( subjectPoints, *auxPoint2 );
						break;
					}
					iterClip++;
				}

			}

			iterSubj++;


		}
		//Roda de volta pra orientacao do mundo.
		wf = dynamic_cast<Wireframe *>( Tranformadas::rotacionar( wf, window->obterRotacao(), window->obterCentro() ) );

	}

	if( objs.size() == 0 ) {
	objs.push_back(obj);
	}
	return objs;
}

std::vector<Ponto2D *>::iterator WeilerAtherton::procuraPonto( std::vector<Ponto2D *> & lista, Ponto2D pontoBusca ) {

	std::vector<Ponto2D *>::iterator itVec;

	for( itVec = lista.begin(); itVec < lista.end(); itVec++ ) {

		Ponto2D pontoLista = **itVec;

		if( pontoLista.x == pontoBusca.x && pontoLista.y == pontoBusca.y ) {

			return itVec;

		}

	}
}


bool WeilerAtherton::todosPontosEntradaVisitados() {

	int lenSubjPoints = subjectPoints.size();

	for( int i = 0; i < lenSubjPoints; i++ ) {

		if( subjectPoints[i]->entrada && !subjectPoints[i]->visitado ) {
			return false;
		}
	}

	return true;

}

std::vector<Ponto2D *>::iterator WeilerAtherton::proximoPontoEntrada() {

	std::vector<Ponto2D *>::iterator subjIter;

	Ponto2D * aux;

	for( subjIter = subjectPoints.begin(); subjIter < subjectPoints.end(); subjIter++ ) {

		aux = *subjIter;

		if( aux->entrada &&  !aux->visitado ) {

			aux->visitado = true;

			return subjIter;
		}
	}

}

void WeilerAtherton::definePontosDeEntrada() {

	int i;
	int lenSubjPoints = subjectPoints.size();


	for( i = 0; i < lenSubjPoints; i++ ) {

		if( subjectPoints[i]->interseccao ) {
			Ponto2D * A = subjectPoints[( i + lenSubjPoints - 2 ) % lenSubjPoints];
			Ponto2D * B = subjectPoints[( i + lenSubjPoints - 1 ) % lenSubjPoints];
			Ponto2D * C = subjectPoints[i];

			if( orientation( *A, *B, *C ) == 1 ) {
				break;
			}
		}
	}

	bool ultimo = true;

	for( int j = i; j < i + lenSubjPoints; j++ ) {

		if( subjectPoints[j % lenSubjPoints]->interseccao ) {
			subjectPoints[j % lenSubjPoints]->entrada = ultimo;
			ultimo = !ultimo;
		}

	}

}

