#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/widget.h>
#include "IncludeObjectDialog.hpp"
#include "objeto.h"
#include <cairomm/context.h>
#include "objectfile.h"
#include <math.h>
#include "ModelColumns.cpp"
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/container.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelcolumn.h>
#include "DrawingArea.hpp"
#include "Observer.hpp"
#include "MainWindowController.hpp"
#include <gtkmm/treemodel.h>
#include "TransformationDialog.hpp"
#include <cassert>
#include <iostream>


class MainWindow : public Gtk::Window, public Observer {

protected:

    Glib::RefPtr<Gtk::Builder> builder;
    IncludeObjectDialog * includeObjDiag;
    DrawingArea * drawingArea;
    TransformationDialog * transformationDialog;
    Gtk::Button * btnInclude;
    Gtk::Button * btnTransf;
    Gtk::Button * btnIn;
    Gtk::Button * btnOut;
    Gtk::Button * btnUp;
    Gtk::Button * btnDown;
    Gtk::Button * btnLeft;
    Gtk::Button * btnRight;
    Gtk::Button * btnHorario;
    Gtk::Button * btnAntiHorario;
    Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;

    ObjectFile * of;
    Cairo::RefPtr<Cairo::Context> cr;
    ModelColumns * m_Columns;
    Gtk::TreeView * m_TreeView;
    Glib::RefPtr<Gtk::ListStore>  m_refTreeModel;

    Window2D * window;

    int nroObjetos;

    MainWindowController *controller;

public:

    MainWindow( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade );

    void setObjectFile(ObjectFile * of);
    void setWindow(Window2D * window);
    void setDrawingArea(DrawingArea * drawingArea);
    void setTransformationDialog(TransformationDialog * transformationDialog);
    void setIncludeObjectDialog(IncludeObjectDialog * includeObjDiag);

    void on_btn_include_clicked();
    void on_btn_in_clicked();
    void on_btn_out_clicked();
    void on_btn_up_clicked();
    void on_btn_down_clicked();
    void on_btn_left_clicked();
    void on_btn_right_clicked();
    void on_selection_obj_changed();
    void on_btn_transf_activate();
    void on_btn_horario_clicked();
    void on_btn_ahorario_clicked();
    

    void update();

};
#endif // MAINWINDOW_H