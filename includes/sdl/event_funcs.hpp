#ifndef MINIASCAPE_SDL_EVENT_FUNCS
#define MINIASCAPE_SDL_EVENT_FUNCS
#include <SDL2/SDL.h>
#include "Exceptions.hpp"
#include "Definition.hpp"

namespace sdl
{

bool PollEvent(Event& ev)
{
    return (SDL_PollEvent(&ev) == 1);
}

}

#endif /* MINIASCAPE_SDL_EVENT_FUNCS */
