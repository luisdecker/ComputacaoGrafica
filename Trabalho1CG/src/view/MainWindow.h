#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include "IncludeObjectDialog.hpp"

class MainWindow : public Gtk::Window
{

protected:
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Button *btnInclude;
    IncludeObjectDialog *includeObjDiag;

public:

    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    void on_btn_include_clicked();

};
#endif // MAINWINDOW_H