#include "ControlWindow.h"
#include "Application.h"

ControlWindow::ControlWindow()
 : media_label("Select a video to start!"),
   media_selector("Select video", Gtk::FILE_CHOOSER_ACTION_OPEN),
   volume_label("Volume"),
   volume_slider(Gtk::ORIENTATION_HORIZONTAL),
   mute_button("Toggle Mute"),
   play_button("Play/Pause")
{
    set_title("Zoetrope");
    set_border_width(10);
    add(box);

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
    
}
