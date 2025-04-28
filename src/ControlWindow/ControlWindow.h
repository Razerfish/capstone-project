#pragma once

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
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
    typedef sigc::signal<void> type_signal_play_state_changed;

protected:
    Gtk::Box box;

    Gtk::Label media_label;
    Gtk::Button media_selector;

    Gtk::Button play_button;

    // Signals
    sigc::signal<void, std::string> m_signal_file_selected;
    sigc::signal<void> m_play_state_changed;

    // Signal emitters.
    void emit_signal_file_selected(std::string file);
    void emit_signal_play_state_changed();

    // Signal handlers
    sigc::slot<void> media_selector_slot = sigc::mem_fun(*this, &ControlWindow::on_file_selector_clicked);
    sigc::slot<void> play_button_slot = sigc::mem_fun(*this, &ControlWindow::on_play_state_changed);

    bool on_delete_event(GdkEventAny* any_event) override;

    // Signal adapters
    void on_file_selector_clicked();
    void on_play_state_changed();

public:
    sigc::signal<void, std::string> signal_file_selected();
    sigc::signal<void> signal_play_state_changed();
};
