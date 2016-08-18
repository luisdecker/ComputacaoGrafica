#include "DrawingArea.hpp"
#include <cairomm/context.h>

DrawingArea::DrawingArea(BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
  Gtk::DrawingArea( cobject ), builder( refGlade )
{
}

DrawingArea::~DrawingArea()
{
}

bool DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  cr->set_line_width(2.0);

  // draw red lines out from the center of the window
  cr->set_source_rgb(0.0, 0.0, 0.0);
  cr->move_to(0, 0);
  cr->line_to(xc, yc);
  cr->line_to(0, height);
  cr->move_to(xc, yc);
  cr->line_to(width, yc);
  cr->stroke();

  return true;
}