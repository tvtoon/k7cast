#include "types.h"

#if defined(__unix__)
#include "hw/sh4/blockmanager.h"
#include "log/LogManager.h"
#include "emulator.h"
#include "rend/mainui.h"
#include "oslib/directory.h"

#include <cstdarg>
#include <csignal>
#include <unistd.h>

#if defined(SUPPORT_DISPMANX)
	#include "dispmanx.h"
#endif

#if defined(SUPPORT_X11)
	#include "x11.h"
#endif

#if defined(USE_SDL)
	#include "sdl/sdl.h"
#endif

#if defined(USE_EVDEV)
	#include "evdev.h"
#endif

#if defined(USE_JOYSTICK)
    #include "cfg/cfg.h"
	#include "joystick.h"
#endif

#if defined(USE_JOYSTICK)
	/* legacy joystick input */
	static int joystick_fd = -1; // Joystick file descriptor
#endif

void os_SetupInput()
{
#if defined(USE_EVDEV)
	input_evdev_init();
#endif

#if defined(USE_JOYSTICK)
	int joystick_device_id = cfgLoadInt("input", "joystick_device_id", JOYSTICK_DEFAULT_DEVICE_ID);
	if (joystick_device_id < 0) {
		INFO_LOG(INPUT, "Legacy Joystick input disabled by config.");
	}
	else
	{
		int joystick_device_length = snprintf(NULL, 0, JOYSTICK_DEVICE_STRING, joystick_device_id);
		char* joystick_device = (char*)malloc(joystick_device_length + 1);
		sprintf(joystick_device, JOYSTICK_DEVICE_STRING, joystick_device_id);
		joystick_fd = input_joystick_init(joystick_device);
		free(joystick_device);
	}
#endif

#if defined(SUPPORT_X11)
	input_x11_init();
#endif

#if defined(USE_SDL)
	input_sdl_init();
#endif
}

void UpdateInputState()
{
	#if defined(USE_JOYSTICK)
		input_joystick_handle(joystick_fd, 0);
	#endif

	#if defined(USE_EVDEV)
		input_evdev_handle();
	#endif

	#if defined(USE_SDL)
		input_sdl_handle();
	#endif
}

void os_DoEvents()
{
	#if defined(SUPPORT_X11)
		input_x11_handle();
		event_x11_handle();
	#endif
}

void os_SetWindowText(const char * text)
{
	#if defined(SUPPORT_X11)
		x11_window_set_text(text);
	#endif
	#if defined(USE_SDL)
		sdl_window_set_text(text);
	#endif
}

void os_CreateWindow()
{
	#if defined(SUPPORT_DISPMANX)
		dispmanx_window_create();
	#endif
	#if defined(SUPPORT_X11)
		x11_window_create();
	#endif
	#if defined(USE_SDL)
		sdl_window_create();
	#endif
}

void common_linux_setup();

