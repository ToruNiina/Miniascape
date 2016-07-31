#include "Observer.hpp"
#include "SquareLattice.hpp"
#include "sdl/RenderableWindow.hpp"

namespace miniascape
{

template<typename T_traits>
class GraphicalObserver : public Observer<T_traits>
{
  public:
    using base_type   = Observer<T_traits>;
    using state_type  = typename base_type::state_type;
    using cell_type   = typename base_type::cell_type;
    using time_type   = typename base_type::time_type;
    using world_type  = typename base_type::world_type;

  public:
    GraphicalObserver(const std::size_t x, const std::size_t y)
        : window_(x, y)
    {}
    ~GraphicalObserver() = default;

    void observe(const time_type& t, const world_type& world) override;

  private:
    sdl::RenderableWindow window_;
};

template<typename T_traits>
void GraphicalObserver<T_traits>::observe(
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
    return;
}





}
