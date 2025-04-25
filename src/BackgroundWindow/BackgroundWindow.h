#pragma once

#include <gtkmm/applicationwindow.h>
#include <glibmm-2.4/glibmm.h>
#include <gdkmm-3.0/gdkmm/monitor.h>
#include <gdk/gdkx.h>

#include <string>

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
    static void get_resolution(Glib::RefPtr<const Gdk::Display> display, int& height, int& width);
};
