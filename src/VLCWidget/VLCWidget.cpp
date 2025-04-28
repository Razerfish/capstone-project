#include "VLCWidget.h"
#include "vlc_args.h"

VLCWidget::VLCWidget() : Gtk::DrawingArea()
{
    bound = false;
    media_path = "";
    volume = 0.0;

    instance = libvlc_new(VLC_ARG_COUNT, VLC_ARGS);
    player = libvlc_media_player_new(instance);
}

VLCWidget::~VLCWidget()
{
    libvlc_media_player_release(player);
    libvlc_release(instance);
}

void VLCWidget::play()
{
    libvlc_media_player_play(player);
}

void VLCWidget::set_media_from_path(std::string path)
{
    libvlc_media_t* media = libvlc_media_new_path(instance, path.c_str());

    // Ensure that media loaded successfully.
    if (!media)
    {
        throw std::runtime_error("Unable to initialize media from path, are you sure your path is correct?");
    }
    else
    {
        media_path = path;
        bool was_playing = libvlc_media_player_is_playing(player);

        libvlc_media_player_stop(player);
        libvlc_media_player_set_media(player, media);
        libvlc_media_player_set_position(player, 0.0);

        if (was_playing)
            libvlc_media_player_play(player);
        
        libvlc_media_release(media);
    }
}

std::string VLCWidget::get_media_path()
{
    return media_path;
}

void VLCWidget::stop()
{
    libvlc_media_player_stop(player);
}

void VLCWidget::pause()
{
    libvlc_media_player_pause(player);
}

void VLCWidget::unpause()
{
    libvlc_media_player_set_pause(player, 0);
}

void VLCWidget::toggle_pause()
{
    if (libvlc_media_player_is_playing(player))
    {
        pause();
    }
    else
    {
        unpause();
    }
}

bool VLCWidget::is_playing()
{
    return libvlc_media_player_is_playing(player);
}

double VLCWidget::get_volume()
{
    int i_volume = libvlc_audio_get_volume(player);
    return (double)(i_volume / 100.0);
}

bool VLCWidget::set_volume(double volume)
{
    this->volume = volume;
    int i_volume = (int)(volume * 100);

    if (libvlc_audio_set_volume(player, i_volume) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VLCWidget::is_bound()
{
    return bound;
}

void VLCWidget::bind_window(XID xid)
{
    libvlc_media_player_set_xwindow(player, xid);
    libvlc_video_set_scale(player, 0);
    bound = true;
}

void VLCWidget::unbind_window()
{
    libvlc_media_player_stop(player);
    libvlc_media_player_set_xwindow(player, 0);
    bound = false;
}

// Rebind window on redraw to prevent flickering.
bool VLCWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &ctr)
{
    if (bound)
    {
        XID xid = gdk_x11_window_get_xid(get_window()->gobj());
        libvlc_media_player_set_xwindow(player, xid);
    }

    return true;
}
