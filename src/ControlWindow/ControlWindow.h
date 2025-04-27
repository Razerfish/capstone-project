#pragma once

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/scale.h>
#include <gtkmm/filechooserbutton.h>
#include <glibmm-2.4/glibmm.h>

#include <string>

class Application;

class ControlWindow : public Gtk::ApplicationWindow
{
public:
    ControlWindow();
    virtual ~ControlWindow();

protected:
    Gtk::Box box;

    Gtk::Label media_label;
    Gtk::FileChooserButton media_selector;

    Gtk::Label volume_label;
    Gtk::Scale volume_slider;

    Gtk::ToggleButton mute_button;
    Gtk::Button play_button;

    friend class Application;
};
