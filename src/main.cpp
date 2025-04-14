#include <gtkmm.h>
#include <string>
#include <iostream>

#include "AppInfo.h"
#include "BackgroundWindow.h"

int main(int argc, char *argv[])
{
    std::cout << "Version: " << AppInfo_VERSION_MAJOR << "."
        << AppInfo_VERSION_MINOR << std::endl;

    // Boilerplate from example in the documentation.
    int argc1 = 1;
    auto app =
        Gtk::Application::create(argc1, argv,
                                 "org.Razerfish.AnimWallpapers.testing");

    // Choose between animated and stillframe based on argv.
    std::string path;
    if (argc == 1)
    {
        // Default to stillframe.
        path = "assets/background.jpg";
    }
    else if (argc > 1 && std::string(argv[1]) == "stillframe")
    {
        path = "assets/background.jpg";
    }
    else if (argc > 1 && std::string(argv[1]) == "animated")
    {
        path = "assets/background.gif";
    }

    //BackgroundWindow window = BackgroundWindow(path, 2560, 1440);
    BackgroundWindow window = BackgroundWindow("assets/Untitled3333.mp4", 2560, 1440);

    return app->run(window);
}