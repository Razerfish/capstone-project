#include "BackgroundWindow.h"

BackgroundWindow::BackgroundWindow(std::string path, int width, int height) : vlc(path, height, width)
{
    /*
    set_default_size(width, height);
    background_image = Gtk::Image(path);
    add(background_image);
    */
    set_default_size(width, height);
    add(vlc);
    show_all_children();
    set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);

    vlc.play(true);
    //sigc::slot<bool> start_slot = sigc::mem_fun(*this, &BackgroundWindow::start_playback);
    //sigc::connection conn = Glib::signal_timeout().connect(start_slot, 1000);
}

BackgroundWindow::~BackgroundWindow()
{

}

bool BackgroundWindow::start_playback()
{
    if (vlc.bind_window())
        vlc.play(true);
    else
        std::cout << "Failed to bind VLC media player to X window" << std::endl;
    return false;
}
