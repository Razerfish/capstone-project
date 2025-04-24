#include "VLCWidget.h"

VLCWidget::VLCWidget(std::string path, int width, int height) : Gtk::DrawingArea()
{
    this->height = height;
    this->width = width;
    this->is_playing = false;

    instance = VLC::Instance(0, nullptr);

#if LIBVLC_VERSION_INT >= LIBVLC_VERSION(4, 0, 0, 0)
    media = VLC::Media(path, VLC::Media::FromPath);
    player = VLC::MediaPlayer(instance, media);
#else
    media = VLC::Media(instance, path, VLC::Media::FromPath);
    player = VLC::MediaPlayer(media);
#endif

    replay_slot = sigc::mem_fun(*this, &VLCWidget::replay_callback);
}


VLCWidget::~VLCWidget()
{
    cancel_replay();
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
    player.setXwindow(xid);
    return true;
}

void VLCWidget::enable_replay()
{
    if (this->replay_timer.empty())
    {
        //int duration = player.length();
        auto x = libvlc_media_get_duration(media.get());
        libvlc_time_t y = libvlc_media_player_get_length(player.get());
        int duration = 10000;
        replay_timer = Glib::signal_timeout().connect(replay_slot, duration);
    }
    else
    {
        std::cout << "Replay is already active!" << std::endl;
    }
}

void VLCWidget::cancel_replay()
{
    if (replay_timer.empty())
    {
        std::cout << "Replay is not active!" << std::endl;
    }
    else
    {
        replay_timer.disconnect();
    }
}

bool VLCWidget::replay_callback()
{
    player.setPosition(0.0);
    if (!player.isPlaying())
    {
        player.play();
    }

    return true;
}

bool VLCWidget::play(bool replay)
{
    player.play();
    if (replay)
        enable_replay();
    
    return player.isPlaying();
}

bool VLCWidget::bind_window()
{
    auto window = this->get_window();
    auto xid = gdk_x11_window_get_xid(window.get()->gobj());
    std::cout << "Window xid: " << xid << std::endl;
    player.setXwindow(xid);
    return true;
}
