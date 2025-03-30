#include "BackgroundWindow.h"

BackgroundWindow::BackgroundWindow(std::string path, int width, int height)
{
    set_default_size(width, height);
    background_image = Gtk::Image(path);
    add(background_image);
    show_all_children();
    set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);
}

BackgroundWindow::~BackgroundWindow()
{

}
