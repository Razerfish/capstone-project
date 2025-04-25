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
    //void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
    //void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;

    //void on_size_allocate(Gtk::Allocation& allocation) override;

    //void on_map() override;
    //void on_unmap() override;

    //void on_realize() override;
    //void on_unrealize() override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctr) override;

public:
    bool play();
    bool bind_window();
};
