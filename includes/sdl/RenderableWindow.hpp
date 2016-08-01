#ifndef MINIASCAPE_SDL_RENDERABLE_WINDOW
#define MINIASCAPE_SDL_RENDERABLE_WINDOW
#include <SDL2/SDL.h>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <cstddef>

namespace sdl
{

using Point = SDL_Point;
using Color = SDL_Color;

class RenderableWindow
{
  public:
    using window_type    = SDL_Window;
    using window_ptr     = window_type*;
    using renderer_type  = SDL_Renderer;
    using renderer_ptr   = renderer_type*;

    RenderableWindow(const std::size_t x, const std::size_t y,
                     const unsigned int window_flag = 0)
        : x_(x), y_(y)
    {
        auto result = SDL_CreateWindowAndRenderer(
                x, y, window_flag, &window_, &renderer_);
        if(result != 0)
        {
            SDL_Log("could not create window and renderer: %s", SDL_GetError());
            throw std::runtime_error("create window & renderer error");
        }
    }
    ~RenderableWindow()
    {
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
    }

    std::pair<std::size_t, std::size_t> size() const
    {return std::make_pair(x_,y_);}

    void putpixel(const Point& p, const Color& c) const
    {
        SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
        SDL_RenderDrawPoint(renderer_, p.x, p.y);
        return;
    }

    void clear(const Color& c) const
    {
        SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
        SDL_RenderClear(renderer_);
        return;
    }

    void update() const
    {
        SDL_RenderPresent(this->renderer_);
        return;
    }

    template<typename Rep, typename Period>
    void wait(const std::chrono::duration<Rep, Period>& dur) const
    {
        using syscl = std::chrono::system_clock;
        syscl::time_point until = syscl::now() + dur;
        while(syscl::now() < until)
        {
            SDL_PumpEvents();
        }
        return;
    }

  private:
    std::size_t  x_;
    std::size_t  y_;
    window_ptr   window_;
    renderer_ptr renderer_;
};

}//sdl

#endif /* MINIASCAPE_SDL_RENDERABLE_WINDOW */
