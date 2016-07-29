#ifndef MINIASCAPE_OBSERVER
#define MINIASCAPE_OBSERVER
#include "Space.hpp"
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
    using space_type  = Space<traits_type>;

  public:
    Observer() = default;
    ~Observer() = default;

    virtual void observe(std::ostream& os, const time_type& t,
                         const space_type& space);
};

template<typename T>
void Observer<T>::observe(std::ostream& os,
        const time_type& t, const space_type& space)
{
    os << "time: " << t << std::endl;
    for(auto iter = space.world().cbegin(); iter != space.world.cend(); ++iter)
    {
        os << (*iter)->state << " ";
    }
    return;
}

}

#endif /* MINIASCAPE_OBSERVER */
