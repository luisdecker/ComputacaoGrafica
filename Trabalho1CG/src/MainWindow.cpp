#include <iostream>
#include "MainWindow.hpp"
#include "window.h"


MainWindow::MainWindow( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
    Gtk::Window( cobject ), builder( refGlade ) {

    nroObjetos = 0;
    controller = new MainWindowController();

    builder->get_widget( "btn_include", btnInclude );
    builder->get_widget( "btn_transf", btnTransf );
    builder->get_widget( "btn_in", btnIn );
    builder->get_widget( "btn_out", btnOut );
    builder->get_widget( "btn_up", btnUp );
    builder->get_widget( "btn_down", btnDown );
    builder->get_widget( "btn_left", btnLeft );
    builder->get_widget( "btn_right", btnRight );
    builder->get_widget( "list_obj", m_TreeView );

    btnTransf->set_sensitive(false);

    refTreeSelection = m_TreeView->get_selection();

    m_Columns = new ModelColumns();

    Gtk::TreeModelColumnRecord * tmcr = dynamic_cast<Gtk::TreeModelColumnRecord *>( m_Columns );

    m_refTreeModel = Gtk::ListStore::create( *tmcr );

    m_TreeView->set_model( m_refTreeModel );
    m_TreeView->append_column( "Nome", m_Columns->nameObj );
    m_TreeView->append_column( "Tipo", m_Columns->typeObj );

    btnInclude->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_include_clicked ) );
    btnIn->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_in_clicked ) );
    btnOut->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_out_clicked ) );
    btnUp->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_up_clicked ) );
    btnDown->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_down_clicked ) );
    btnLeft->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_left_clicked ) );
    btnRight->signal_clicked().connect( sigc::mem_fun( *this, &MainWindow::on_btn_right_clicked ) );
    refTreeSelection->signal_changed().connect(sigc::mem_fun( *this, &MainWindow::on_selection_obj_changed ) );
    btnTransf->signal_clicked().connect(sigc::mem_fun( *this, &MainWindow::on_btn_transf_activate ));
}

void MainWindow::update() {

    if(controller->obtemTamanhoObjectFile() > nroObjetos) {

        nroObjetos++;

        Objeto * ultimo = controller->obtemUltimoObjInserido();

        Gtk::TreeModel::Row row = *( m_refTreeModel->append() );
        row[m_Columns->nameObj] = ultimo->nome;

        switch(ultimo->tipoObjeto) {
        case 0: {
            row[m_Columns->typeObj] = "Ponto";
        }
        break;
        case 1: {
            row[m_Columns->typeObj] = "Reta";
        }
        break;
        case 2: {
            row[m_Columns->typeObj] = "Wireframe";
        }
        break;
        }
    }

}

void MainWindow::setObjectFile(ObjectFile * obf) {

    this->of = obf;
    controller->setObjectFile(obf);

    of->subscribe(this);

}

void MainWindow::setIncludeObjectDialog(IncludeObjectDialog * includeObjDiag) {

    this->includeObjDiag = includeObjDiag;

}

void MainWindow::setDrawingArea(DrawingArea * drawingArea) {

    this->drawingArea = drawingArea;

}

void MainWindow::setTransformationDialog(TransformationDialog * transformationDialog) {

    this->transformationDialog = transformationDialog;

}

void MainWindow::setWindow(Window2D * window) {

    this->window = window;
    controller->setWindow(window);

}

void MainWindow::on_selection_obj_changed() {

    btnTransf->set_sensitive(true);

}

void MainWindow::on_btn_transf_activate() {

    Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
    if(iter) //If anything is selected
    {
        Gtk::TreeModel::Row row = *iter;

        std::string nomeObj = row->get_value(m_Columns->nameObj);
        transformationDialog->executar(nomeObj);

    }

}


void MainWindow::on_btn_include_clicked() {

    includeObjDiag->executar();

}

void MainWindow::on_btn_in_clicked() {

    controller->windowZoomIn();
}

void MainWindow::on_btn_down_clicked() {

    controller->windowDown();
}

void MainWindow::on_btn_left_clicked() {

    controller->windowLeft();
}

void MainWindow::on_btn_right_clicked() {

    controller->windowRight();

}
void MainWindow::on_btn_up_clicked() {

    controller->windowUp();
}

void MainWindow::on_btn_out_clicked() {

    controller->windowZoomOut();
}





















