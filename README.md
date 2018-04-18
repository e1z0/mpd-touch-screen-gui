# Usage

This the frontend GUI application for my DIY HiFi system and digital audio streaming solution (based on Raspberry Pi 2B and HifiBerry AMP+) showing on an IL9341 LCD including a touch screen (with 320x240 resolution). It allows controlling a running MPD instance.

As the display lacks any hardware acceleration and is run from the framebuffer, the draw operations are largely reduced. I.e. there is no periodic rendering. The screen is updated when necessary.

## Configuration

On the first run the program will install the default configuration file (usually in `$HOME/.config/mpd-touch-screen-gui/program.conf` and `client.conf` for the client).


If you don't intend to run it on the same machine, you should set the MPD environment variables (i.e. `MPD_HOST`).

# Features

* Global button controls on the left side (most importantly to switch the view).
* Cover view that displays a cover or a replacement with song information. Swiping gestures allow control over the playback and volume (left, right, up, down and press).
* A playlist view allows viewing and changing the song from the current playlist.
* In the search view a on-screen keyboard is presented that allows to search for songs case-insensitive. The results may be browsed and played in the same manner as with the playlist view.
* A final view allows shutting down and rebooting the machine.
* A configurable UDP client allows basic UI controls (intended for use with an IR remote) in 6 directions (next and previous in x, y and natural order)

## Example images

![cover swipe](/example-images/cover-swipe.png)
![cover swipe text](/example-images/cover-swipe-text.png)
![playlist](/example-images/playlist.png)
![search input](/example-images/search-input.png)
![search result](/example-images/search-result.png)
![shutdown](/example-images/shutdown.png)

# Requirements

* SDL2_ttf (font rendering)
* SDL2_image (cover image loading)
* sdl2 (rendering)
* libmpdclient (communication with MPD instance)
* icu-uc (lower-case conversion for case insensitive search)
* boost_filesystem
* boost_system
* boost_asio (UDP interface for remote navigation)
* libwtk-sdl2 (widgets)
* C++17

# Install dependencies and requirements on Raspbian Stretch!
* `apt-get install autoconf libsdl2-dev libsdl-ttf2.0-0 libsdl2-ttf-dev libsdl2-image-dev libtool`
* `git clone https://bitbucket.org/sol_prog/raspberry-pi-gcc-binary.git`
* `cd raspberry-pi-gcc-binary&&tar xjvf gcc-7.2.0.tar.bz2 -C /opt/`
* `cd /opt/gcc-7.2.0/bin/&&ln -s gcc-7.2.0 gcc&&ln -s g++-7.2.0 g++&&ln -s c++-7.2.0 c++&&ln -s cpp-7.2.0 cpp`
* `export PATH=/opt/gcc-7.2.0/bin:$PATH`
* `git clone https://github.com/e1z0/libwtk-sdl2.git`
* `cd libwtk-sdl2&&autoreconf --install&&./configure&&make&&make install`

# Installation

*mpd-touch-screen-gui* uses autotools as build system:
* `autoreconf --install`
* `./configure`
* `make`
* `make install`

# State

I have been using it for a while now and it has been very stable. However, I'm currently trying to improve the UI and add IR remote control support for navigation.

# Contact

If you find my code useful please let me know. I'm also interested in your use case, any suggestions, improvements or criticism. Cheers!
