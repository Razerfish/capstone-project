# Zoetrope - Video Wallpapers for Linux
Simple animated desktop wallpapers for linux desktop environments.

## Building
To build the project first make sure that the required packages are installed.
```
apt install build-essential cmake libgtkmm-3.0-dev libvlc-dev vlc
```
This project is configured with CMake so to build all you need to do is run the following commands from the root of the repository:
```
mkdir out
cd out
cmake ..
cmake --build .
```
