#pragma once

#include <gtkmm.h>
#include <gdk/gdkx.h>
// TODO: Decide if we need string or not.
#include <string>
#include <vlc/vlc.h>

#include <iostream>

class VLCWidget : public Gtk::DrawingArea
{
public:
    VLCWidget(std::string path, int height, int width);
    virtual ~VLCWidget();

protected:
    int
        height,
        width;

    libvlc_instance_t* instance;
    libvlc_media_t* media;
    libvlc_media_player_t* player;
    
    // OVERRIDES
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctr) override;

public:
    bool play();
    bool bind_window();
};
