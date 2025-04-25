#include "BackgroundWindow.h"

BackgroundWindow::BackgroundWindow(std::string path)
{
    std::tuple<int, int> resolution = BackgroundWindow::get_resolution(get_display());

    this->height = std::get<0>(resolution);
    this->width = std::get<1>(resolution);

    vlc = new VLCWidget(path);

    // Set our ideal size, add and show the vlc widget and set our type hint so we show up properly.
    set_default_size(width, height);
    add(*vlc);
    show_all_children();
    set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);

    // Register a callback to wait a bit and check if we're ready to bind VLC.
    check_ready_callback = Glib::signal_timeout().connect(check_ready_slot, 10);
}

BackgroundWindow::~BackgroundWindow()
{
    check_ready_callback.disconnect();
    delete vlc;
}

bool BackgroundWindow::check_ready()
{
    Glib::RefPtr<Gdk::Window> window = get_window();

    // Once we get a window bind vlc to it.
    if (window)
    {
        XID win_id = gdk_x11_window_get_xid(window->gobj());
        vlc->bind_window(win_id);
        vlc->play();
        return false; // Don't run this callback again.
    }
    return true; // Check again later.
}

std::tuple<int, int> BackgroundWindow::get_resolution(Glib::RefPtr<const Gdk::Display> display)
{
    // TODO: Implement checking for null.
    Glib::RefPtr<const Gdk::Monitor> monitor = display->get_primary_monitor();
    int scale = monitor->get_scale_factor();

    Gdk::Rectangle geometry;
    monitor->get_geometry(geometry);

    return std::tuple<int, int>(geometry.get_height() * scale, geometry.get_width() * scale);
}
