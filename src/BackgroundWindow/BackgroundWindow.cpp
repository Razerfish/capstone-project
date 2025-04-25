#include "BackgroundWindow.h"

BackgroundWindow::BackgroundWindow(std::string path, int width, int height) : vlc(path, height, width)
{
    set_default_size(width, height);
    add(vlc);
    show_all_children();
    set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);

    vlc.play();
}

BackgroundWindow::~BackgroundWindow()
{

}
