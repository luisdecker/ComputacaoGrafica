#include <gtkmm/treemodelcolumn.h>

class ModelColumns : public Gtk::TreeModelColumnRecord {
public:

    ModelColumns()
    {
        add( nameObj );
        add( typeObj );
    }

    Gtk::TreeModelColumn<Glib::ustring> nameObj;
    Gtk::TreeModelColumn<Glib::ustring> typeObj;
};