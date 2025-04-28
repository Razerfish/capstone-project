#pragma once

#include <gtkmm/application.h>
#include <glibmm-2.4/glibmm.h>
#include <gtkmm/filechooserbutton.h>

#include <string>
#include <sigc++/sigc++.h>

class BackgroundWindow;
class VLCWidget;
class ControlWindow;

class Application : public sigc::trackable
{
public:
    Application(int argc, char *argv[], std::string identifier);
    virtual ~Application();

protected:
    double stored_volume;

    Glib::RefPtr<Gtk::Application> app;
    BackgroundWindow* background;
    VLCWidget* player;
    ControlWindow* controller;

    // Signal handlers.
    sigc::slot<void, std::string> media_set_slot = sigc::mem_fun(*this, &Application::set_media);
    sigc::slot<void, double> volume_set_slot = sigc::mem_fun(*this, &Application::set_volume);
    sigc::slot<void, bool> mute_state_slot = sigc::mem_fun(*this, &Application::set_mute);
    sigc::slot<void> play_state_slot = sigc::mem_fun(*this, &Application::toggle_play);

    // Callbacks
    void set_media(std::string media_path);
    void set_volume(double volume);
    void set_mute(bool state);
    void toggle_play();

public:
    int run();
};
