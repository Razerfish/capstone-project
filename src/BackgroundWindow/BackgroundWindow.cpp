#include "BackgroundWindow.h"

// BackgroundWindow DOES NOT take ownership of player, you need to deallocate it yourself.
BackgroundWindow::BackgroundWindow(VLCWidget* player)
{
    BackgroundWindow::get_resolution(get_display(), height, width);

    // Check that we were able to actually get the resolution.
    if (height == -1 || width == -1)
    {
        throw std::runtime_error("Unable to get primary monitor resolution");
    }

    this->player = player;

    // Set our ideal size, add and show the vlc widget and set our type hint so we show up properly.
    set_default_size(width, height);
    add(*player);
    show_all_children();
    set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);
}

BackgroundWindow::~BackgroundWindow()
{
    swap_media_slot.disconnect();
    bind_when_ready_conn.disconnect();
    player->unbind_window();
}

bool BackgroundWindow::bind_if_ready()
{
    Glib::RefPtr<Gdk::Window> window = get_window();

    // Only bind if we actually have a window.
    if (window)
    {
        XID win_id = gdk_x11_window_get_xid(window->gobj());
        player->bind_window(win_id);

        return true; // Binding successful.
    }

    return false; // Binding unsuccessful.
}

bool BackgroundWindow::bind_when_ready_callback()
{
    /*
    Callback version of check_ready, returns false if binding was successful
    to indicate that the callback should not be repeated.
    */
    return !(bind_if_ready());
}

void BackgroundWindow::swap_media(std::string path)
{
    std::cout << "Swapping media" << std::endl;
    player->set_media_from_path(path);
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

void BackgroundWindow::bind_when_ready()
{
    if (!bind_if_ready())
    {
        // Register a callback to wait a bit and try again.
        bind_when_ready_conn = Glib::signal_timeout().connect(bind_when_ready_slot, 10);
    }
}
