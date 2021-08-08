#include "oslib/oslib.h"
#include "oslib/audiostream.h"
#include "imgread/common.h"
#include "stdclass.h"
#include "cfg/cfg.h"
#include "xinput_gamepad.h"
#include "win_keyboard.h"
#include "hw/sh4/blockmanager.h"
#include "log/LogManager.h"
#include "wsi/context.h"
#if defined(USE_SDL)
#include "sdl/sdl.h"
#endif
#include "hw/maple_devs.h"
#include "emulator.h"
#include "rend/mainui.h"
#include "hw/sh4/ngen.h"
#include "oslib/host_context.h"
#include "../shell/windows/resource.h"

#include <windows.h>
#include <windowsx.h>

PCHAR*
	CommandLineToArgvA(
	PCHAR CmdLine,
	int* _argc
	)
{
	PCHAR* argv;
	PCHAR  _argv;
	ULONG   len;
	ULONG   argc;
	CHAR    a;
	ULONG   i, j;

	BOOLEAN  in_QM;
	BOOLEAN  in_TEXT;
	BOOLEAN  in_SPACE;

	len = strlen(CmdLine);
	i = ((len+2)/2)*sizeof(PVOID) + sizeof(PVOID);

	argv = (PCHAR*)GlobalAlloc(GMEM_FIXED,
		i + (len+2)*sizeof(CHAR));

	_argv = (PCHAR)(((PUCHAR)argv)+i);

	argc = 0;
	argv[argc] = _argv;
	in_QM = FALSE;
	in_TEXT = FALSE;
	in_SPACE = TRUE;
	i = 0;
	j = 0;

	while ((a = CmdLine[i]) != 0)
	{
		if(in_QM)
		{
			if(a == '\"')
			{
				in_QM = FALSE;
			}
			else
			{
				_argv[j] = a;
				j++;
			}
		}
		else
		{
			switch(a)
			{
			case '\"':
				in_QM = TRUE;
				in_TEXT = TRUE;
				if(in_SPACE) {
					argv[argc] = _argv+j;
					argc++;
				}
				in_SPACE = FALSE;
				break;
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				if(in_TEXT)
				{
					_argv[j] = '\0';
					j++;
				}
				in_TEXT = FALSE;
				in_SPACE = TRUE;
				break;
			default:
				in_TEXT = TRUE;
				if(in_SPACE)
				{
					argv[argc] = _argv+j;
					argc++;
				}
				_argv[j] = a;
				j++;
				in_SPACE = FALSE;
				break;
			}
		}
		i++;
	}
	_argv[j] = '\0';
	argv[argc] = NULL;

	(*_argc) = argc;
	return argv;
}

bool VramLockedWrite(u8* address);
bool BM_LockedWrite(u8* address);

static std::shared_ptr<WinKbGamepadDevice> kb_gamepad;
static std::shared_ptr<WinMouseGamepadDevice> mouse_gamepad;

void os_SetupInput()
{
#if defined(USE_SDL)
	input_sdl_init();
#else
	XInputGamepadDevice::CreateDevices();
	kb_gamepad = std::make_shared<WinKbGamepadDevice>(0);
	GamepadDevice::Register(kb_gamepad);
	mouse_gamepad = std::make_shared<WinMouseGamepadDevice>(0);
	GamepadDevice::Register(mouse_gamepad);
#endif
}

static void readContext(const EXCEPTION_POINTERS *ep, host_context_t &context)
{
#if HOST_CPU == CPU_X86
	context.pc = ep->ContextRecord->Eip;
	context.esp = ep->ContextRecord->Esp;
	context.eax = ep->ContextRecord->Eax;
	context.ecx = ep->ContextRecord->Ecx;
#elif HOST_CPU == CPU_X64
	context.pc = ep->ContextRecord->Rip;
	context.rsp = ep->ContextRecord->Rsp;
	context.r9 = ep->ContextRecord->R9;
	context.rcx = ep->ContextRecord->Rcx;
#endif
}

