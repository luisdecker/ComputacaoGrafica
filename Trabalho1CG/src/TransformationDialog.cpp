#include "TransformationDialog.hpp"

TransformationDialog::TransformationDialog( BaseObjectType * cobject, const Glib::RefPtr<Gtk::Builder> & refGlade ) :
    Gtk::Dialog( cobject ), builder( refGlade ) {

    controller = new TransformationController();

    builder->get_widget("tabs_transf",tabs);
    builder->get_widget("x_transl",x_transl);
    builder->get_widget("y_transl",y_transl);
    builder->get_widget("x_escal",x_escal);
    builder->get_widget("y_escal",y_escal);
    builder->get_widget("x_rot",x_rot);
    builder->get_widget("y_rot",y_rot);
    builder->get_widget("rd_mundo",rd_mundo);
    builder->get_widget("rd_obj",rd_obj);
    builder->get_widget("rd_pto",rd_pto);
    builder->get_widget("entry_angulo",entry_angulo);

}

void TransformationDialog::executar(std::string nomeObj) {

    int result = run();

    switch( result ) {
    case Gtk::RESPONSE_OK: {

        aplicarTransformacao(nomeObj);
        close();

    }
    break;

    case Gtk::RESPONSE_CANCEL: {

        close();
    }

    break;
    }
}

void TransformationDialog::setObjectFile(ObjectFile * obf) {

    this->obf = obf;
    controller->setObjectFile(obf);

}

void TransformationDialog::aplicarTransformacao(std::string objName) {

    int tabNum = tabs->get_current_page();

    switch( tabNum ) {

    //case 0: ponto
    case 0: {

        if( x_transl->get_text().size() > 0 && y_transl->get_text().size() > 0 ) {

            double x, y;

            x = stod( x_transl->get_text() );
            y = stod( y_transl->get_text() );

            controller->aplicarTranslacao(objName,x,y);

        }

        x_transl->set_text("");
        y_transl->set_text("");

        break;
    }

    //case 1: reta
    case 1: {

        if( x_escal->get_text().size() > 0 && y_escal->get_text().size() > 0) {

            double x, y;

            x = stod( x_escal->get_text() );
            y = stod( y_escal->get_text() );

            controller->aplicarEscalonamento(objName,x,y);

        }

        x_escal->set_text("");
        y_escal->set_text("");

        break;
    }

    case 2: {

        double angulo;

        if( entry_angulo->get_text().size() > 0) {

            angulo = stod( entry_angulo->get_text() );

            if(rd_mundo->get_active()) {

                controller->aplicarRotacaoCentroMundo(objName, angulo);


            } else if(rd_obj->get_active()) {

                controller->aplicarRotacaoCentroObjeto(objName, angulo);

            } else {

                if( x_rot->get_text().size() > 0 && y_rot->get_text().size() > 0) {

                    double x,y;

                    x = stod( x_rot->get_text() );
                    y = stod( y_rot->get_text() );

                    controller->aplicarRotacaoPontoArbitrario(objName, angulo, x, y);

                }

                x_rot->set_text("");
                y_rot->set_text("");


            }

        }

        entry_angulo->set_text("");

        break;

    }


    }
}