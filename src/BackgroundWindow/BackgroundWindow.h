#pragma once

#include <gtkmm/applicationwindow.h>
#include <glibmm-2.4/glibmm.h>
#include <gdkmm-3.0/gdkmm/monitor.h>
#include <gdk/gdkx.h>

#include <string>

class VLCWidget;

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

    sigc::slot<bool> bind_when_ready_slot = sigc::mem_fun(*this, &BackgroundWindow::bind_when_ready_callback);
    sigc::connection bind_when_ready_conn;

    // Callbacks
    bool bind_if_ready();
    bool bind_when_ready_callback();

    // Static helper functions.
    static void get_resolution(Glib::RefPtr<const Gdk::Display> display, int& height, int& width);

public:
    void bind_when_ready();
};
