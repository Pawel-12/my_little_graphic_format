#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace mlgf{
    inline void logSDLerror(const std::string & msg,  const char * (* const errFunc)() = SDL_GetError, std::ostream & os = std::cerr){
        os << msg << " error: " << errFunc() << '\n';
    }
}