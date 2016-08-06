#ifndef MINIASCAPE_SDL_RENDERER_FUNCS
#define MINIASCAPE_SDL_RENDERER_FUNCS
#include "Renderer.hpp"
#include "Definition.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <array>

namespace sdl
{

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Present(const Renderer<T_smart_ptr>& ren)
{
    return SDL_RenderPresent(ren.get());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void Clear(const Renderer<T_smart_ptr>& ren)
{
    if(SDL_RenderClear(ren.get()) == 0) return ;
    else throw RendererError(SDL_GetError());
}

// DrawPoint, DrawPoints {{{
template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void DrawPoint(const Renderer<T_smart_ptr>& ren, Point p)
{
    if(SDL_RenderDrawPoint(ren.get(), p.x, p.y) == 0) return;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void DrawPoints(const Renderer<T_smart_ptr>& ren,
                const std::vector<Point>& points)
{
    if(points.size() == 0) return;
    if(SDL_RenderDrawPoints(ren.get(), points.data(), points.size()) == 0)
        return;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr, std::size_t N>
void DrawPoints(const Renderer<T_smart_ptr>& ren,
                const std::array<Point, N>& points)
{
    static_assert(N > 0, "array should have at least one element");
    if(SDL_RenderDrawPoints(ren.get(), points.data(), N) == 0)
        return;
    else throw RendererError(SDL_GetError());
}
// }}}

// DrawLine, DrawLines {{{
template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void DrawLine(const Renderer<T_smart_ptr>& ren, Point begin, Point end)
{
    if(SDL_RenderDrawLine(ren.get(), begin.x, begin.y, end.x, end.y) == 0)
        return ;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void DrawLine(const Renderer<T_smart_ptr>& ren,
              const std::pair<Point, Point>& range)
{
    if(SDL_RenderDrawLine(ren.get(), range.first.x, range.first.y,
                          range.second.x, range.second.y) == 0) return ;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void DrawLines(const Renderer<T_smart_ptr>& ren,
               const std::vector<Point>& points)
{
    if(SDL_RenderDrawLines(ren.get(), points.data(), points.size()) == 0)
        return ;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr, std::size_t N>
void DrawLines(const Renderer<T_smart_ptr>& ren,
               const std::array<Point, N>& points)
{
    if(SDL_RenderDrawLines(ren.get(), points.data(), N) == 0) return ;
    else throw RendererError(SDL_GetError());
}

// }}}

// DrawRect, DrawRects {{{

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void DrawRect(const Renderer<T_smart_ptr>& ren, const Rect& rect)
{
    if(SDL_RenderDrawRect(ren.get(), &rect) == 0) return ;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void DrawRects(const Renderer<T_smart_ptr>& ren, const std::vector<Rect>& rects)
{
    if(SDL_RenderDrawRect(ren.get(), rects.data(), rects.size()) == 0) return;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr, std::size_t N>
void DrawRects(const Renderer<T_smart_ptr>& ren, const std::array<Rect, N>& rects)
{
    if(SDL_RenderDrawRect(ren.get(), rects.data(), N) == 0) return;
    else throw RendererError(SDL_GetError());
}

// }}}

// FillRect, FillRects {{{
template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void FillRect(const Renderer<T_smart_ptr>& ren, const Rect& rect)
{
    if(SDL_RenderFillRect(ren.get(), &rect) == 0) return;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void FillRects(const Renderer<T_smart_ptr>& ren, const std::vector<Rect>& rects)
{
    if(SDL_RenderFillRects(ren.get(), rects.data(), rects.size()) == 0) return;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr, std::size_t N>
void FillRects(const Renderer<T_smart_ptr>& ren,
               const std::array<Rect, N>& rects)
{
    if(SDL_RenderFillRects(ren.get(), rects.data(), N) == 0) return;
    else throw RendererError(SDL_GetError());
}

// }}}

// Get&Set DrawColor {{{
template<template<typename Tp_, typename Dp_>class T_smart_ptr>
void SetDrawColor(const Renderer<T_smart_ptr>& ren, const Color& col)
{
    if(SDL_SetRenderDrawColor(ren.get(), col.r, col.g, col.b, col.a) == 0)
        return;
    else throw RendererError(SDL_GetError());
}

template<template<typename Tp_, typename Dp_>class T_smart_ptr>
Color GetDrawColor(const Renderer<T_smart_ptr>& ren)
{
    Color col;
    if(SDL_GetRenderDrawColor(ren.get(),
                &(col.r), &(col.g), &(col.b), &(col.a)) == 0) return col;
    else throw RendererError(SDL_GetError());
}
// }}}

template<template<typename Tp_, typename Dp_>class T_info_ptr,
         template<typename Tp_, typename Dp_>class T_renderer_ptr>
T_info_ptr<RendererInfo, std::default_delete<RendererInfo>>
GetRendererInfo(const Renderer<T_renderer_ptr>& ren)
{
    T_info_ptr<RendererInfo, std::default_delete<RendererInfo>>
        info(new RendererInfo);
    if(SDL_GetRendererInfo(ren.get(), info.get()) != 0)
        throw RendererError(SDL_GetError());
    else return info;
}

}//sdl

#endif /* MINIASCAPE_SDL_RENDERER_FUNCS */
