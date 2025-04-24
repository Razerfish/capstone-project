#pragma once

#include <gtkmm.h>
#include <gdk/gdkx.h>
// TODO: Decide if we need string or not.
#include <string>
#include <vlcpp/vlc.hpp>

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
    bool is_playing;

    VLC::Instance instance;
    VLC::Media media;
    VLC::MediaPlayer player;

    // CALLBACKS
    sigc::slot<bool> replay_slot;
    sigc::connection replay_timer;
    
    void enable_replay();
    void cancel_replay();
    bool replay_callback();

    // OVERRIDES
    //void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
    //void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;

    //void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const override;
    //void get_preferred_width_for_height_vfunc(int height, int& mimimum_width, int& natural_width) const override;

    //void on_size_allocate(Gtk::Allocation& allocation) override;

    //void on_map() override;
    //void on_unmap() override;

    //void on_realize() override;
    //void on_unrealize() override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctr) override;

public:
    bool play(bool replay);
    bool bind_window();
};
