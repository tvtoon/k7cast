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
/*
#include "TexCache.h"
#include "hw/pvr/ta_ctx.h"
#include "cfg/option.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
*/
#include "transform_matrix.h"
/*
TransformMatrix::TransformMatrix()
{
}
*/
TransformMatrix::TransformMatrix(const rend_context& renderingContext, int width, int height)
{
 invertY = true;
 CalcMatrices(&renderingContext, width, height);
}

bool TransformMatrix::IsClipped() const
{
 return renderingContext->fb_X_CLIP.min != 0 || lroundf((renderingContext->fb_X_CLIP.max + 1) / scale_x) != 640L || renderingContext->fb_Y_CLIP.min != 0 || lroundf((renderingContext->fb_Y_CLIP.max + 1) / scale_y) != 480L;
}

const glm::mat4& TransformMatrix::GetNormalMatrix() const
{
 return normalMatrix;
}

const glm::mat4& TransformMatrix::GetScissorMatrix() const
{
 return scissorMatrix;
}

const glm::mat4& TransformMatrix::GetViewportMatrix() const
{
 return viewportMatrix;
}

// Return the width of the black bars when the screen is wider than 4:3. Returns a negative number when the screen is taller than 4:3,
// whose inverse is the height of the top and bottom bars.
float TransformMatrix::GetSidebarWidth() const
{
 return sidebarWidth;
}

glm::vec2 TransformMatrix::GetDreamcastViewport() const
{
 return dcViewport;
}

void TransformMatrix::CalcMatrices(const rend_context *renderingContext, int width, int height )
{
		renderViewport = { width == 0 ? screen_width : width, height == 0 ? screen_height : height };
		this->renderingContext = renderingContext;

		GetFramebufferScaling(false, scale_x, scale_y);

		if (renderingContext->isRTT)
		{
			dcViewport.x = renderingContext->fb_X_CLIP.max - renderingContext->fb_X_CLIP.min + 1;
			dcViewport.y = renderingContext->fb_Y_CLIP.max - renderingContext->fb_Y_CLIP.min + 1;
			normalMatrix = glm::translate(glm::vec3(-1, -1, 0))
				* glm::scale(glm::vec3(2.0f / dcViewport.x, 2.0f / dcViewport.y, 1.f));
			scissorMatrix = normalMatrix;
			sidebarWidth = 0;
		}
		else
		{
			dcViewport.x = 640.f * scale_x;
			dcViewport.y = 480.f * scale_y;

			float startx = 0;
			float starty = 0;
#if 0
			const bool vga = FB_R_CTRL.vclk_div == 1;
			switch (SPG_LOAD.hcount)
			{
				case 857: // NTSC, VGA
					startx = VO_STARTX.HStart - (vga ? 0xa8 : 0xa4);
					break;
				case 863: // PAL
					startx = VO_STARTX.HStart - 0xae;
					break;
				default:
					INFO_LOG(PVR, "unknown video mode: hcount %d", SPG_LOAD.hcount);
					break;
			}
			switch (SPG_LOAD.vcount)
			{
				case 524: // NTSC, VGA
					starty = VO_STARTY.VStart_field1 - (vga ? 0x28 : 0x12);
					break;
				case 262: // NTSC 240p
					starty = VO_STARTY.VStart_field1 - 0x11;
					break;
				case 624: // PAL
					starty = VO_STARTY.VStart_field1 - 0x2d;
					break;
				case 312: // PAL 240p
					starty = VO_STARTY.VStart_field1 - 0x2e;
					break;
				default:
					INFO_LOG(PVR, "unknown video mode: vcount %d", SPG_LOAD.vcount);
					break;
			}
			// some heuristic...
			startx *= 0.8;
			starty *= 1.1;
			// TODO need to adjust lightgun coordinates
#endif
			normalMatrix = glm::translate(glm::vec3(startx, starty, 0));
			scissorMatrix = normalMatrix;

			const float screen_stretching = config::ScreenStretching / 100.f;
			float scissoring_scale_x, scissoring_scale_y;
			GetFramebufferScaling(true, scissoring_scale_x, scissoring_scale_y);

			float x_coef;
			float y_coef;
			glm::mat4 trans_rot;

			if (config::Rotate90)
			{
				float dc2s_scale_h = renderViewport.x / 640.0f;

				sidebarWidth = 0;
				y_coef = 2.0f / (renderViewport.y / dc2s_scale_h * scale_y) * screen_stretching * (invertY ? -1 : 1);
				x_coef = 2.0f / dcViewport.x;
			}
			else
			{
				float dc2s_scale_h = renderViewport.y / 480.0f;

				sidebarWidth =  (renderViewport.x - dc2s_scale_h * 640.0f * screen_stretching) / 2;
				x_coef = 2.0f / (renderViewport.x / dc2s_scale_h * scale_x) * screen_stretching;
				y_coef = 2.0f / dcViewport.y * (invertY ? -1 : 1);
			}
			trans_rot = glm::translate(glm::vec3(-1 + 2 * sidebarWidth / renderViewport.x, invertY ? 1 : -1, 0));

			normalMatrix = trans_rot
				* glm::scale(glm::vec3(x_coef, y_coef, 1.f))
				* normalMatrix;
			scissorMatrix = trans_rot
				* glm::scale(glm::vec3(x_coef * scissoring_scale_x, y_coef * scissoring_scale_y, 1.f))
				* scissorMatrix;
		}
		normalMatrix = glm::scale(glm::vec3(1, 1, 1 / config::ExtraDepthScale))
				* normalMatrix;

		glm::mat4 vp_trans = glm::translate(glm::vec3(1, 1, 0));
		if (renderingContext->isRTT)
		{
			vp_trans = glm::scale(glm::vec3(dcViewport.x / 2, dcViewport.y / 2, 1.f))
				* vp_trans;
		}
		else
		{
			vp_trans = glm::scale(glm::vec3(renderViewport.x / 2, renderViewport.y / 2, 1.f))
				* vp_trans;
		}
		viewportMatrix = vp_trans * normalMatrix;
		scissorMatrix = vp_trans * scissorMatrix;
}

void TransformMatrix::GetFramebufferScaling(bool scissor, float& scale_x, float& scale_y)
{
 scale_x = 1.f;
		scale_y = 1.f;

		if (!renderingContext->isRTT && !renderingContext->isRenderFramebuffer)
		{
			if (!scissor)
			{
				scale_x = fb_scale_x;
				scale_y = fb_scale_y;
			}
			if (SCALER_CTL.vscalefactor > 0x400)
			{
				// Interlace mode A (single framebuffer)
				if (SCALER_CTL.interlace == 0 && !scissor)
					scale_y *= roundf((float)SCALER_CTL.vscalefactor / 0x400);
				else if (SCALER_CTL.interlace == 1 && scissor)
					// Interlace mode B (alternating framebuffers)
					scale_y *= roundf((float)SCALER_CTL.vscalefactor / 0x400);
			}

			// VO pixel doubling is done after fb rendering/clipping
			// so it should be used for scissoring as well
			if (VO_CONTROL.pixel_double && !scissor)
				scale_x *= 0.5f;

			// the X Scaler halves the horizontal resolution but
			// before clipping/scissoring
			if (SCALER_CTL.hscale)
				scale_x *= 2.f;
		}
}
