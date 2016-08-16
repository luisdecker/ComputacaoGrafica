//Global include
#include <iostream>
//Local include
#include "objectfile.h"
#include "window.h"
#include "viewport.h"

int main( int argc, char ** argv ) {
	ObjectFile of;
	Objeto * linha = new Reta( "", set2DPoint( 1, 1 ), set2DPoint( 2, 2 ) );
	std::cout << "Hello, world!" << std::endl;
	return 0;
}
