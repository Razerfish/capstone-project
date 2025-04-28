#include <gtkmm.h>
#include <string>
#include <iostream>

#include "AppInfo.h"
#include "BackgroundWindow.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    int dummy_argc = 1;
    Application app = Application(dummy_argc, argv, AppInfo_IDENTIFIER);

    return app.run();
}
