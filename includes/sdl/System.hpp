#ifndef MINIASCAPE_SDL_SYSTEM
#define MINIASCAPE_SDL_SYSTEM
#include "Exceptions.hpp"
#include <SDL2/SDL.h>
#include <cstdint>

namespace sdl
{

class System
{
  public:

    System(const uint32_t flag) : flag_(flag)
    {
        auto result = SDL_Init(flag);
        if(result != 0)
            throw InitError(std::string(SDL_GetError()));
    }
    ~System() noexcept {SDL_Quit();}

    const uint32_t& flag() const {return flag_;}

  private:
    const uint32_t flag_;
};

}

#endif /* MINIASCAPE_SDL_SYSTEM */
