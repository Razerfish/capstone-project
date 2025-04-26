#include "BackgroundWindow.h"

BackgroundWindow::BackgroundWindow(std::string path)
{
    BackgroundWindow::get_resolution(get_display(), height, width);

    // Check that we were able to actually get the resolution.
    if (height == -1 || width == -1)
    {
        throw std::runtime_error("Unable to get primary monitor resolution");
    }

    vlc = new VLCWidget();
    vlc->set_media_from_path(path);

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
    swap_media_slot.disconnect();
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

        //swap_media_slot = sigc::bind(sigc::mem_fun(*this, &BackgroundWindow::swap_media), "assets/short.mp4");
        //Glib::signal_timeout().connect_once(swap_media_slot, 5000);
        return false; // Don't run this callback again.
    }
    return true; // Check again later.
}

void BackgroundWindow::swap_media(std::string path)
{
    std::cout << "Swapping media" << std::endl;
    vlc->set_media_from_path(path);
}

void BackgroundWindow::get_resolution(Glib::RefPtr<const Gdk::Display> display, int& height, int& width)
{
    // Ensure that display is not null.
    if (display)
    {
        Glib::RefPtr<const Gdk::Monitor> monitor = display->get_primary_monitor();
        if (monitor)
        {
            int scale = monitor->get_scale_factor();

            Gdk::Rectangle geometry;
            monitor->get_geometry(geometry);

            height = geometry.get_height();
            width = geometry.get_width();
            return;
        }
    }

    // Unable to get monitor resolution.
    height = -1;
    width = -1;
    return;
}
