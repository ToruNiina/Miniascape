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
class IsingModelVisualizer : public Observer<T_traits>
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
    IsingModelVisualizer(const std::size_t x, const std::size_t y)
        : system_(SDL_INIT_VIDEO), window_("Ising model", 0, 0, x, y,
          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
          renderer_(window_, -1, SDL_RENDERER_ACCELERATED)
    {
        const sdl::Color black{0, 0, 0, 0};
        sdl::SetDrawColor(this->renderer_, black);
        sdl::Present(this->renderer_);
    }
    ~IsingModelVisualizer() = default;

    void observe(const time_type& t, const world_type& world) override;
    bool closed() const {return closed_;}

  private:
    bool closed_ = false;
    sdl::System           system_;
    window_type   window_;
    renderer_type renderer_;
};

template<typename T_traits>
void IsingModelVisualizer<T_traits>::observe(
        const time_type& t, const world_type& world)
{
    const auto size = sdl::GetSize(this->window_);
    const sdl::Color up{255, 255, 255, 0};
    const sdl::Color down{0,   0,   0, 0};
    sdl::SetDrawColor(this->renderer_, down);
    sdl::Clear(renderer_);

    SquareLattice<T_traits> const& sql =
        dynamic_cast<SquareLattice<T_traits> const&>(world);

    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        if(sql.access(x, y)->state)
        {
            sdl::Point pos{x, y};
            sdl::SetDrawColor(this->renderer_, up);
            sdl::DrawPoint(this->renderer_, pos);
        }
    }
    sdl::Present(this->renderer_);
    using syscl = std::chrono::system_clock;
    const syscl::time_point until = syscl::now() + std::chrono::milliseconds(1);
    sdl::Event ev;
    while(syscl::now() < until)
    {
        if(sdl::PollEvent(ev))
        {
            switch(ev.type)
            {
                case SDL_QUIT:
                {
                    closed_ = true; break;
                }
                case SDL_WINDOWEVENT:
                {
                    switch(ev.window.event)
                    {
                      case SDL_WINDOWEVENT_MAXIMIZED:
                        sdl::Maximize(window_); break;
                    }
                }
            }
        }
    }
    return;
}



}//miniascape
