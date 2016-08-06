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

namespace miniascape
{

template<typename T_traits>
class ConwaysLifeGameVisualizer : public Observer<T_traits>
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
    ConwaysLifeGameVisualizer(const std::size_t x, const std::size_t y)
        : system_(SDL_INIT_VIDEO), window_("Conway's Game of Life", 0, 0, x, y,
          SDL_WINDOW_SHOWN), renderer_(window_, -1, SDL_RENDERER_ACCELERATED)
    {
        const sdl::Color black{0, 0, 0, 0};
        sdl::SetDrawColor(this->renderer_, black);
        sdl::Present(this->renderer_);
    }
    ~ConwaysLifeGameVisualizer() = default;

    void observe(const time_type& t, const world_type& world) override;
    bool closed() const {return closed_;}

  private:
    bool          closed_ = false;
    sdl::System   system_;
    window_type   window_;
    renderer_type renderer_;
};

template<typename T_traits>
void ConwaysLifeGameVisualizer<T_traits>::observe(
        const time_type& t, const world_type& world)
{
    const auto size = sdl::GetSize(this->window_);
    const sdl::Color green{0, 255, 0, 0};
    const sdl::Color black{0,   0, 0, 0};
    sdl::SetDrawColor(this->renderer_, black);
    sdl::Clear(renderer_);
    SquareLattice<T_traits> const& sql =
        dynamic_cast<SquareLattice<T_traits> const&>(world);

    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        if(sql(x, y)->state)
        {
            sdl::Point pos{x, y};
            sdl::SetDrawColor(this->renderer_, green);
            sdl::DrawPoint(this->renderer_, pos);
        }
    }
    sdl::Present(this->renderer_);

    using syscl = std::chrono::system_clock;
    const syscl::time_point until = syscl::now() + std::chrono::milliseconds(1);
    sdl::Event ev;
    while(syscl::now() < until)
    {
        if(sdl::PollEvent(ev) && ev.type == SDL_QUIT)
            closed_ = true;
    }
    return;
}

}
