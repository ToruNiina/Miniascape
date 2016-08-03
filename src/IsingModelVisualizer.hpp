#include "core/Observer.hpp"
#include "core/SquareLattice.hpp"
#include "sdl/RenderableWindow.hpp"
#include "sdl/System.hpp"

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

  public:
    IsingModelVisualizer(const std::size_t x, const std::size_t y)
        : system_(SDL_INIT_VIDEO), window_(x, y)
    {
        const sdl::Color black{0, 0, 0, 0};
        window_.clear(black);
        window_.update();
    }
    ~IsingModelVisualizer()
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
void IsingModelVisualizer<T_traits>::observe(
        const time_type& t, const world_type& world)
{
    const auto size = window_.size();
    const sdl::Color up{255, 255, 255, 0};
    const sdl::Color down{0,   0,   0, 0};
    window_.clear(down);

    SquareLattice<T_traits> const& sql =
        dynamic_cast<SquareLattice<T_traits> const&>(world);

    for(int x = 0; x < size.first; ++x)
    for(int y = 0; y < size.second; ++y)
    {
        sdl::Point pos{x, y};
        if(sql(x, y)->state.val)
            window_.putpixel(pos, up);
    }
    window_.update();
    window_.wait(std::chrono::microseconds(10));
    return;
}



}//miniascape
