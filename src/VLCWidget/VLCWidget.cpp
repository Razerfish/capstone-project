#include "VLCWidget.h"

VLCWidget::VLCWidget(std::string path, int width, int height) : Gtk::DrawingArea()
{
    this->height = height;
    this->width = width;

    const char* args[] = {"--input-repeat=65545", "--no-disable-screensaver"};
    instance = libvlc_new(2, args);
    media = libvlc_media_new_path(instance, path.c_str());
    player = libvlc_media_player_new_from_media(media);
}

VLCWidget::~VLCWidget()
{
    libvlc_media_release(media);
    libvlc_media_player_release(player);
    libvlc_release(instance);
}

/*
void VLCWidget::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const
{
    minimum_width = width;
    natural_width = width;
}

void VLCWidget::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const
{
    minimum_height = height;
    natural_height = height;
}
*/

/*
void VLCWidget::on_realize()
{
    std::cout << "Window xid: " << gdk_x11_window_get_xid(this->get_window().get()->gobj());
}
*/

/*
void VLCWidget::on_unrealize()
{
    player.setXwindow(0);
}
*/

bool VLCWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &ctr)
{
    auto window = this->get_window();
    auto xid = gdk_x11_window_get_xid(window.get()->gobj());
    std::cout << "Window xid: " << xid << std::endl;
    libvlc_media_player_set_xwindow(player, xid);
    libvlc_video_set_scale(player, 0);
    return true;
}

bool VLCWidget::play()
{
    libvlc_media_player_play(player);
    return libvlc_media_player_is_playing(player);
}
