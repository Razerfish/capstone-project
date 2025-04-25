#pragma once

#include <gtkmm.h>
#include <gdk/gdkx.h>
#include <string>
#include <tuple>

#include "VLCWidget.h"

class BackgroundWindow : public Gtk::ApplicationWindow
{
public:
    BackgroundWindow(std::string path);
    virtual ~BackgroundWindow();

protected:
    int
        height,
        width;

    VLCWidget* vlc;

    sigc::slot<bool> check_ready_slot = sigc::mem_fun(*this, &BackgroundWindow::check_ready);
    sigc::connection check_ready_callback;

    // Callbacks
    bool check_ready();

    // Static helper functions.
    static std::tuple<int, int> get_resolution(Glib::RefPtr<const Gdk::Display> display);
};
