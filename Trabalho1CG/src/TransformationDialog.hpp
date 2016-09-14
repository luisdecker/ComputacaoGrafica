#ifndef TRANSFORMATIONDIALOG_H
#define TRANSFORMATIONDIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/notebook.h>
#include <gtkmm/entry.h>
#include "objectfile.h"
#include <string>
#include <gtkmm/builder.h>
#include <gtkmm/radiobutton.h>
#include <iostream>
#include "TransformationController.hpp"


using namespace std;

class TransformationDialog: public Gtk::Dialog {

    void aplicarTransformacao(std::string objName);
    TransformationController * controller;

protected:
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Notebook * tabs;
    Gtk::Entry * x_transl;
    Gtk::Entry * y_transl;
    Gtk::Entry * x_escal;
    Gtk::Entry * y_escal;
    Gtk::Entry * x_rot;
    Gtk::Entry *y_rot;
    Gtk::Entry * entry_angulo;
    Gtk::RadioButton *rd_mundo;
    Gtk::RadioButton *rd_obj;
    Gtk::RadioButton *rd_pto;
    ObjectFile * obf;

public:

    TransformationDialog( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );
    void executar(std::string nomeObj);
    void setObjectFile(ObjectFile *obf);

};

#endif