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

	switch( result ) {
		case Gtk::RESPONSE_OK: {

			incluirObjeto();

			close();

		}
		break;

		case Gtk::RESPONSE_CANCEL: {

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

			bool ehPreenchido = rd_preench->get_active();

			controller->confirmaInclusaoWireframe( objName, true, ehPreenchido );

		}
		break;
	}

	in_name_obj->set_text( "" );

}
//-----------------------------------------------
void IncludeObjectDialog::setWindow( Window2D * window ) {
	this->controller->setWindow( window );
}


