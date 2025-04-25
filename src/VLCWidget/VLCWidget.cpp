#include "VLCWidget.h"

VLCWidget::VLCWidget(std::string path) : Gtk::DrawingArea()
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

bool VLCWidget::play()
{
    libvlc_media_player_play(player);
    return libvlc_media_player_is_playing(player);
}

void VLCWidget::bind_window(XID xid)
{
    libvlc_media_player_set_xwindow(player, xid);
    libvlc_video_set_scale(player, 0);
}
