import sys
import gi

gi.require_version("Gtk", "4.0")

from gi.repository import Gtk, Gio, Gdk

class TestWindow(Gtk.ApplicationWindow):
    def __init__(self, *args, **kwargs):
        super(TestWindow, self).__init__(*args, **kwargs)

if __name__ == "__main__":
    win = Gtk.ApplicationWindow()
    win.set_type_hint(Gdk.WindowTypeHint.DESKTOP)
    win.present()
