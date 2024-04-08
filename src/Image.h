#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "logSDLerror.h"

namespace mlgf {
    class Image {
    private:
        SDL_Texture * textureSDL = nullptr;
        SDL_Rect rect;
        float textureWidth = 0;
        float textureHeight = 0;
    public:
        Image(const char * path, SDL_Renderer * render);
        Image(TTF_Font * font, const char * text, const SDL_Color & color, SDL_Renderer * render);
        ~Image();
        SDL_Texture * getTexture();
        void draw(SDL_Renderer * render) const;
        void setXY(float x, float y);
        void moveXY(float x, float y);
        void scale(float scale);
        float getWidth() const;
        float getHeight() const;
    };
}