#pragma once

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/scale.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/filechooserdialog.h>
#include <glibmm-2.4/glibmm.h>

#include <iostream>
#include <sigc++/sigc++.h>
#include <string>

class Application;

class ControlWindow : public Gtk::ApplicationWindow
{
public:
    ControlWindow();
    virtual ~ControlWindow();

    typedef sigc::signal<void, std::string> type_signal_file_selected;
    typedef sigc::signal<void, double> type_signal_volume_set;
    typedef sigc::signal<void, bool> type_signal_mute_state_changed;
    typedef sigc::signal<void> type_signal_play_state_changed;

protected:
    Gtk::Box box;

    Gtk::Label media_label;
    Gtk::Button media_selector;

    Gtk::Label volume_label;
    Glib::RefPtr<Gtk::Adjustment> volume_adjuster;
    Gtk::Scale volume_slider;

    Gtk::ToggleButton mute_button;
    Gtk::Button play_button;

    // Signals
    sigc::signal<void, std::string> m_signal_file_selected;
    sigc::signal<void, double> m_signal_volume_set;
    sigc::signal<void, bool> m_signal_mute_state_changed;
    sigc::signal<void> m_play_state_changed;

    // Signal emitters.
    void emit_signal_file_selected(std::string file);
    void emit_signal_volume_set(double volume);
    void emit_signal_mute_state_changed(bool mute_state);
    void emit_signal_play_state_changed();

    // Signal handlers
    sigc::slot<void> media_selector_slot = sigc::mem_fun(*this, &ControlWindow::on_file_selector_clicked);
    sigc::slot<bool, Gtk::ScrollType, double> volume_slider_slot = sigc::mem_fun(*this, &ControlWindow::on_volume_slider_changed);
    sigc::slot<void> mute_button_slot = sigc::mem_fun(*this, &ControlWindow::on_mute_state_changed);
    sigc::slot<void> play_button_slot = sigc::mem_fun(*this, &ControlWindow::on_play_state_changed);

    // Signal adapters
    void on_file_selector_clicked();
    bool on_volume_slider_changed(Gtk::ScrollType scrolltype, double value);
    void on_mute_state_changed();
    void on_play_state_changed();

public:
    sigc::signal<void, std::string> signal_file_selected();
    sigc::signal<void, double> signal_volume_set();
    sigc::signal<void, bool> signal_mute_state_changed();
    sigc::signal<void> signal_play_state_changed();
};
