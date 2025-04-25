#include "VLCWidget.h"
#include "vlc_args.h"

VLCWidget::VLCWidget() : Gtk::DrawingArea()
{
    this->height = height;
    this->width = width;

    instance = libvlc_new(VLC_ARG_COUNT, VLC_ARGS);
    player = libvlc_media_player_new(instance);
}

VLCWidget::~VLCWidget()
{
    libvlc_media_player_release(player);
    libvlc_release(instance);
}

void VLCWidget::set_media(std::string path)
{
    libvlc_media_t* media = libvlc_media_new_path(instance, path.c_str());

    // Ensure that media loaded successfully.
    if (!media)
    {
        throw std::runtime_error("Unable to initialize media from path, are you sure your path is correct?");
    }
    else
    {
        bool was_playing = libvlc_media_player_is_playing(player);

        libvlc_media_player_stop(player);
        libvlc_media_player_set_media(player, media);
        libvlc_media_player_set_position(player, 0.0);

        if (was_playing)
            libvlc_media_player_play(player);
        
        libvlc_media_release(media);
    }
}

bool VLCWidget::play()
{
    libvlc_media_player_play(player);
    return libvlc_media_player_is_playing(player);
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
    int vol_int = libvlc_audio_get_volume(player);

    return double(vol_int) / 100.0;
}

void VLCWidget::set_volume(double volume)
{
    int vol_int = int(std::round(volume * 100));
    libvlc_audio_set_volume(player, vol_int);
}

bool VLCWidget::is_muted()
{
    if (libvlc_audio_get_mute(player) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void VLCWidget::mute()
{
    libvlc_audio_set_mute(player, true);
}

void VLCWidget::unmute()
{
    libvlc_audio_set_mute(player, false);
}

void VLCWidget::toggle_mute()
{
    if (is_muted())
    {
        unmute();
    }
    else
    {
        mute();
    }
}

void VLCWidget::bind_window(XID xid)
{
    libvlc_media_player_set_xwindow(player, xid);
    libvlc_video_set_scale(player, 0);
}
