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
#pragma once
#if defined(__APPLE__)
#if defined(TARGET_IPHONE) //apple-specific ogles2 headers
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include <OpenGL/gl3.h>
#endif
#include "gl_context.h"

class OSXGraphicsContext : public GLGraphicsContext
{
public:
	bool Init() { PostInit(); return true; }
	void Term() { PreTerm(); }
	void Swap();
};

extern OSXGraphicsContext theGLContext;
#endif
