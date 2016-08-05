#ifndef MINIASCAPE_SDL_RENDERER
#define MINIASCAPE_SDL_RENDERER
#include <SDL2/SDL.h>
#include <string>
#include "Exceptions.hpp"

namespace sdl
{

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
class Window;

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
class Renderer
{
  public:
    template<typename Tp_, typename Dp_>
    using smart_ptr_type = T_smart_ptr<Tp_, Dp_>;
    using renderer_type  = SDL_Renderer;
    using renderer_ptr   = renderer_type*;
    using renderer_ref   = renderer_type&;
    using deleter_type   = decltype(&SDL_DestroyRenderer);
    using resource_type  = smart_ptr_type<renderer_type, deleter_type>;

  public:
    Renderer(): renderer_(nullptr, SDL_DestroyRenderer){}
    ~Renderer() = default;

    explicit Renderer(renderer_ptr ren) : renderer_(ren, SDL_DestroyRenderer){}

    Renderer(SDL_Window* win, int index, Uint32 flags)
        : renderer_(SDL_CreateRenderer(win, index, flags), SDL_DestroyRenderer)
    {
        if(renderer_.get() == nullptr)
            throw InitError("Renderer initalization failed: " +
                            std::string(SDL_GetError()));
    }

    template<template<typename Tp_, typename Dp_>class T_ptr>
    Renderer(const Window<T_ptr>& win, int index, Uint32 flags)
        : renderer_(SDL_CreateRenderer(win.get(), index, flags),
                    SDL_DestroyRenderer)
    {
        if(renderer_.get() == nullptr)
            throw InitError("Renderer initalization failed: " +
                            std::string(SDL_GetError()));
    }

    void reset(renderer_ptr ptr) noexcept {renderer_.reset(ptr);}
    void swap(renderer_ptr& ptr) noexcept {renderer_.swap(ptr);}

    renderer_ptr get()        const noexcept {return renderer_.get();}
    renderer_ref operator*()  const noexcept {return *renderer_;}
    renderer_ptr operator->() const noexcept {return renderer_;}

    operator bool() const {return renderer_;}

  private:

    resource_type renderer_;
};

}//sdl

#endif /* MINIASCAPE_SDL_RENDERER */
