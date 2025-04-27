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
    BackgroundWindow(VLCWidget* player);
    virtual ~BackgroundWindow();

protected:
    int
        height,
        width;

    VLCWidget* player;

    sigc::slot<bool> check_ready_slot = sigc::mem_fun(*this, &BackgroundWindow::check_ready_callback);
    sigc::slot<void> swap_media_slot;
    
    sigc::connection check_ready_conn;

    // Callbacks
    bool check_ready();
    bool check_ready_callback();
    void swap_media(std::string path);

    // Static helper functions.
    static void get_resolution(Glib::RefPtr<const Gdk::Display> display, int& height, int& width);

public:
    void bind_when_ready();
};
