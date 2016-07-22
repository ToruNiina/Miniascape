#ifndef MINIASCAPE_STEPPER
#define MINIASCAPE_STEPPER
#include "Space.hpp"
#include "zip_iterator.hpp"

namespace miniascape
{

template<typename T_traits>
class Stepper
{
  public:
    using traits_type = T_traits;
    using world_type  = typename traits_type::world_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using rule_type   = typename traits_type::rule_type;

    static void step(Space<traits_type>& space);
};

template<typename T_traits>
void Stepper<T_traits>::step(Space<traits_type>& space)
{
    for(auto cell = make_zip(space.world().cbegin(),space.temp().begin());
            cell != make_zip(space.world().cend(),  space.temp().end()); ++cell)
        **get<1>(cell) = rule_type::step(**get<0>(cell));

    for(auto cell = make_zip(space.world().begin(), space.temp().begin());
            cell != make_zip(space.world().end(),   space.temp().end()); ++cell)
        (*get<0>(cell))->state = std::move(**get<1>(cell));

    return;
}


}

#endif /* MINIASCAPE_STEPPER */
