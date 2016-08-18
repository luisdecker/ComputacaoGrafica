#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <gtkmm/drawingarea.h>
#include "../objectfile.h"
#include "../window.h"
#include "../viewport.cpp"

class DrawingArea : public Gtk::DrawingArea {
public:

	DrawingArea( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );
	virtual ~DrawingArea();
	void atualizaObjectFile( ObjectFile * of );
	void atualizaWindow( Window2D * window );


protected:
	//Override default signal handler:
	Glib::RefPtr<Gtk::Builder> builder;
	bool on_draw( const Cairo::RefPtr<Cairo::Context> & cr ) override;
	ObjectFile * mainOf;
	Window2D * mainWindow;
	ViewPort * viewPort;

};

#endif