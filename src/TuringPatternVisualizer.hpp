#include "core/Observer.hpp"
#include "core/SquareLattice.hpp"
#include "sdl/Window.hpp"
#include "sdl/Renderer.hpp"
#include "sdl/create_window_and_renderer.hpp"
#include "sdl/window_funcs.hpp"
#include "sdl/renderer_funcs.hpp"
#include "sdl/event_funcs.hpp"
#include "sdl/System.hpp"
#include "sdl/Definition.hpp"
#include <memory>
#include <chrono>
#include <cmath>

namespace miniascape
{

template<typename T_traits>
class TuringPatternVisualizer : public Observer<T_traits>
{
  public:
    using base_type   = Observer<T_traits>;
    using state_type  = typename base_type::state_type;
    using cell_type   = typename base_type::cell_type;
    using time_type   = typename base_type::time_type;
    using world_type  = typename base_type::world_type;
    using window_type = sdl::Window<std::unique_ptr>;
    using renderer_type = sdl::Renderer<std::unique_ptr>;

  public:
    TuringPatternVisualizer(const std::size_t x, const std::size_t y)
        : system_(SDL_INIT_VIDEO),
          window_("Gray-Scott reaction diffusion model", 0, 0, x, y,
          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
          renderer_(window_, -1, SDL_RENDERER_ACCELERATED)
    {
        const sdl::Color black{0, 0, 0, 0};
        sdl::SetDrawColor(this->renderer_, black);
        sdl::Present(this->renderer_);
    }
    ~TuringPatternVisualizer() = default;

    void observe(const time_type& t, const world_type& world) override;
    bool closed() const {return closed_;}

  private:
    sdl::Color coloring(const double u) const;

  private:
    bool closed_ = false;
    sdl::System   system_;
    window_type   window_;
    renderer_type renderer_;
};

template<typename T_traits>
void TuringPatternVisualizer<T_traits>::observe(
        const time_type& t, const world_type& world)
{
    const auto size = sdl::GetSize(this->window_);

    SquareLattice<T_traits> const& sql =
        dynamic_cast<SquareLattice<T_traits> const&>(world);

    double u_min = std::numeric_limits<double>::max();
    double u_max = std::numeric_limits<double>::min();
    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        const double u_cell = sql.access(x,y)->state.u;
        if(u_cell > u_max) u_max = u_cell;
        if(u_cell < u_min) u_min = u_cell;
    }

    const double standardize_constant = (u_max - u_min > 0.) ? 1.0 / (u_max - u_min) : 0.;
    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        const double u_color = (sql.access(x,y)->state.u - u_min) *
                                standardize_constant;
        sdl::Point pos{x, y};
        sdl::SetDrawColor(this->renderer_, coloring(u_color));
        sdl::DrawPoint(this->renderer_, pos);
    }

    sdl::Present(this->renderer_);

    using syscl = std::chrono::system_clock;
    const syscl::time_point until = syscl::now() + std::chrono::microseconds(10);
    sdl::Event ev;
    while(syscl::now() < until)
    {
        if(sdl::PollEvent(ev))
        {
            if(ev.type == SDL_QUIT)
                closed_ = true;
            else if(ev.type == SDL_WINDOWEVENT &&
                    ev.window.event == SDL_WINDOWEVENT_MAXIMIZED)
                sdl::Maximize(window_);
            break;
        }
    }
    return;
}

template<typename T_traits>
sdl::Color TuringPatternVisualizer<T_traits>::coloring(const double u) const
{
    const std::size_t index = static_cast<std::size_t>(u * 7.);
    switch(index)
    {
        case  0: return sdl::Color{128,   0, 128};
        case  1: return sdl::Color{  0,   0, 255};
        case  2: return sdl::Color{  0, 255, 255};
        case  3: return sdl::Color{  0, 128,   0};
        case  4: return sdl::Color{255, 255,   0};
        case  5: return sdl::Color{255, 165,   0};
        case  6: return sdl::Color{255,   0,   0};
        default: return sdl::Color{255, 255, 255};
    }
}


}//miniascape
