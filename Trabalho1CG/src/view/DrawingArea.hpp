#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <gtkmm/drawingarea.h>

class DrawingArea : public Gtk::DrawingArea
{
public:

  DrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~DrawingArea();

protected:
  //Override default signal handler:
	Glib::RefPtr<Gtk::Builder> builder;
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif