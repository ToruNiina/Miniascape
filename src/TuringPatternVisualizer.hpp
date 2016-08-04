#include "core/Observer.hpp"
#include "core/SquareLattice.hpp"
#include "sdl/RenderableWindow.hpp"
#include "sdl/System.hpp"
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

  public:
    TuringPatternVisualizer(const std::size_t x, const std::size_t y)
        : system_(SDL_INIT_VIDEO), window_(x, y)
    {
        const sdl::Color black{0, 0, 0, 0};
        window_.clear(black);
        window_.update();
    }
    ~TuringPatternVisualizer()
    {
        window_.~RenderableWindow();
        system_.~System();
    }

    void observe(const time_type& t, const world_type& world) override;

  private:
    sdl::Color coloring(const double u) const;

  private:
    sdl::System           system_;
    sdl::RenderableWindow window_;
};

template<typename T_traits>
void TuringPatternVisualizer<T_traits>::observe(
        const time_type& t, const world_type& world)
{
    const auto size = window_.size();

    SquareLattice<T_traits> const& sql =
        dynamic_cast<SquareLattice<T_traits> const&>(world);

    double u_min = std::numeric_limits<double>::max();
    double u_max = std::numeric_limits<double>::min();
    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        const double u_cell = sql(x,y)->state.u;
        if(u_cell > u_max) u_max = u_cell;
        if(u_cell < u_min) u_min = u_cell;
    }

    const double standardize_constant = 1.0 / (u_max - u_min);
    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        const double u_cell = sql(x,y)->state.u;
        const double u_color = (u_cell - u_min) * standardize_constant;

        sdl::Point pos{x, y};
        sdl::Color cell_color = coloring(u_color);
        window_.putpixel(pos, cell_color);
    }

    window_.update();
    window_.wait(std::chrono::microseconds(10));
    return;
}

template<typename T_traits>
sdl::Color TuringPatternVisualizer<T_traits>::coloring(const double u) const
{
    if(u < 1.0/7.0)
        return sdl::Color{128,   0, 128};
    else if(u < 2.0/7.0)
        return sdl::Color{  0,   0, 255};
    else if(u < 3.0/7.0)
        return sdl::Color{  0, 255, 255};
    else if(u < 4.0/7.0)
        return sdl::Color{  0, 128,   0};
    else if(u < 5.0/7.0)
        return sdl::Color{255, 255,   0};
    else if(u < 6.0/7.0)
        return sdl::Color{255, 165,   0};
    else
        return sdl::Color{255,   0,   0};
}


}//miniascape
