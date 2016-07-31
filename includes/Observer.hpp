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

    virtual void observe(std::ostream& os, const time_type& t,
                         const world_type& space);
};

template<typename T>
void Observer<T>::observe(std::ostream& os, const time_type& t,
                          const world_type& world)
{
    os << "time: " << t << std::endl;
    for(auto iter = world.cbegin(); iter != world.cend(); ++iter)
    {
        os << (*iter)->state << " ";
    }
    return;
}

}

#endif /* MINIASCAPE_OBSERVER */
