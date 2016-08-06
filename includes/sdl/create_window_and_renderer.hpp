#ifndef MINIASCAPE_SDL_CREATE_WINDOW_AND_RENDERER
#define MINIASCAPE_SDL_CREATE_WINDOW_AND_RENDERER
#include "Window.hpp"
#include "Renderer.hpp"
#include <utility>

namespace sdl
{


template<template<typename Tp_, typename Dp_>class T_window_ptr,
         template<typename Tp_, typename Dp_>class T_renderer_ptr>
std::pair<Window<T_window_ptr>, Renderer<T_renderer_ptr>>
CreateWindowAndRenderer(int width, int height, Uint32 window_flags = 0)
{
    Window<T_window_ptr>     window;
    Renderer<T_renderer_ptr> renderer;
    if(SDL_CreateWindowAndRenderer(width, height, window_flags,
                &(window.get()), &(renderer.get())) != 0)
        throw InitError(SDL_GetError());
    return std::make_pair(window, renderer);
}




} //sdl

#endif /* MINIASCAPE_SDL_CREATE_WINDOW_AND_RENDERER */
