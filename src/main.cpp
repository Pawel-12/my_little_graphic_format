#include <SDL2/SDL.h>

#include "Window.h"
#include "Image.h"

int main(int argc, char* argv[]) {
    const unsigned int WINDOWWIDTH = 1920;
    const unsigned int WINDOWHEIGHT = 1080;

    mlgf::Window window(WINDOWWIDTH,WINDOWHEIGHT);
    mlgf::Image img("../data/test.png", window.getRend());

    TTF_Font * font = TTF_OpenFont("../data/ChakraPetch-Bold.ttf",200);
    mlgf::Image text(font,"MLGF",SDL_Color(0,128,128,255),window.getRend());

    text.setXY((WINDOWWIDTH - text.getWidth())/2,0);

    auto start_time = SDL_GetTicks();
    auto temp = SDL_GetTicks();

    SDL_Event e;
    bool quit = false;

    float scale = 0.1;
    img.scale(scale);

    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                quit = true;
            else if(e.type == SDL_MOUSEWHEEL)
                img.scale(scale += (e.wheel.y * 0.01));
        }

        img.draw(window.getRend());
        text.draw(window.getRend());

        SDL_RenderPresent(window.getRend());
        SDL_RenderClear(window.getRend());

        int x,y;
        SDL_GetMouseState(&x, &y);
        img.setXY(x,y);

        temp = SDL_GetTicks();
        if((1000/60) > (SDL_GetTicks() - start_time)) {                                             // 60 FPS
            SDL_Delay((1000/60)-(SDL_GetTicks()-start_time));
        }

        start_time = temp;
    }

    TTF_CloseFont(font);
    return 0;
}
