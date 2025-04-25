#include "BackgroundWindow.h"

BackgroundWindow::BackgroundWindow(std::string path) : vlc(path, 0, 0)
{
    std::tuple<int, int> resolution = BackgroundWindow::get_resolution(get_display());

    this->height = std::get<0>(resolution);
    this->width = std::get<1>(resolution);

    set_default_size(width, height);
    add(vlc);
    show_all_children();
    set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);

    vlc.play();
}

BackgroundWindow::~BackgroundWindow()
{

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
