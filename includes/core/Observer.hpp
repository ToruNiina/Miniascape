#ifndef MINIASCAPE_OBSERVER
#define MINIASCAPE_OBSERVER
#include "World.hpp"
#include <iostream>

namespace miniascape
{

template<typename T_traits>
class Observer
{
  public:
    using traits_type = T_traits;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using time_type   = typename traits_type::time_type;
    using world_type  = World<traits_type>;

  public:
    Observer() = default;
    ~Observer() = default;

    virtual void observe(const time_type& t, const world_type& space) = 0;
};


template<typename T_traits>
class DefaultObserver : public Observer<T_traits>
{
  public:
    using base_type   = Observer<T_traits>;
    using state_type  = typename base_type::state_type;
    using cell_type   = typename base_type::cell_type;
    using time_type   = typename base_type::time_type;
    using world_type  = typename base_type::world_type;

  public:
    DefaultObserver() = default;
    ~DefaultObserver() = default;

    void observe(const time_type& t, const world_type& space) override;
};

template<typename T_traits>
void DefaultObserver<T_traits>::observe(
        const time_type& t, const world_type& world)
{
    std::cout << "time: " << t << std::endl;
    for(auto iter = world.cbegin(); iter != world.cend(); ++iter)
        std::cout << (*iter)->state << " ";
    std::cout << std::endl;
    return;
}

}

#endif /* MINIASCAPE_OBSERVER */
