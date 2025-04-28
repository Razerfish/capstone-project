#include "Application.h"

#include "BackgroundWindow.h"
#include "VLCWidget.h"
#include "ControlWindow.h"

Application::Application(int argc, char *argv[], std::string identifier)
{
    stored_volume = 0.0;

    app = Gtk::Application::create(argc, argv, identifier);

    player = new VLCWidget();
    background = new BackgroundWindow(player);
    controller = new ControlWindow();

    controller->signal_file_selected().connect(media_set_slot);
    controller->signal_play_state_changed().connect(play_state_slot);
}

Application::~Application()
{
    media_set_slot.disconnect();
    play_state_slot.disconnect();

    delete controller;
    delete background;
    delete player;
}

// Callbacks
void Application::set_media(std::string media_path)
{
    player->set_media_from_path(media_path);
    player->play();
}

void Application::toggle_play()
{
    if (player->is_playing())
    {
        player->pause();
    }
    else
    {
        player->unpause();
    }
}

int Application::run()
{
    app->signal_startup().connect([&]{
        controller->show();
        app->add_window(*controller);
    });
    

    background->show();
    background->bind_when_ready();
    return app->run(*background);
}
