#include <gtkmm.h>
#include <string>
#include <iostream>

#include "AppInfo.h"
#include "BackgroundWindow.h"

int main(int argc, char *argv[])
{
    std::cout << "Version: " << AppInfo_VERSION_MAJOR << "."
        << AppInfo_VERSION_MINOR << std::endl;

    std::string path;
    if (argc == 1)
    {
        std::cout << "Must specify a video to display" << std::endl;
        return 1;
    }
    path = std::string(argv[1]);

    int dummy_argc = 1;
    auto app =
        Gtk::Application::create(dummy_argc, argv,
                                 "org.Razerfish.AnimWallpapers.testing");

    BackgroundWindow window = BackgroundWindow(path);

    return app->run(window);
}