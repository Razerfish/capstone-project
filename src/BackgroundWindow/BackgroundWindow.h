#pragma once

#include <gtkmm.h>
#include <string>

#include "VLCWidget.h"

class BackgroundWindow : public Gtk::ApplicationWindow
{
public:
    BackgroundWindow(std::string path, int width, int height);
    virtual ~BackgroundWindow();

protected:
    //Gtk::Image background_image;
    VLCWidget vlc;
};
