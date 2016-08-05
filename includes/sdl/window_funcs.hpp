#ifndef MINIASCAPE_SDL_WINDOW_FUNCS
#define MINIASCAPE_SDL_WINDOW_FUNCS
#include <SDL2/SDL.h>

namespace sdl
{

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
class Window;

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Hide(const Window<T_smart_ptr>& win)
{
    return SDL_HideWindow(win.get());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Maximize(const Window<T_smart_ptr>& win)
{
    return SDL_MaximizeWindow(win.get());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Minimize(const Window<T_smart_ptr>& win)
{
    return SDL_MinimizeWindow(win.get());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Restore(const Window<T_smart_ptr>& win)
{
    return SDL_RestoreWindow(win.get());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Raise(const Window<T_smart_ptr>& win)
{
    return SDL_RaiseWindow(win.get());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Show(const Window<T_smart_ptr>& win)
{
    return SDL_ShowWindow(win.get());
}


// setter
template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void SetFullscreen(const Window<T_smart_ptr>& win, const Uint32 flags)
{
    return SDL_SetWindowFullscreen(win.get(), flags);
}

// getter
template<template<typename Tp_, typename Dp_>class T_smart_ptr>
Uint32 GetFlags(const Window<T_smart_ptr>& win)
{
    return SDL_GetWindowFlags(win.get());
}

}//sdl

#endif /* MINIASCAPE_SDL_WINDOW_FUNCS */
