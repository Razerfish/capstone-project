#pragma once

#include <gtkmm/drawingarea.h>
#include <gdk/gdkx.h>
// TODO: Decide if we need string or not.
#include <string>
#include <vlc/vlc.h>

#include <iostream>

class VLCWidget : public Gtk::DrawingArea
{
public:
    VLCWidget();
    virtual ~VLCWidget();

protected:
    int
        height,
        width;

    libvlc_instance_t* instance;
    libvlc_media_player_t* player;

public:
    void set_media(std::string path);

    bool play();
    void stop();
    void pause();
    void unpause();
    void toggle_pause();
    bool is_playing();

    double get_volume();
    void set_volume(double volume);

    bool is_muted();
    void mute();
    void unmute();
    void toggle_mute();

    void bind_window(XID xid);
};