static void writeContext(EXCEPTION_POINTERS *ep, const host_context_t &context)
{
#if HOST_CPU == CPU_X86
	ep->ContextRecord->Eip = context.pc;
	ep->ContextRecord->Esp = context.esp;
	ep->ContextRecord->Eax = context.eax;
	ep->ContextRecord->Ecx = context.ecx;
#elif HOST_CPU == CPU_X64
	ep->ContextRecord->Rip = context.pc;
	ep->ContextRecord->Rsp = context.rsp;
	ep->ContextRecord->R9 = context.r9;
	ep->ContextRecord->Rcx = context.rcx;
#endif
}
LONG ExeptionHandler(EXCEPTION_POINTERS *ep)
{
	u32 dwCode = ep->ExceptionRecord->ExceptionCode;

	if (dwCode != EXCEPTION_ACCESS_VIOLATION)
		return EXCEPTION_CONTINUE_SEARCH;

	EXCEPTION_RECORD* pExceptionRecord = ep->ExceptionRecord;
	u8* address = (u8 *)pExceptionRecord->ExceptionInformation[1];

	//printf("[EXC] During access to : 0x%X\n", address);

	// code protection in RAM
	if (bm_RamWriteAccess(address))
		return EXCEPTION_CONTINUE_EXECUTION;
	// texture protection in VRAM
	if (VramLockedWrite(address))
		return EXCEPTION_CONTINUE_EXECUTION;
	// FPCB jump table protection
	if (BM_LockedWrite(address))
		return EXCEPTION_CONTINUE_EXECUTION;

	host_context_t context;
	readContext(ep, context);
#if FEAT_SHREC == DYNAREC_JIT
	// fast mem access rewriting
	if (ngen_Rewrite(context, address))
	{
		writeContext(ep, context);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
#endif

    ERROR_LOG(COMMON, "[GPF] PC %p unhandled access to %p", (void *)context.pc, address);
    os_DebugBreak();

	return EXCEPTION_CONTINUE_SEARCH;
}


void SetupPath()
{
	wchar_t fname[512];
	GetModuleFileNameW(0, fname, ARRAY_SIZE(fname));

	std::string fn;
	nowide::stackstring path;
	if (!path.convert(fname))
		fn = ".\\";
	else
		fn = path.c_str();
	size_t pos = get_last_slash_pos(fn);
	if (pos != std::string::npos)
		fn = fn.substr(0, pos) + "\\";
	else
		fn = ".\\";
	set_user_config_dir(fn);
	add_system_data_dir(fn);

	std::string data_path = fn + "data\\";
	set_user_data_dir(data_path);
	CreateDirectory(data_path.c_str(), NULL);
}

static Win32KeyboardDevice keyboard(0);

void ToggleFullscreen();


void UpdateInputState()
{
#if defined(USE_SDL)
	input_sdl_handle();
#else
	for (int port = 0; port < 4; port++)
	{
		std::shared_ptr<XInputGamepadDevice> gamepad = XInputGamepadDevice::GetXInputDevice(port);
		if (gamepad != nullptr)
			gamepad->ReadInput();
	}
#endif
}

// Windows class name to register
#define WINDOW_CLASS "nilDC"

// Width and height of the window
#define DEFAULT_WINDOW_WIDTH  1280
#define DEFAULT_WINDOW_HEIGHT 720
extern int screen_width, screen_height;
static bool window_maximized = false;

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		/*
		Here we are handling 2 system messages: screen saving and monitor power.
		They are especially relevant on mobile devices.
		*/
	case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_SCREENSAVE:   // Screensaver trying to start ?
			case SC_MONITORPOWER: // Monitor trying to enter powersave ?
				return 0;         // Prevent this from happening
			}
			break;
		}
		// Handles the close message when a user clicks the quit icon of the window
	case WM_CLOSE:
		PostQuitMessage(0);
		return 1;

	case WM_SIZE:
		screen_width = LOWORD(lParam);
		screen_height = HIWORD(lParam);
		window_maximized = (wParam & SIZE_MAXIMIZED) != 0;
		return 0;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		switch (message)
		{
		case WM_LBUTTONDOWN:
			mouse_gamepad->gamepad_btn_input(0, true);
			break;
		case WM_LBUTTONUP:
			mouse_gamepad->gamepad_btn_input(0, false);
			break;
		case WM_MBUTTONDOWN:
			mouse_gamepad->gamepad_btn_input(1, true);
			break;
		case WM_MBUTTONUP:
			mouse_gamepad->gamepad_btn_input(1, false);
			break;
		case WM_RBUTTONDOWN:
			mouse_gamepad->gamepad_btn_input(2, true);
			break;
		case WM_RBUTTONUP:
			mouse_gamepad->gamepad_btn_input(2, false);
			break;
		}
		/* no break */
	case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			SetMousePosition(xPos, yPos, screen_width, screen_height);

			mo_buttons[0] = 0xffffffff;
			if (wParam & MK_LBUTTON)
				mo_buttons[0] &= ~(1 << 2);
			if (wParam & MK_MBUTTON)
				mo_buttons[0] &= ~(1 << 3);
			if (wParam & MK_RBUTTON)
				mo_buttons[0] &= ~(1 << 1);
		}
		if (message != WM_MOUSEMOVE)
			return 0;
		break;
	case WM_MOUSEWHEEL:
		mo_wheel_delta[0] -= (float)GET_WHEEL_DELTA_WPARAM(wParam)/(float)WHEEL_DELTA * 16;
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
		{
			u8 keycode;
			// bit 24 indicates whether the key is an extended key, such as the right-hand ALT and CTRL keys that appear on an enhanced 101- or 102-key keyboard.
			// (It also distinguishes between the main Return key and the numeric keypad Enter key)
			// The value is 1 if it is an extended key; otherwise, it is 0.
			if (wParam == VK_RETURN && ((lParam & (1 << 24)) != 0))
				keycode = VK_NUMPAD_RETURN;
			else
				keycode = wParam & 0xff;
			kb_gamepad->gamepad_btn_input(keycode, message == WM_KEYDOWN);
			keyboard.keyboard_input(keycode, message == WM_KEYDOWN);
		}
		break;
	
	case WM_SYSKEYDOWN:
		if (wParam == VK_RETURN)
			if ((HIWORD(lParam) & KF_ALTDOWN))
				ToggleFullscreen();
		
		break;

	case WM_CHAR:
		keyboard.keyboard_character((char)wParam);
		return 0;

	default:
		break;
	}

	// Calls the default window procedure for messages we did not handle
	return DefWindowProc(hWnd, message, wParam, lParam);
}

