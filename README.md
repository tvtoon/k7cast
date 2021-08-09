# en.UTF-8

Yet another nullDC fork, from the flycast tree ( https://www.github.com/flyinghead/flycast ), to relieve some issues from the reicast transition: the renderer selection and the forced networking. The renderer selection still got a long way to go, the networking elimination "just works" but is not in touch with the reicast way... Why? Besides time, the lack of knowledge about DreamCast internals isn't helpful, so it will be reworked later looking trough reicast.

## Macros.

Important to notice: drivers can be enabled but not selected like in reicast.

* NDEBUG: very important macro, as it wasn't used in reicast. Spills lots of debugging without this setting.
* SUPPORT_X11: the X11 backend, however it conflicts with the SDL support.
* USE_ALSA: ALSA backend, "oslib/audiobackend_alsa.cpp".
* USE_EVDEV: general input for Linux (Android) trough evdev library, "linux-dist/evdev.cpp" and "linux-dist/main.cpp" only. Used to conflict with others.
* USE_JOYSTICK: joystick for Linux, "linux-dist/joystick.cpp" and "linux-dist/main.cpp" only.
* USE_LIBAO: "oslib/audiobackend_libao.cpp".
* USE_NETWORK: enable the networking stuff, both BBA and modem. It needs picotcp and miniupnpc, not included.
* USE_SDL: for the input and OpenGL backend.
* USE_SDL_AUDIO: for the audio driver, "oslib/audiobackend_sdl2.cpp".
* USE_UDEV: uses udev to poll devices connected, only worthy with the evdev macro.
* USE_VULKAN: Vulkan backend.
* TEST_DC1: custom testing flag, not ready to use.
