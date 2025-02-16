#include <gtkmm.h>

int main(int argc, char *argv[])
{
    auto app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");
    Gtk::Window window;
    window.set_default_size(2560, 1440);
    window.set_type_hint(Gdk::WINDOW_TYPE_HINT_DESKTOP);
    return app->run(window);
}