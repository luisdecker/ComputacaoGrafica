#include <iostream>
#include <string>
#include <gtkmm/builder.h>
#include "IncludeObjectDialog.hpp"


using namespace std;//Isso é feio

IncludeObjectDialog::IncludeObjectDialog( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
	Gtk::Dialog( cobject ), builder( refGlade ) {

	builder->get_widget( "tabs_incl", tabs );
	builder->get_widget( "in_name", in_name_obj );
	builder->get_widget( "x_point", x_point );
	builder->get_widget( "y_point", y_point );
	builder->get_widget( "x0_str_line", x0_str_line );
	builder->get_widget( "y0_str_line", y0_str_line );
	builder->get_widget( "x1_str_line", x1_str_line );
	builder->get_widget( "y1_str_line", y1_str_line );
	builder->get_widget( "btn_add_point_wire", btn_add_point_wire );
	builder->get_widget( "x_wire", x_wire );
	builder->get_widget( "y_wire", y_wire );
	builder->get_widget( "rd_arame", rd_arame );
	builder->get_widget( "rd_preench", rd_preench );
//bezier
//X
	builder->get_widget( "pontoControle1x", xPontoControle1 );
	builder->get_widget( "pontoControle2x", xPontoControle2 );
	builder->get_widget( "pontoControle3x", xPontoControle3 );
	builder->get_widget( "pontoControle4x", xPontoControle4 );
//Y
	builder->get_widget( "pontoControle1y", yPontoControle1 );
	builder->get_widget( "pontoControle2y", yPontoControle2 );
	builder->get_widget( "pontoControle3y", yPontoControle3 );
	builder->get_widget( "pontoControle4y", yPontoControle4 );

	btn_add_point_wire->signal_clicked().connect( sigc::mem_fun( *this, &IncludeObjectDialog::on_btn_add_point_wire_clicked ) );

	controller = new IncludeObjectController();
}
//-----------------------------------------------
void IncludeObjectDialog::setObjectFile( ObjectFile * obf ) {
	this->lastOf = obf;
	controller->setObjectFile( obf );
}
//-----------------------------------------------
void IncludeObjectDialog::on_btn_add_point_wire_clicked() {

	string objName = in_name_obj->get_text();

	double x, y;
	if( x_wire->get_text().size() > 0 && y_wire->get_text().size() > 0 ) {

		x = stod( x_wire->get_text() );
		y = stod( y_wire->get_text() );

		controller->incluirPontoWireframe( objName, x, y );
	}

	x_wire->set_text( "" );
	y_wire->set_text( "" );

}
//-----------------------------------------------
void IncludeObjectDialog::executar() {

	int result = run();
	std::cout << "Executou a janelota"<<std::endl;
	switch( result ) {
		case Gtk::RESPONSE_OK: {
std::cout << "ok na janelota"<<std::endl;
			incluirObjeto();

			close();

		}
		break;

		case Gtk::RESPONSE_CANCEL: {
std::cout << "cancel na janelota"<<std::endl;

			close();
		}

		break;
	}
}
//-----------------------------------------------
void IncludeObjectDialog::incluirObjeto() {

	int tabNum = tabs->get_current_page();

	string objName = in_name_obj->get_text();

	switch( tabNum ) {

		//case 0: ponto
		case 0: {
			double x, y;
			if( x_point->get_text().size() > 0 && y_point->get_text().size() > 0 ) {

				x = stod( x_point->get_text() );
				y = stod( y_point->get_text() );

				controller->incluirPonto( objName, x, y );
			}

			x_point->set_text( "" );
			y_point->set_text( "" );

		}

		break;

		//case 1: reta
		case 1: {

			double x0;
			double y0;
			double x1;
			double y1;

			if( x0_str_line->get_text().size() > 0 && y0_str_line->get_text().size() > 0 &&
				x1_str_line->get_text().size() > 0 && y1_str_line->get_text().size() > 0 ) {

				x0 = stod( x0_str_line->get_text() );
				y0 = stod( y0_str_line->get_text() );
				x1 = stod( x1_str_line->get_text() );
				y1 = stod( y1_str_line->get_text() );

				controller->incluirReta( objName, x0, y0, x1, y1 );;
			}


			x0_str_line->set_text( "" );
			y0_str_line->set_text( "" );
			x1_str_line->set_text( "" );
			y1_str_line->set_text( "" );
		}

		break;

		//case 2:wireframe
		case 2: {
// d
			bool ehPreenchido = rd_preench->get_active();

			controller->confirmaInclusaoWireframe( objName, true, ehPreenchido );
			break;
		}
		case 3: {
			std::vector<Ponto2D> pontosControle;

			double xp1 = stod( xPontoControle1->get_text() );
			double xp2 = stod( xPontoControle2->get_text() );
			double xp3 = stod( xPontoControle3->get_text() );
			double xp4 = stod( xPontoControle4->get_text() );

			double yp1 = stod( yPontoControle1->get_text() );
			double yp2 = stod( yPontoControle2->get_text() );
			double yp3 = stod( yPontoControle3->get_text() );
			double yp4 = stod( yPontoControle4->get_text() );

			pontosControle.push_back( set2DPoint( xp1, yp1 ) );
			pontosControle.push_back( set2DPoint( xp2, yp2 ) );
			pontosControle.push_back( set2DPoint( xp3, yp3 ) );
			pontosControle.push_back( set2DPoint( xp4, yp4 ) );

			controller->incluirBezier(objName,pontosControle);

		}


	}

	in_name_obj->set_text( "" );

}
//-----------------------------------------------
void IncludeObjectDialog::setWindow( Window2D * window ) {
	this->controller->setWindow( window );
}


