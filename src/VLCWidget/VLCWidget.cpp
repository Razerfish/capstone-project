#include "VLCWidget.h"

VLCWidget::VLCWidget(std::string path, int width, int height) : Gtk::DrawingArea()
{
    this->height = height;
    this->width = width;

    id = 0;

    int argCount = 1;
    // This results in a warning but I don't think there's any other way to do this.
    char* args = "--no-disable-screensaver";

    instance = VLC::Instance(argCount, &args);

#if LIBVLC_VERSION_INT >= LIBVLC_VERSION(4, 0, 0, 0)
    media = VLC::Media(path, VLC::Media::FromPath);
    player = VLC::MediaPlayer(instance, media);
#else
    media = VLC::Media(instance, path, VLC::Media::FromPath);
    player = VLC::MediaPlayer(media);
#endif
}


VLCWidget::~VLCWidget()
{
    
}


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

/*
void VLCWidget::on_realize()
{
    player.setXwindow(Gtk::ApplicationWindow(this->get_window()).get_id());
}


void VLCWidget::on_unrealize()
{
    player.setXwindow(0);
}
*/


bool VLCWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &ctr)
{
    player.setXwindow(id);
    return true;
}


void VLCWidget::setID(uint32_t id)
{
    this->id = id;
}


void VLCWidget::play()
{
    player.setXwindow(id);
    player.play();
}