// Find the user config directory.
// The following folders are checked in this order:
// $HOME/.reicast
// $HOME/.config/flycast
// $HOME/.config/reicast
// If no folder exists, $HOME/.config/flycast is created and used.
std::string find_user_config_dir()
{
	struct stat info;
	std::string xdg_home;
	if (getenv("HOME") != NULL)
	{
		// Support for the legacy config dir at "$HOME/.reicast"
		std::string legacy_home = (std::string)getenv("HOME") + "/.reicast/";
		if (flycast::stat(legacy_home.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
			// "$HOME/.reicast" already exists, let's use it!
			return legacy_home;

		/* If $XDG_CONFIG_HOME is not set, we're supposed to use "$HOME/.config" instead.
		 * Consult the XDG Base Directory Specification for details:
		 *   http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html#variables
		 */
		xdg_home = (std::string)getenv("HOME") + "/.config";
	}
	if (getenv("XDG_CONFIG_HOME") != NULL)
		// If XDG_CONFIG_HOME is set explicitly, we'll use that instead of $HOME/.config
		xdg_home = (std::string)getenv("XDG_CONFIG_HOME");

	if (!xdg_home.empty())
	{
		std::string fullpath = xdg_home + "/flycast/";
		if (flycast::stat(fullpath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
			// Found .config/flycast
			return fullpath;
		fullpath = xdg_home + "/reicast/";
		if (flycast::stat(fullpath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
			// Found .config/reicast
			return fullpath;

		// Create .config/flycast
		fullpath = xdg_home + "/flycast/";
		flycast::mkdir(fullpath.c_str(), 0755);

		return fullpath;
	}

	// Unable to detect config dir, use the current folder
	return ".";
}

// Find the user data directory.
// The following folders are checked in this order:
// $HOME/.reicast/data
// $HOME/.local/share/flycast
// $HOME/.local/share/reicast
// If no folder exists, $HOME/.local/share/flycast is created and used.
std::string find_user_data_dir()
{
	struct stat info;
	std::string xdg_home;
	if (getenv("HOME") != NULL)
	{
		// Support for the legacy config dir at "$HOME/.reicast/data"
		std::string legacy_data = (std::string)getenv("HOME") + "/.reicast/data/";
		if (flycast::stat(legacy_data.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
			// "$HOME/.reicast/data" already exists, let's use it!
			return legacy_data;

		/* If $XDG_DATA_HOME is not set, we're supposed to use "$HOME/.local/share" instead.
		 * Consult the XDG Base Directory Specification for details:
		 *   http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html#variables
		 */
		xdg_home = (std::string)getenv("HOME") + "/.local/share";
	}
	if (getenv("XDG_DATA_HOME") != NULL)
		// If XDG_DATA_HOME is set explicitly, we'll use that instead of $HOME/.local/share
		xdg_home = (std::string)getenv("XDG_DATA_HOME");

	if (!xdg_home.empty())
	{
		std::string fullpath = xdg_home + "/flycast/";
		if (flycast::stat(fullpath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
			// Found .local/share/flycast
			return fullpath;
		fullpath = xdg_home + "/reicast/";
		if (flycast::stat(fullpath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
			// Found .local/share/reicast
			return fullpath;

		// Create .local/share/flycast
		fullpath = xdg_home + "/flycast/";
		flycast::mkdir(fullpath.c_str(), 0755);

		return fullpath;
	}

	// Unable to detect data dir, use the current folder
	return ".";
}

static void addDirectoriesFromPath(std::vector<std::string>& dirs, const std::string& path, const std::string& suffix)
{
	std::string::size_type pos = 0;
	std::string::size_type n = path.find(':', pos);
	while (n != std::string::npos)
	{
		if (n != pos)
			dirs.push_back(path.substr(pos, n - pos) + suffix);
		pos = n + 1;
		n = path.find(':', pos);
	}
	// Separator not found
	if (pos < path.length())
		dirs.push_back(path.substr(pos) + suffix);
}

// Find a file in the user and system config directories.
// The following folders are checked in this order:
// $HOME/.reicast
// $HOME/.config/flycast
// $HOME/.config/reicast
// if XDG_CONFIG_DIRS is defined:
//   <$XDG_CONFIG_DIRS>/flycast
//   <$XDG_CONFIG_DIRS>/reicast
// else
//   /etc/flycast/
//   /etc/xdg/flycast/
// .
std::vector<std::string> find_system_config_dirs()
{
	std::vector<std::string> dirs;

	std::string xdg_home;
	if (getenv("HOME") != NULL)
	{
		// Support for the legacy config dir at "$HOME/.reicast"
		dirs.push_back((std::string)getenv("HOME") + "/.reicast/");
		xdg_home = (std::string)getenv("HOME") + "/.config";
	}
	if (getenv("XDG_CONFIG_HOME") != NULL)
		// If XDG_CONFIG_HOME is set explicitly, we'll use that instead of $HOME/.config
		xdg_home = (std::string)getenv("XDG_CONFIG_HOME");
	if (!xdg_home.empty())
	{
		// XDG config locations
		dirs.push_back(xdg_home + "/flycast/");
		dirs.push_back(xdg_home + "/reicast/");
	}

	if (getenv("XDG_CONFIG_DIRS") != NULL)
	{
		std::string path = (std::string)getenv("XDG_CONFIG_DIRS");
		addDirectoriesFromPath(dirs, path, "/flycast/");
		addDirectoriesFromPath(dirs, path, "/reicast/");
	}
	else
	{
		dirs.push_back("/etc/flycast/"); // This isn't part of the XDG spec, but much more common than /etc/xdg/
		dirs.push_back("/etc/xdg/flycast/");
	}
	dirs.push_back("./");

	return dirs;
}

// Find a file in the user data directories.
// The following folders are checked in this order:
// $HOME/.reicast/data
// $HOME/.local/share/flycast
// $HOME/.local/share/reicast
// if XDG_DATA_DIRS is defined:
//   <$XDG_DATA_DIRS>/flycast
//   <$XDG_DATA_DIRS>/reicast
// else
//   /usr/local/share/flycast
//   /usr/share/flycast
//   /usr/local/share/reicast
//   /usr/share/reicast
// <$FLYCAST_BIOS_PATH>
// ./
// ./data
std::vector<std::string> find_system_data_dirs()
{
	std::vector<std::string> dirs;

	std::string xdg_home;
	if (getenv("HOME") != NULL)
	{
		// Support for the legacy data dir at "$HOME/.reicast/data"
		dirs.push_back((std::string)getenv("HOME") + "/.reicast/data/");
		xdg_home = (std::string)getenv("HOME") + "/.local/share";
	}
	if (getenv("XDG_DATA_HOME") != NULL)
		// If XDG_DATA_HOME is set explicitly, we'll use that instead of $HOME/.local/share
		xdg_home = (std::string)getenv("XDG_DATA_HOME");
	if (!xdg_home.empty())
	{
		// XDG data locations
		dirs.push_back(xdg_home + "/flycast/");
		dirs.push_back(xdg_home + "/reicast/");
		dirs.push_back(xdg_home + "/reicast/data/");
	}

	if (getenv("XDG_DATA_DIRS") != NULL)
	{
		std::string path = (std::string)getenv("XDG_DATA_DIRS");

		addDirectoriesFromPath(dirs, path, "/flycast/");
		addDirectoriesFromPath(dirs, path, "/reicast/");
	}
	else
	{
		dirs.push_back("/usr/local/share/flycast/");
		dirs.push_back("/usr/share/flycast/");
		dirs.push_back("/usr/local/share/reicast/");
		dirs.push_back("/usr/share/reicast/");
	}
	if (getenv("FLYCAST_BIOS_PATH") != NULL)
	{
		std::string path = (std::string)getenv("FLYCAST_BIOS_PATH");
		addDirectoriesFromPath(dirs, path, "/");
	}
	dirs.push_back("./");
	dirs.push_back("data/");

	return dirs;
}

int main(int argc, char* argv[])
{
	LogManager::Init();

	// Set directories
	set_user_config_dir(find_user_config_dir());
	set_user_data_dir(find_user_data_dir());
	for (const auto& dir : find_system_config_dirs())
		add_system_config_dir(dir);
	for (const auto& dir : find_system_data_dirs())
		add_system_data_dir(dir);
	INFO_LOG(BOOT, "Config dir is: %s", get_writable_config_path("").c_str());
	INFO_LOG(BOOT, "Data dir is:   %s", get_writable_data_path("").c_str());

#if defined(USE_SDL)
	// init video now: on rpi3 it installs a sigsegv handler(?)
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		die("SDL: Initialization failed!");
	}
#endif

	common_linux_setup();

	if (reicast_init(argc, argv))
		die("Reicast initialization failed\n");

	mainui_loop();

	dc_term();

#if defined(USE_EVDEV)
	input_evdev_close();
#endif

#if defined(SUPPORT_X11)
	x11_window_destroy();
#endif

#if defined(USE_SDL)
	sdl_window_destroy();
#endif

	return 0;
}
#endif

void os_DebugBreak()
{
	raise(SIGTRAP);
}



