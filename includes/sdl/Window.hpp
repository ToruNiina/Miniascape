#ifndef MINIASCAPE_SDL_WINDOW
#define MINIASCAPE_SDL_WINDOW
#include <SDL2/SDL.h>
#include <string>
#include "Exceptions.hpp"

namespace sdl
{

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
class Window
{
  public:
    template<typename Tp_, typename Dp_>
    using smart_ptr_type = T_smart_ptr<Tp_, Dp_>;
    using window_type    = SDL_Window;
    using window_ptr     = window_type*;
    using window_ref     = window_type&;
    using deleter_type   = decltype(&SDL_DestroyWindow);
    using resource_type  = smart_ptr_type<window_type, deleter_type>;

  public:
    Window(): window_(nullptr, &SDL_DestroyWindow){}
    ~Window() = default;

    explicit Window(window_ptr win) : window_(win, &SDL_DestroyWindow){}

    Window(const std::string& title, int pos_x, int pos_y, int width,
           int height, Uint32 flags)
        : window_(SDL_CreateWindow(title.c_str(), pos_x, pos_y,
                                   width, height, flags), &SDL_DestroyWindow)
    {
        if(window_.get() == nullptr)
            throw InitError("Window initialization failed: " +
                            std::string(SDL_GetError()));
    }

    void reset(window_ptr ptr) noexcept {window_.reset(ptr);}
    void swap(window_ptr& ptr) noexcept {window_.swap(ptr);}

    window_ptr get()        const noexcept {return window_.get();}
    window_ref operator*()  const noexcept {return *window_;}
    window_ptr operator->() const noexcept {return window_;}

    operator bool() const {return window_;}

  private:

    resource_type window_;
};

}//sdl

#endif /* MINIASCAPE_SDL_WINDOW */
