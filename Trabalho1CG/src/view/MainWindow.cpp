#include <iostream>
#include "MainWindow.hpp"


MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject), builder(refGlade) {

    includeObjDiag = nullptr;

    builder->get_widget("btn_include",btnInclude);
    builder->get_widget("btn_in",btnIn);
    builder->get_widget("btn_out",btnOut);
    builder->get_widget_derived("diag_incl_obj",includeObjDiag);


    btnInclude->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_btn_include_clicked));
    btnIn->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_btn_in_clicked));
    btnOut->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_btn_out_clicked));

}

void MainWindow::on_btn_include_clicked() {

    includeObjDiag->executar();

}

void MainWindow::on_btn_in_clicked(){

}

void MainWindow::on_btn_out_clicked(){
	
}