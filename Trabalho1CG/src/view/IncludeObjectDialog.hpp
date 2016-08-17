#ifndef INCLUDEOBJECTDIALOG_H
#define INCLUDEOBJECTDIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/notebook.h>
#include <gtkmm/entry.h>

class IncludeObjectDialog : public Gtk::Dialog
{

	void incluirObjeto();

protected:
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Notebook *tabs;
    Gtk::Entry *in_name_obj;
    Gtk::Entry *x_point;
    Gtk::Entry *y_point;
    Gtk::Entry *x0_str_line;
    Gtk::Entry *y0_str_line;
    Gtk::Entry *x1_str_line;
    Gtk::Entry *y1_str_line;

public:

    IncludeObjectDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    void executar();


};
#endif // INCLUDEOBJECTDIALOG_H