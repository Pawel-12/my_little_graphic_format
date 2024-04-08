#include "Window.h"

namespace mlgf{
    Window::Window(unsigned int ww, unsigned int wh): WINDOWWIDTH(ww), WINDOWHEIGHT(wh){
        //Initialize SDL subsystems
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
            logSDLerror("SDL could not initialize! SDL_Error: ");
            return;
        }
        else{
            // Create window
            winSDL = SDL_CreateWindow( "MLGF", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);

            // if create window failed
            if(winSDL == nullptr){
                logSDLerror("Window could not be created! SDL_Error: ");
                return;
            }

            // create SDL renderer
            render = SDL_CreateRenderer(winSDL, -1, SDL_RENDERER_ACCELERATED/*|SDL_RENDERER_PRESENTVSYNC*/);

            // hide cursor
            SDL_ShowCursor(SDL_DISABLE);

            // if create renderer failed
            if (render == nullptr){
                logSDLerror("SDL_CreateRenderer Error:");
                return;
            }

            SDL_SetRenderDrawColor(render, 0, 0, 0, 255);         // Set renderer color
            SDL_RenderClear(render);                                            // Fill renderer with color
            SDL_RenderPresent(render);                                          // Show renderer on window

            //Initialize SDL_image subsystems
            if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
                logSDLerror("SDL_image could not initialize! IMG_INIT Error: ", IMG_GetError);
                return;
            }

            //Initialize SDL_ttf
            if(TTF_Init() < 0){
                logSDLerror("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError);
                return;
            }
        }
        return;
    }

    Window::~Window(){
        //Destroy window
        SDL_DestroyWindow(winSDL);
        winSDL = nullptr;

        // destroy renderer
        SDL_DestroyRenderer(render);
        render = nullptr;

        //Quit SDL IMG
        IMG_Quit();

        //Quit SDL subsystems
        SDL_Quit();

        TTF_Quit();
    }

    unsigned int Window::getWidth()const{
        return WINDOWWIDTH;
    }

    unsigned int Window::getHeight()const{
        return WINDOWHEIGHT;
    }

    SDL_Renderer * Window::getRend()const{
        return render;
    }

    SDL_Window * Window::getWin()const{
        return winSDL;
    }
}