static HWND hWnd;
static int window_x, window_y;

#if !defined(USE_SDL)
static bool windowClassRegistered;

void CreateMainWindow()
{
	if (hWnd != NULL)
		return;
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(0);
	if (!windowClassRegistered)
	{
		WNDCLASS sWC;
		sWC.style = CS_HREDRAW | CS_VREDRAW;
		sWC.lpfnWndProc = WndProc2;
		sWC.cbClsExtra = 0;
		sWC.cbWndExtra = 0;
		sWC.hInstance = hInstance;
		sWC.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		sWC.hCursor = LoadCursor(NULL, IDC_ARROW);
		sWC.lpszMenuName = 0;
		sWC.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
		sWC.lpszClassName = WINDOW_CLASS;
		ATOM registerClass = RegisterClass(&sWC);
		if (!registerClass)
			MessageBox(0, "Failed to register the window class", "Error", MB_OK | MB_ICONEXCLAMATION);
		else
			windowClassRegistered = true;
		screen_width = cfgLoadInt("window", "width", DEFAULT_WINDOW_WIDTH);
		screen_height = cfgLoadInt("window", "height", DEFAULT_WINDOW_HEIGHT);
		window_maximized = cfgLoadBool("window", "maximized", false);
	}

	// Create the eglWindow
	RECT sRect;
	SetRect(&sRect, 0, 0, screen_width, screen_height);
	AdjustWindowRectEx(&sRect, WS_OVERLAPPEDWINDOW, false, 0);

	hWnd = CreateWindow(WINDOW_CLASS, VER_FULLNAME, WS_VISIBLE | WS_OVERLAPPEDWINDOW | (window_maximized ? WS_MAXIMIZE : 0),
			window_x, window_y, sRect.right - sRect.left, sRect.bottom - sRect.top, NULL, NULL, hInstance, NULL);
#ifdef USE_VULKAN
	theVulkanContext.SetWindow((void *)hWnd, (void *)GetDC((HWND)hWnd));
#endif
	theGLContext.SetWindow(hWnd);
	theGLContext.SetDeviceContext(GetDC(hWnd));
}
#endif

void os_CreateWindow()
{
#if defined(USE_SDL)
	sdl_window_create();
#else
	CreateMainWindow();
	InitRenderApi();
#endif	// !USE_SDL
}

