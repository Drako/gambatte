//
//   Copyright (C) 2007 by sinamas <sinamas at users.sourceforge.net>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License version 2 for more details.
//
//   You should have received a copy of the GNU General Public License
//   version 2 along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.
//

#include "sdlblitter.h"
#include "scalebuffer.h"
#include <SDL.h>

struct SdlBlitter::SurfaceDeleter {
	static void del(SDL_Surface *s) { SDL_FreeSurface(s); }
};

SdlBlitter::SdlBlitter(unsigned inwidth, unsigned inheight,
                       int scale, bool startFull)
: screen_ (SDL_CreateWindow("Gambatte SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, inwidth * scale, inheight * scale, startFull ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0))
, screen_surface_(SDL_GetWindowSurface(screen_))
, surface_(screen_surface_ && scale > 1
           ? SDL_CreateRGBSurface(SDL_SWSURFACE, inwidth, inheight,
                                  screen_surface_->format->BitsPerPixel, 0, 0, 0, 0)
           : nullptr) {
}


SdlBlitter::~SdlBlitter() {
}

SdlBlitter::PixelBuffer SdlBlitter::inBuffer() const {
	PixelBuffer pb = { 0, 0, RGB32 };

	if (SDL_Surface *s = surface_ ? surface_.get() : screen_surface_) {
		pb.pixels = static_cast<char *>(s->pixels);
		pb.format = s->format->BitsPerPixel == 16 ? RGB16 : RGB32;
		pb.pitch = s->pitch / s->format->BytesPerPixel;
	}

	return pb;
}

template<typename T>
inline void SdlBlitter::swScale() {
	T const *src = reinterpret_cast<T *>(static_cast<char *>(surface_->pixels));
	T       *dst = reinterpret_cast<T *>(static_cast<char *>(screen_surface_->pixels));
	scaleBuffer(src, dst, surface_->w, surface_->h,
	            screen_surface_->pitch / screen_surface_->format->BytesPerPixel, screen_surface_->h / surface_->h);
}

void SdlBlitter::draw() {
	if (surface_ && screen_surface_) {
		if (surface_->format->BitsPerPixel == 16)
			swScale<Uint16>();
		else
			swScale<Uint32>();
	}
}

void SdlBlitter::present() {
	if (!screen_surface_)
		return;

    SDL_UpdateWindowSurface(screen_);
}

void SdlBlitter::toggleFullScreen() {
	if (screen_) {
	    auto const flags = SDL_GetWindowFlags(screen_);
	    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP)
	        SDL_SetWindowFullscreen(screen_, 0);
	    else
	        SDL_SetWindowFullscreen(screen_, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}
