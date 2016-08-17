#include "MainWindow.h"


MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Window(cobject), builder(refGlade) {

    includeObjDiag = nullptr;

    builder->get_widget("btn_include",btnInclude);
    builder->get_widget_derived("diag_incl_obj",includeObjDiag);


    btnInclude->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_btn_include_clicked));
}

void MainWindow::on_btn_include_clicked() {

    includeObjDiag->run();

}