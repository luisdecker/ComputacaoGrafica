#include <iostream>
#include <string>
#include <gtkmm/builder.h>
#include "IncludeObjectDialog.hpp"


using namespace std;

IncludeObjectDialog::IncludeObjectDialog( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
	Gtk::Dialog( cobject ), builder( refGlade ) {

	builder->get_widget( "tabs", tabs );
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

	btn_add_point_wire->signal_clicked().connect( sigc::mem_fun( *this, &IncludeObjectDialog::on_btn_add_point_wire_clicked ) );

}

void IncludeObjectDialog::on_btn_add_point_wire_clicked(){

	string objName = in_name_obj->get_text();

	double x, y;
	if( x_wire->get_text().size() > 0 && y_wire->get_text().size() > 0 ) {

		x = stod( x_wire->get_text() );
		y = stod( y_wire->get_text() );

		if( lastOf->contemObjeto( objName ) ) {
			Wireframe * wire = dynamic_cast<Wireframe * > (lastOf->obterObjetoNome( objName ));
			wire->adicionarPonto(set2DPoint(x,y));

		} else {
			Wireframe * wire = new Wireframe(objName);
			lastOf->inserirObjeto( wire );
			wire->adicionarPonto(set2DPoint(x,y));
		}
	}

	
	x_wire->set_text("");
	y_wire->set_text("");
	

}

bool IncludeObjectDialog::executar( ObjectFile * of ) {
	this->lastOf = of;

	bool objInserido = false;

	int result = run();

	switch( result ) {
		case Gtk::RESPONSE_OK:{

			if(incluirObjeto()){
				objInserido = true;
			}

			close();
			}
			break;

		case Gtk::RESPONSE_CANCEL:{

			close();
		}

			break;
	}
	return objInserido;
}

bool IncludeObjectDialog::incluirObjeto() {

	int tabNum = tabs->get_current_page();

	string objName = in_name_obj->get_text();

	bool objInserido = false;

	switch( tabNum ) {

		//case 0: ponto
		case 0: {
			double x, y;
			if( x_point->get_text().size() > 0 && y_point->get_text().size() > 0 ) {

				x = stod( x_point->get_text() );
				y = stod( y_point->get_text() );

				Ponto * p = new Ponto( objName, set2DPoint( x, y ) );
				if( !lastOf->contemObjeto( objName ) ) {
					lastOf->inserirObjeto( p );
				} else {
					lastOf->atualizarObjeto( p );
				}

				objInserido = true;
			}

			
			x_point->set_text("");
			y_point->set_text("");

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

				Reta * r = new Reta( objName, set2DPoint( x0, y0 ), set2DPoint( x1, y1 ) );
				if( !lastOf->contemObjeto( objName ) ) {
					lastOf->inserirObjeto( r );
				} else {
					lastOf->atualizarObjeto( r );
				}

				objInserido = true;
			}
			

			x0_str_line->set_text("");
			y0_str_line->set_text("");
			x1_str_line->set_text("");
			y1_str_line->set_text("");
		}

		break;

		//case 2: polígono (a ser feito depois que o resto tiver pronto)
		case 2: {
			objInserido = lastOf->contemObjeto( objName );
		}
			break;
	}

	in_name_obj->set_text("");

	return objInserido;

}


