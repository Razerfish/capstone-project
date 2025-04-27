#pragma once

#include <gtkmm/application.h>
#include <glibmm-2.4/glibmm.h>

#include <string>

class BackgroundWindow;
class VLCWidget;
class ControlWindow;

class Application
{
public:
    Application(int argc, char *argv[], std::string identifier);
    ~Application();

protected:
    double stored_volume;

    Glib::RefPtr<Gtk::Application> app;
    BackgroundWindow* background;
    VLCWidget* player;
    ControlWindow* controller;

    

    // Callbacks
    void update_media(std::string path);
    void update_volume(double volume);
    void set_mute(bool state);
    void toggle_play();

public:
    int run();
};
