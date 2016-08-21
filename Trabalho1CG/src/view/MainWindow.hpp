#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/widget.h>
#include "IncludeObjectDialog.hpp"
#include "../objeto.h"
#include <cairomm/context.h>
#include "../objectfile.h"
#include <math.h>
#include "ModelColumns.cpp"
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/container.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include "DrawingArea.hpp"

class MainWindow : public Gtk::Window {

protected:

	Glib::RefPtr<Gtk::Builder> builder;
	IncludeObjectDialog * includeObjDiag;
	DrawingArea * drawingArea;
	Gtk::Button * btnInclude;
	Gtk::Button * btnIn;
	Gtk::Button * btnOut;
	Gtk::Button * btnUp;
	Gtk::Button * btnDown;
	Gtk::Button * btnLeft;
	Gtk::Button * btnRight;


	Gtk::DrawingArea * papel;
	ObjectFile * of;
	Cairo::RefPtr<Cairo::Context> cr;
	ModelColumns * m_Columns;
	Gtk::TreeView * m_TreeView;
	Glib::RefPtr<Gtk::ListStore>  m_refTreeModel;

	Window2D * windowPrincipal;



public:


	MainWindow( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );

	void on_btn_include_clicked();
	void on_btn_in_clicked();
	void on_btn_out_clicked();
	void on_btn_up_clicked();
	void on_btn_down_clicked();
	void on_btn_left_clicked();
	void on_btn_right_clicked();

//	bool drawObject( GtkWidget * widget );
	void atualizaObjectFile( ObjectFile * newOf );
	void atualizaWindow( Window2D * window );

};
#endif // MAINWINDOW_H