void DestroyMainWindow()
{
	if (hWnd)
	{
		WINDOWPLACEMENT placement;
		placement.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(hWnd, &placement);
		window_maximized = placement.showCmd == SW_SHOWMAXIMIZED;
		window_x = placement.rcNormalPosition.left;
		window_y = placement.rcNormalPosition.top;
		DestroyWindow(hWnd);
		hWnd = NULL;
	}
}

void* libPvr_GetRenderTarget()
{
	return (void*)hWnd;
}

void ToggleFullscreen()
{
	static RECT rSaved;
	static bool fullscreen=false;

	fullscreen = !fullscreen;


	if (fullscreen)
	{
		GetWindowRect(hWnd, &rSaved);

		MONITORINFO mi = { sizeof(mi) };
		HMONITOR hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
		if (GetMonitorInfo(hmon, &mi)) {

			SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
			SetWindowLongPtr(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

			SetWindowPos(hWnd, HWND_TOPMOST, mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, 
				SWP_SHOWWINDOW|SWP_FRAMECHANGED|SWP_ASYNCWINDOWPOS);
		}
	}
	else {
		
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
		SetWindowLongPtr(hWnd, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW | (window_maximized ? WS_MAXIMIZE : 0));

		SetWindowPos(hWnd, NULL, rSaved.left, rSaved.top,
			rSaved.right - rSaved.left, rSaved.bottom - rSaved.top, 
			SWP_SHOWWINDOW|SWP_FRAMECHANGED|SWP_ASYNCWINDOWPOS|SWP_NOZORDER);
	}

}


BOOL CtrlHandler( DWORD fdwCtrlType )
{
	switch( fdwCtrlType )
	{
		case CTRL_SHUTDOWN_EVENT:
		case CTRL_LOGOFF_EVENT:
		// Pass other signals to the next handler.
		case CTRL_BREAK_EVENT:
		// CTRL-CLOSE: confirm that the user wants to exit.
		case CTRL_CLOSE_EVENT:
		// Handle the CTRL-C signal.
		case CTRL_C_EVENT:
			SendMessageA(hWnd, WM_CLOSE, 0, 0); //FIXEM
			return( TRUE );
		default:
			return FALSE;
	}
}


void os_SetWindowText(const char* text)
{
#if defined(USE_SDL)
	sdl_window_set_text(text);
#else
	if (GetWindowLongPtr(hWnd, GWL_STYLE) & WS_BORDER)
	{
		SetWindowText(hWnd, text);
	}
#endif
}

void ReserveBottomMemory()
{
#if defined(_WIN64) && defined(_DEBUG)
    static bool s_initialized = false;
    if ( s_initialized )
        return;
    s_initialized = true;

    // Start by reserving large blocks of address space, and then
    // gradually reduce the size in order to capture all of the
    // fragments. Technically we should continue down to 64 KB but
    // stopping at 1 MB is sufficient to keep most allocators out.

    const size_t LOW_MEM_LINE = 0x100000000LL;
    size_t totalReservation = 0;
    size_t numVAllocs = 0;
    size_t numHeapAllocs = 0;
    size_t oneMB = 1024 * 1024;
    for (size_t size = 256 * oneMB; size >= oneMB; size /= 2)
    {
        for (;;)
        {
            void* p = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);
            if (!p)
                break;

            if ((size_t)p >= LOW_MEM_LINE)
            {
                // We don't need this memory, so release it completely.
                VirtualFree(p, 0, MEM_RELEASE);
                break;
            }

            totalReservation += size;
            ++numVAllocs;
        }
    }

    // Now repeat the same process but making heap allocations, to use up
    // the already reserved heap blocks that are below the 4 GB line.
    HANDLE heap = GetProcessHeap();
    for (size_t blockSize = 64 * 1024; blockSize >= 16; blockSize /= 2)
    {
        for (;;)
        {
            void* p = HeapAlloc(heap, 0, blockSize);
            if (!p)
                break;

            if ((size_t)p >= LOW_MEM_LINE)
            {
                // We don't need this memory, so release it completely.
                HeapFree(heap, 0, p);
                break;
            }

            totalReservation += blockSize;
            ++numHeapAllocs;
        }
    }

    // Perversely enough the CRT doesn't use the process heap. Suck up
    // the memory the CRT heap has already reserved.
    for (size_t blockSize = 64 * 1024; blockSize >= 16; blockSize /= 2)
    {
        for (;;)
        {
            void* p = malloc(blockSize);
            if (!p)
                break;

            if ((size_t)p >= LOW_MEM_LINE)
            {
                // We don't need this memory, so release it completely.
                free(p);
                break;
            }

            totalReservation += blockSize;
            ++numHeapAllocs;
        }
    }

    // Print diagnostics showing how many allocations we had to make in
    // order to reserve all of low memory, typically less than 200.
    char buffer[1000];
    sprintf_s(buffer, "Reserved %1.3f MB (%d vallocs,"
                      "%d heap allocs) of low-memory.\n",
            totalReservation / (1024 * 1024.0),
            (int)numVAllocs, (int)numHeapAllocs);
    OutputDebugStringA(buffer);
#endif
}

