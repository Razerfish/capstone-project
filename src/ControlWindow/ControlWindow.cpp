#include "ControlWindow.h"

ControlWindow::ControlWindow()
 : media_label("Select a video to start!"),
   media_selector("Select video"),
   volume_label("Volume"),
   volume_adjuster(Gtk::Adjustment::create(0.0, 0.0, 100.0, 1.0)),
   volume_slider(volume_adjuster, Gtk::ORIENTATION_HORIZONTAL),
   mute_button("Toggle Mute"),
   play_button("Play/Pause")
{
    set_title("Zoetrope");
    set_border_width(10);
    add(box);

    media_selector.signal_clicked().connect(media_selector_slot);

    volume_slider.set_digits(1);
    volume_slider.signal_change_value().connect(volume_slider_slot);

    mute_button.signal_clicked().connect(mute_button_slot);

    play_button.signal_clicked().connect(play_button_slot);

    box.pack_start(media_label);
    box.pack_start(media_selector);

    box.pack_start(volume_label);
    box.pack_start(volume_slider);
    
    box.pack_start(mute_button);
    box.pack_start(play_button);

    box.show_all();
}

ControlWindow::~ControlWindow()
{
    media_selector_slot.disconnect();
    volume_slider_slot.disconnect();
    mute_button_slot.disconnect();
    play_button_slot.disconnect();
}

void ControlWindow::emit_signal_file_selected(std::string file)
{
    m_signal_file_selected.emit(file);
}

void ControlWindow::emit_signal_volume_set(double volume)
{
    m_signal_volume_set.emit(volume);
}

void ControlWindow::emit_signal_mute_state_changed(bool mute_state)
{
    m_signal_mute_state_changed.emit(mute_state);
}

void ControlWindow::emit_signal_play_state_changed()
{
    m_play_state_changed.emit();
}

void ControlWindow::on_file_selector_clicked()
{
    // Adapted from the example on page 248 of Programming with gtkmm3.
    Gtk::FileChooserDialog dialog = Gtk::FileChooserDialog("Please select a video to play",
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    std::cout << "User selecting file" << std::endl;
    int result = dialog.run();

    switch (result)
    {
        case (Gtk::RESPONSE_OK):
        {
            std::string file = dialog.get_filename();
            std::cout << "Selected file: " << file << std::endl;
            emit_signal_file_selected(file);
            break;
        }
        case (Gtk::RESPONSE_CANCEL):
        {
            std::cout << "File selection cancelled" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Unexpected input" << std::endl;
            break;
        }
    }
}

bool ControlWindow::on_volume_slider_changed(Gtk::ScrollType scrolltype, double value)
{
    if (scrolltype == Gtk::ScrollType::SCROLL_NONE)
    {
        return true;
    }
    
    if (value > 100.0)
    {
        value = 100.0;
    }

    if (value < 0.0)
    {
        value = 0.0;
    }

    std::cout << "Volume set to: " << value << std::endl;
    emit_signal_volume_set(value);
    return false;
}

void ControlWindow::on_mute_state_changed()
{
    bool state = mute_button.get_active();
    if (state)
    {
        std::cout << "Muted" << std::endl;
    }
    else
    {
        std::cout << "Unmuted" << std::endl;
    }

    emit_signal_mute_state_changed(state);
}

void ControlWindow::on_play_state_changed()
{
    std::cout << "Play state changed" << std::endl;
    emit_signal_play_state_changed();
}

sigc::signal<void, std::string> ControlWindow::signal_file_selected()
{
    return m_signal_file_selected;
}

sigc::signal<void, double> ControlWindow::signal_volume_set()
{
    return m_signal_volume_set;
}

sigc::signal<void, bool> ControlWindow::signal_mute_state_changed()
{
    return m_signal_mute_state_changed;
}

sigc::signal<void> ControlWindow::signal_play_state_changed()
{
    return m_play_state_changed;
}
