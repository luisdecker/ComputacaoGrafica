#ifndef INCLUDEOBJECTDIALOG_H
#define INCLUDEOBJECTDIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/notebook.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include <string>
#include "objectfile.h"
#include "IncludeObjectController.hpp"
#include "window.h"



class IncludeObjectDialog : public Gtk::Dialog {

	void incluirObjeto();

	IncludeObjectController * controller;

protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Notebook * tabs;
	Gtk::Entry * in_name_obj;
	Gtk::Entry * x_point;
	Gtk::Entry * y_point;
	Gtk::Entry * x0_str_line;
	Gtk::Entry * y0_str_line;
	Gtk::Entry * x1_str_line;
	Gtk::Entry * y1_str_line;
	ObjectFile * lastOf;
	Gtk::Button * btn_add_point_wire;
	Gtk::Entry * x_wire;
	Gtk::Entry * y_wire;
	Gtk::RadioButton * rd_arame;
	Gtk::RadioButton * rd_preench;
	
	//Botoes de bezier
	Gtk::Entry * xPontoControle1;
	Gtk::Entry * xPontoControle2;
	Gtk::Entry * xPontoControle3;
	Gtk::Entry * xPontoControle4;

	Gtk::Entry * yPontoControle1;	
	Gtk::Entry * yPontoControle2;	
	Gtk::Entry * yPontoControle3;	
	Gtk::Entry * yPontoControle4;

	//inputs b-spline

	Gtk::Entry * pto_ctrl_spl_x1;
	Gtk::Entry * pto_ctrl_spl_x2;
	Gtk::Entry * pto_ctrl_spl_x3;
	Gtk::Entry * pto_ctrl_spl_x4;
	Gtk::Entry * pto_ctrl_spl_x5;
	Gtk::Entry * pto_ctrl_spl_x6;
	Gtk::Entry * pto_ctrl_spl_x7;
	Gtk::Entry * pto_ctrl_spl_x8;
	Gtk::Entry * pto_ctrl_spl_x9;
	Gtk::Entry * pto_ctrl_spl_x10;
	Gtk::Entry * pto_ctrl_spl_x11;
	Gtk::Entry * pto_ctrl_spl_x12;
	Gtk::Entry * pto_ctrl_spl_x13;
	Gtk::Entry * pto_ctrl_spl_x14;
	Gtk::Entry * pto_ctrl_spl_x15;
	Gtk::Entry * pto_ctrl_spl_x16;
	Gtk::Entry * pto_ctrl_spl_x17;
	Gtk::Entry * pto_ctrl_spl_x18;

	Gtk::Entry * pto_ctrl_spl_y1;
	Gtk::Entry * pto_ctrl_spl_y2;
	Gtk::Entry * pto_ctrl_spl_y3;
	Gtk::Entry * pto_ctrl_spl_y4;
	Gtk::Entry * pto_ctrl_spl_y5;
	Gtk::Entry * pto_ctrl_spl_y6;
	Gtk::Entry * pto_ctrl_spl_y7;
	Gtk::Entry * pto_ctrl_spl_y8;
	Gtk::Entry * pto_ctrl_spl_y9;
	Gtk::Entry * pto_ctrl_spl_y10;
	Gtk::Entry * pto_ctrl_spl_y11;
	Gtk::Entry * pto_ctrl_spl_y12;
	Gtk::Entry * pto_ctrl_spl_y13;
	Gtk::Entry * pto_ctrl_spl_y14;
	Gtk::Entry * pto_ctrl_spl_y15;
	Gtk::Entry * pto_ctrl_spl_y16;
	Gtk::Entry * pto_ctrl_spl_y17;
	Gtk::Entry * pto_ctrl_spl_y18;
	
	


public:

	IncludeObjectDialog( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );
	void executar();
	void on_btn_add_point_wire_clicked();
	void setObjectFile( ObjectFile * obf );
	void setWindow( Window2D * window );


};
#endif // INCLUDEOBJECTDIALOG_H
