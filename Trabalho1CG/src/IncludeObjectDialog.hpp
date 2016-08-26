#ifndef INCLUDEOBJECTDIALOG_H
#define INCLUDEOBJECTDIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/notebook.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include "objectfile.h"
#include "IncludeObjectController.hpp"



class IncludeObjectDialog : public Gtk::Dialog {

    void incluirObjeto();

    IncludeObjectController *controller;

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

public:

    IncludeObjectDialog( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );
    void executar();
    void on_btn_add_point_wire_clicked();
    void setObjectFile(ObjectFile *obf);


};
#endif // INCLUDEOBJECTDIALOG_H
