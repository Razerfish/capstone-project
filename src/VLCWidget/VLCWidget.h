#pragma once

#include <gtkmm/drawingarea.h>
#include <gdk/gdkx.h>
#include <string>
#include <vlc/vlc.h>

#include <iostream>

class VLCWidget : public Gtk::DrawingArea
{
public:
    VLCWidget();
    virtual ~VLCWidget();

protected:    
    bool bound;
    double volume;

    std::string media_path;

    libvlc_instance_t* instance;
    libvlc_media_player_t* player;

public:
    void play();

    void set_media_from_path(std::string path);
    std::string get_media_path();

    void stop();
    void pause();
    void unpause();
    void toggle_pause();
    bool is_playing();

    double get_volume();
    bool set_volume(double volume);

    bool is_bound();
    void bind_window(XID xid);
    void unbind_window();

protected:
    // Signal handler overrides.
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &ctr) override;
};
