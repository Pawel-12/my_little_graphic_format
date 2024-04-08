#include "Image.h"

namespace mlgf{
    Image::Image(const char * path, SDL_Renderer * render) {
        textureSDL = IMG_LoadTexture(render, path);

        if (textureSDL == nullptr) {
            logSDLerror("IMG_LoadTexture: ", IMG_GetError);

            //If nullptr try loading image using SDL_Surface
            SDL_Surface * sprite = IMG_Load(path);

            if (sprite == nullptr) {
                logSDLerror("SDL_Surface = IMG_Load(imgpath) Error: ", IMG_GetError);
                return;
            }

            // Upload surface to renderer, and then, free the surface
            textureSDL = SDL_CreateTextureFromSurface(render, sprite);

            SDL_FreeSurface(sprite);

            if (textureSDL == nullptr) {
                logSDLerror("SDL_CreateTextureFromSurface Error: ");
                return;
            }
        }

        int w,h;
        SDL_QueryTexture(textureSDL, nullptr, nullptr, &w, &h);

        textureWidth = w;
        textureHeight = h;

        rect = {0,0,w,h};
    }

    Image::Image(TTF_Font * font, const char * text, const SDL_Color & color, SDL_Renderer * render) {
        SDL_Surface * textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text, color, 0);

        if (textSurface == nullptr) {
            logSDLerror("Unable to render text surface! SDL_ttf Error: ",TTF_GetError);
            return;
        }
        else {
            textureSDL = SDL_CreateTextureFromSurface(render, textSurface);

            SDL_FreeSurface(textSurface);

            if (textureSDL == nullptr) {
                logSDLerror("SDL_CreateTextureFromSurface Error: ");
                return;
            }

            int w,h;
            SDL_QueryTexture(textureSDL, nullptr, nullptr, &w, &h);

            textureWidth = w;
            textureHeight = h;

            rect = {0,0,w,h};
        }
    }

    Image::~Image() {
        SDL_DestroyTexture(textureSDL);
        textureSDL = nullptr;
    }

    SDL_Texture * Image::getTexture() {
        return textureSDL;
    }

    void Image::draw(SDL_Renderer * render) const {
        if(textureSDL == nullptr)
            return;

        SDL_RenderCopy(render, textureSDL, nullptr, &rect);
    }

    void Image::setXY(float x, float y) {
        rect.x = x;
        rect.y = y;
    }

    void Image::moveXY(float x, float y) {
        rect.x += x;
        rect.y += y;
    }

    void Image::scale(float scale) {
        rect.w =  textureWidth * scale;
        rect.h = textureHeight * scale;
    }

    float Image::getWidth() const {
        return rect.w;
    }

    float Image::getHeight() const {
        return rect.h;
    }
}