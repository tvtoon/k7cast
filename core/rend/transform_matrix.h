/*
    Created on: Oct 22, 2019

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
#include "TexCache.h"
#include "hw/pvr/ta_ctx.h"
#include "cfg/option.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

extern int screen_width, screen_height;

//template<bool invertY>
class TransformMatrix
{
public:
	TransformMatrix() = default;
	TransformMatrix(const rend_context& renderingContext, int width = 0, int height = 0);

	bool IsClipped() const;

	const glm::mat4& GetNormalMatrix() const;
	const glm::mat4& GetScissorMatrix() const;
	const glm::mat4& GetViewportMatrix() const;

	// Return the width of the black bars when the screen is wider than 4:3. Returns a negative number when the screen is taller than 4:3,
	// whose inverse is the height of the top and bottom bars.
	float GetSidebarWidth() const;
	glm::vec2 GetDreamcastViewport() const;
	void CalcMatrices(const rend_context *renderingContext, int width = 0, int height = 0);

private:
	void GetFramebufferScaling(bool scissor, float& scale_x, float& scale_y);
 bool invertY;
	const rend_context *renderingContext = nullptr;
	glm::mat4 normalMatrix;
	glm::mat4 scissorMatrix;
	glm::mat4 viewportMatrix;
	glm::vec2 dcViewport;
	glm::vec2 renderViewport;
	float scale_x = 0;
	float scale_y = 0;
	float sidebarWidth = 0;
};
