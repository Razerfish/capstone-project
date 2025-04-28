#include "ControlWindow.h"

ControlWindow::ControlWindow()
 : media_label("Select a video to start!"),
   media_selector("Select video"),
   play_button("Play/Pause")
{
    set_title("Zoetrope");
    set_border_width(10);
    add(box);

    media_selector.signal_clicked().connect(media_selector_slot);

    play_button.signal_clicked().connect(play_button_slot);

    box.pack_start(media_label);
    box.pack_start(media_selector);

    box.pack_start(play_button);

    box.show_all();
}

ControlWindow::~ControlWindow()
{
    media_selector_slot.disconnect();
    play_button_slot.disconnect();
}

void ControlWindow::emit_signal_file_selected(std::string file)
{
    m_signal_file_selected.emit(file);
}

void ControlWindow::emit_signal_play_state_changed()
{
    m_play_state_changed.emit();
}

bool ControlWindow::on_delete_event(GdkEventAny *any_event)
{
    std::cout << "Exiting" << std::endl;
    get_application()->quit();
    return false;
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

void ControlWindow::on_play_state_changed()
{
    std::cout << "Play state changed" << std::endl;
    emit_signal_play_state_changed();
}

sigc::signal<void, std::string> ControlWindow::signal_file_selected()
{
    return m_signal_file_selected;
}

sigc::signal<void> ControlWindow::signal_play_state_changed()
{
    return m_play_state_changed;
}
