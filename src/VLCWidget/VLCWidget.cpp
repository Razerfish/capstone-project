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
    // Cleanup mute_when_ready_workaround callback in case it never fired.
    libvlc_event_detach(
        libvlc_media_player_event_manager(player),
        libvlc_MediaPlayerPlaying,
        VLCWidget::mute_when_ready_workaround,
        nullptr
    );

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

    // Apply mute workaround.
    int bind_result = libvlc_event_attach(
        libvlc_media_player_event_manager(player),
        libvlc_MediaPlayerPlaying,
        VLCWidget::mute_when_ready_workaround,
        player
    );

    if (bind_result == 0)
        std::cout << "Successfully bound mute_when_ready_workaround callback" << std::endl;
    else
        std::cout << "Failed to bind mute_when_ready_workaround callback" << std::endl;

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

// Volume related functions are currently very unreliable, USE AT YOUR OWN RISK.
int VLCWidget::get_volume()
{
    return libvlc_audio_get_volume(player);
}

bool VLCWidget::set_volume(int volume)
{
    auto tracks = libvlc_audio_get_track_description(player);

    if (libvlc_audio_set_volume(player, volume) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
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

void VLCWidget::mute_when_ready_workaround(const struct libvlc_event_t* event, void* p_player)
{
    libvlc_media_player_t* player = static_cast<libvlc_media_player_t*>(p_player);
    if (libvlc_audio_set_volume(player, 0) == 0)
        std::cout << "Workaround volume set successfully" << std::endl;
    else
        std::cout << "Failed to set volume in workaround" << std::endl;
}
