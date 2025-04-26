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

    std::string media_path;

    libvlc_instance_t* instance;
    libvlc_media_player_t* player;

public:
    bool play();

    void set_media_from_path(std::string path);
    std::string get_media_path();

    void stop();
    void pause();
    void unpause();
    void toggle_pause();
    bool is_playing();

    // Volume functions currently broken.
    // This is probably due to the player needing to initialize fully before volume can be adjusted.
    // This would be resolved best by implementing a robust callback system for handling events like this,
    // so do that when you get the chance.
    int get_volume();
    bool set_volume(int volume);

    bool is_muted();
    void mute();
    void unmute();
    void toggle_mute();

    void bind_window(XID xid);

private:
    // Mute workaround callback.
    // p_player should point to the player.
    static void mute_when_ready_workaround(const struct libvlc_event_t* event, void* p_player);
};
