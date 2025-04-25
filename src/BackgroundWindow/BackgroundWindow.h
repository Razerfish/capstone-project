#pragma once

#include <gtkmm.h>
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

    VLCWidget vlc;

    // Static helper functions.
    static std::tuple<int, int> get_resolution(Glib::RefPtr<const Gdk::Display> display);
};
