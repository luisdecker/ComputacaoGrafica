#ifndef INCLUDEOBJECTDIALOG_H
#define INCLUDEOBJECTDIALOG_H

#include <gtkmm/dialog.h>

class IncludeObjectDialog : public Gtk::Dialog
{

protected:
    Glib::RefPtr<Gtk::Builder> builder;


public:

    IncludeObjectDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);


};
#endif // INCLUDEOBJECTDIALOG_H