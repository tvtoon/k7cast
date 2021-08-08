/*
    Created on: Oct 18, 2019

	Copyright 2019 flyinghead

	This file is part of Flycast.

    Flycast is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Flycast is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Flycast.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "gl_context.h"
#include "types.h"
#include "oslib/oslib.h"

#if defined(_WIN32) && !defined(USE_SDL)
void CreateMainWindow();
void DestroyMainWindow();

WGLGraphicsContext theGLContext;

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

bool WGLGraphicsContext::Init()
{
	if (ourOpenGLRenderingContext != NULL)
		// Already initialized
		return true;

	CreateMainWindow();
	PIXELFORMATDESCRIPTOR pfd =
	{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
			32,                        //Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                        //Number of bits for the depthbuffer
			8,                        //Number of bits for the stencilbuffer
			0,                        //Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
	};

	int  letWindowsChooseThisPixelFormat;
	letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
	SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);

	HGLRC tempOpenGLContext = wglCreateContext(ourWindowHandleToDeviceContext);
	wglMakeCurrent(ourWindowHandleToDeviceContext, tempOpenGLContext);

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if(!wglChoosePixelFormatARB)
		return false;

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if(!wglCreateContextAttribsARB)
		return false;

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(!wglSwapIntervalEXT)
		return false;

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	ourOpenGLRenderingContext = wglCreateContextAttribsARB(ourWindowHandleToDeviceContext, 0, attribs);

	if (!ourOpenGLRenderingContext)
	{
		INFO_LOG(RENDERER, "Open GL 4.3 not supported");
		// Try Gl 3.1
		attribs[1] = 3;
		attribs[3] = 1;
		ourOpenGLRenderingContext = wglCreateContextAttribsARB(ourWindowHandleToDeviceContext, 0, attribs);
	}

	bool rv = true;

	if (ourOpenGLRenderingContext)
		wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);
	else
		rv = false;

	wglDeleteContext(tempOpenGLContext);

	if (rv) {
		rv = gl3wInit() != -1 && gl3wIsSupported(3, 1);
	}

	RECT r;
	GetClientRect(ourWindow, &r);
	screen_width = r.right - r.left;
	screen_height = r.bottom - r.top;

	if (rv)
		PostInit();

	return rv;
}

void WGLGraphicsContext::Swap()
{
#ifdef TEST_AUTOMATION
	do_swap_automation();
#endif
	wglSwapLayerBuffers(ourWindowHandleToDeviceContext, WGL_SWAP_MAIN_PLANE);
}

void WGLGraphicsContext::Term()
{
	PreTerm();
	if (ourOpenGLRenderingContext != NULL)
	{
		wglMakeCurrent(ourWindowHandleToDeviceContext, NULL);
		wglDeleteContext(ourOpenGLRenderingContext);
		ourOpenGLRenderingContext = NULL;
		DestroyMainWindow();
	}
}

#endif