#ifdef _WIN64

typedef union _UNWIND_CODE {
	struct {
		u8 CodeOffset;
		u8 UnwindOp : 4;
		u8 OpInfo : 4;
	};
	USHORT FrameOffset;
} UNWIND_CODE, *PUNWIND_CODE;

typedef struct _UNWIND_INFO {
	u8 Version : 3;
	u8 Flags : 5;
	u8 SizeOfProlog;
	u8 CountOfCodes;
	u8 FrameRegister : 4;
	u8 FrameOffset : 4;
	//ULONG ExceptionHandler;
	UNWIND_CODE UnwindCode[1];
	/*  UNWIND_CODE MoreUnwindCode[((CountOfCodes + 1) & ~1) - 1];
	*   union {
	*       OPTIONAL ULONG ExceptionHandler;
	*       OPTIONAL ULONG FunctionEntry;
	*   };
	*   OPTIONAL ULONG ExceptionData[]; */
} UNWIND_INFO, *PUNWIND_INFO;

static RUNTIME_FUNCTION Table[1];
static _UNWIND_INFO unwind_info[1];

EXCEPTION_DISPOSITION
__gnat_SEH_error_handler(struct _EXCEPTION_RECORD* ExceptionRecord,
void *EstablisherFrame,
struct _CONTEXT* ContextRecord,
	void *DispatcherContext)
{
	EXCEPTION_POINTERS ep;
	ep.ContextRecord = ContextRecord;
	ep.ExceptionRecord = ExceptionRecord;

	return (EXCEPTION_DISPOSITION)ExeptionHandler(&ep);
}

PRUNTIME_FUNCTION
seh_callback(
_In_ DWORD64 ControlPc,
_In_opt_ PVOID Context
) {
	unwind_info[0].Version = 1;
	unwind_info[0].Flags = UNW_FLAG_UHANDLER;
	/* We don't use the unwinding info so fill the structure with 0 values.  */
	unwind_info[0].SizeOfProlog = 0;
	unwind_info[0].CountOfCodes = 0;
	unwind_info[0].FrameOffset = 0;
	unwind_info[0].FrameRegister = 0;
	/* Add the exception handler.  */

//		unwind_info[0].ExceptionHandler =
	//	(DWORD)((u8 *)__gnat_SEH_error_handler - CodeCache);
	/* Set its scope to the entire program.  */
	Table[0].BeginAddress = 0;// (CodeCache - (u8*)__ImageBase);
	Table[0].EndAddress = /*(CodeCache - (u8*)__ImageBase) +*/ CODE_SIZE + TEMP_CODE_SIZE;
	Table[0].UnwindData = (DWORD)((u8 *)unwind_info - CodeCache);
    INFO_LOG(COMMON, "TABLE CALLBACK");
	//for (;;);
	return Table;
}
void setup_seh() {
#if 1
	/* Get the base of the module.  */
	//u8* __ImageBase = (u8*)GetModuleHandle(NULL);
	/* Current version is always 1 and we are registering an
	exception handler.  */
	unwind_info[0].Version = 1;
	unwind_info[0].Flags = UNW_FLAG_NHANDLER;
	/* We don't use the unwinding info so fill the structure with 0 values.  */
	unwind_info[0].SizeOfProlog = 0;
	unwind_info[0].CountOfCodes = 1;
	unwind_info[0].FrameOffset = 0;
	unwind_info[0].FrameRegister = 0;
	/* Add the exception handler.  */

	unwind_info[0].UnwindCode[0].CodeOffset = 0;
	unwind_info[0].UnwindCode[0].UnwindOp = 2;// UWOP_ALLOC_SMALL;
	unwind_info[0].UnwindCode[0].OpInfo = 0x20 / 8;

	//unwind_info[0].ExceptionHandler =
		//(DWORD)((u8 *)__gnat_SEH_error_handler - CodeCache);
	/* Set its scope to the entire program.  */
	Table[0].BeginAddress = 0;// (CodeCache - (u8*)__ImageBase);
	Table[0].EndAddress = /*(CodeCache - (u8*)__ImageBase) +*/ CODE_SIZE + TEMP_CODE_SIZE;
	Table[0].UnwindData = (DWORD)((u8 *)unwind_info - CodeCache);
	/* Register the unwind information.  */
	RtlAddFunctionTable(Table, 1, (DWORD64)CodeCache);
#endif

	//verify(RtlInstallFunctionTableCallback((unat)CodeCache | 0x3, (DWORD64)CodeCache, CODE_SIZE + TEMP_CODE_SIZE, seh_callback, 0, 0));
}
#endif

