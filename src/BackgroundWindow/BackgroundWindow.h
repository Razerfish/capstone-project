#pragma once

#include <gtkmm.h>
#include <string>

class BackgroundWindow : public Gtk::Window
{
public:
    BackgroundWindow(std::string path, int width, int height);
    virtual ~BackgroundWindow();

protected:
    Gtk::Image background_image;
};
