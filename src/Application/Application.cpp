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
}

Application::~Application()
{
    delete controller;
    delete background;
    delete player;
}

// Callbacks
void Application::update_media(std::string path)
{

}

void Application::update_volume(double volume)
{

}

void Application::set_mute(bool state)
{
    
}

void Application::toggle_play()
{

}

int Application::run()
{
    return app->run(*controller);
    return 0;
}
