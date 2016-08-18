#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/widget.h>
#include "IncludeObjectDialog.cpp"
#include "../objeto.cpp"
#include <cairomm/context.h>
#include "../objectfile.cpp"
#include <math.h>
#include "ModelColumns.cpp"
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <glibmm/refptr.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include "DrawingArea.cpp"


class MainWindow : public Gtk::Window {

protected:

	Glib::RefPtr<Gtk::Builder> builder;
	IncludeObjectDialog * includeObjDiag;
	DrawingArea * drawingArea;
	Gtk::Button * btnInclude;
	Gtk::Button * btnIn;
	Gtk::Button * btnOut;
	Gtk::DrawingArea * papel;
	ObjectFile * of;
	Cairo::RefPtr<Cairo::Context> cr;
	ModelColumns * m_Columns;
	Gtk::TreeView * m_TreeView;
	Glib::RefPtr<Gtk::ListStore>  m_refTreeModel;


public:

	MainWindow( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );
	void on_btn_include_clicked();
	void on_btn_in_clicked();
	void on_btn_out_clicked();
	bool drawObject( GtkWidget * widget );
	void atualizaObjectFile( ObjectFile * newOf );
};
#endif // MAINWINDOW_H