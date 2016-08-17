#include "IncludeObjectDialog.h"

#include <gtkmm/builder.h>

IncludeObjectDialog::IncludeObjectDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
    Gtk::Dialog(cobject), builder(refGlade) {


}

