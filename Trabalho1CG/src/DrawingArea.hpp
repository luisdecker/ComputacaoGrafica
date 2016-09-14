#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <gtkmm/drawingarea.h>

#include "objectfile.h"
#include "window.h"
#include "viewport.h"
#include <gtkmm/builder.h>
#include "Observer.hpp"

class DrawingArea : public Gtk::DrawingArea, public Observer {
public:

    DrawingArea( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );
    virtual ~DrawingArea();
    void setObjectFile( ObjectFile * of );
    void setWindow( Window2D * window );
    void update();


protected:
    //Override default signal handler:
    Glib::RefPtr<Gtk::Builder> builder;
    bool on_draw( const Cairo::RefPtr<Cairo::Context> & cr ) override;
    ObjectFile * mainOf;
    Window2D * mainWindow;
    ViewPort * viewPort;


};

#endif