#include <gtkmm.h>
#include <string>
#include <iostream>

#include "AppInfo.h"

int main(int argc, char *argv[])
{
    std::cout << "Version: " << AppInfo_VERSION_MAJOR << "."
        << AppInfo_VERSION_MINOR << std::endl;

    // Boilerplate from example in the documentation.
    int argc1 = 1;
    auto app =
        Gtk::Application::create(argc1, argv,
                                 "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_default_size(2560, 1440);

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

    // Initialize image widget.
    Gtk::Image image = Gtk::Image(path);
    window.add(image);
    window.show_all_children();

    // Set window type hint.
    window.set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);
    return app->run(window);
}