#include "core/Observer.hpp"
#include "core/SquareLattice.hpp"
#include "sdl/RenderableWindow.hpp"
#include "sdl/System.hpp"

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

  public:
    ConwaysLifeGameVisualizer(const std::size_t x, const std::size_t y)
        : system_(SDL_INIT_VIDEO), window_(x, y)
    {
        const sdl::Color black{0, 0, 0, 0};
        window_.clear(black);
        window_.update();
    }
    ~ConwaysLifeGameVisualizer()
    {
        window_.~RenderableWindow();
        system_.~System();
    }

    void observe(const time_type& t, const world_type& world) override;

  private:
    sdl::System           system_;
    sdl::RenderableWindow window_;
};

template<typename T_traits>
void ConwaysLifeGameVisualizer<T_traits>::observe(
        const time_type& t, const world_type& world)
{
    const auto size = window_.size();
    const sdl::Color green{0, 255, 0, 0};
    const sdl::Color black{0,   0, 0, 0};
    window_.clear(black);
    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        sdl::Point pos{x, y};
        if((dynamic_cast<SquareLattice<T_traits> const&>(world)(x, y))->state)
            window_.putpixel(pos, green);
    }
    window_.update();
    window_.wait(std::chrono::microseconds(10));
    return;
}

}
