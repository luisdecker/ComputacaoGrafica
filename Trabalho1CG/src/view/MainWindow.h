#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include "IncludeObjectDialog.hpp"

class MainWindow : public Gtk::Window
{

protected:

    Glib::RefPtr<Gtk::Builder> builder;
    IncludeObjectDialog *includeObjDiag;
    Gtk::Button *btnInclude;
    Gtk::Button *btnIn;
    Gtk::Button *btnOut;

public:

    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    void on_btn_include_clicked();
    void on_btn_in_clicked();
    void on_btn_out_clicked();

};
#endif // MAINWINDOW_H