static void findKeyboardLayout()
{
	HKL keyboardLayout = GetKeyboardLayout(0);
	WORD lcid = HIWORD(keyboardLayout);
	switch (PRIMARYLANGID(lcid)) {
	case 0x09:	// English
		if (lcid == 0x0809)
			settings.input.keyboardLangId = KeyboardLayout::UK;
		else
			settings.input.keyboardLangId = KeyboardLayout::US;
		break;
	case 0x11:
		settings.input.keyboardLangId = KeyboardLayout::JP;
		break;
	case 0x07:
		settings.input.keyboardLangId = KeyboardLayout::GE;
		break;
	case 0x0c:
		settings.input.keyboardLangId = KeyboardLayout::FR;
		break;
	case 0x10:
		settings.input.keyboardLangId = KeyboardLayout::IT;
		break;
	case 0x0A:
		settings.input.keyboardLangId = KeyboardLayout::SP;
		break;
	default:
		break;
	}
}


// DEF_CONSOLE allows you to override linker subsystem and therefore default console //
//	: pragma isn't pretty but def's are configurable 
#ifdef DEF_CONSOLE
#pragma comment(linker, "/subsystem:console")

int main(int argc, char **argv)
{

#else
#pragma comment(linker, "/subsystem:windows")

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShowCmd)
{
	int argc = 0;
	char* cmd_line = GetCommandLineA();
	char** argv = CommandLineToArgvA(cmd_line, &argc);

#endif

#if defined(_WIN32) && defined(LOG_TO_PTY)
    setbuf(stderr,NULL);
#endif
	LogManager::Init();

	ReserveBottomMemory();
	SetupPath();
	findKeyboardLayout();
#ifdef _WIN64
	AddVectoredExceptionHandler(1, ExeptionHandler);
#else
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&ExeptionHandler);
#endif
	if (reicast_init(argc, argv) != 0)
		die("Flycast initialization failed");

#ifdef _WIN64
	setup_seh();
#endif

	mainui_loop();

	dc_term();

	SetUnhandledExceptionFilter(0);
#ifdef USE_SDL
	sdl_window_destroy();
#else
	cfgSaveBool("window", "maximized", window_maximized);
	if (!window_maximized && screen_width != 0 && screen_height != 0)
	{
		cfgSaveInt("window", "width", screen_width);
		cfgSaveInt("window", "height", screen_height);
	}
#endif

	return 0;
}

double os_GetSeconds()
{
	static double qpfd = []() {
		LARGE_INTEGER qpf;
		QueryPerformanceFrequency(&qpf);
		return 1.0 / qpf.QuadPart; }();

	LARGE_INTEGER time_now;

	QueryPerformanceCounter(&time_now);
	static LARGE_INTEGER time_now_base = time_now;

	return (time_now.QuadPart - time_now_base.QuadPart) * qpfd;
}

void os_DebugBreak()
{
	__debugbreak();
}

void os_DoEvents()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// If the message is WM_QUIT, exit the while loop
		if (msg.message == WM_QUIT)
		{
			dc_exit();
		}

		// Translate the message and dispatch it to WindowProc()
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
