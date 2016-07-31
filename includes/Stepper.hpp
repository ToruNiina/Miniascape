#ifndef MINIASCAPE_STEPPER
#define MINIASCAPE_STEPPER
#include "World.hpp"
#include "Rule.hpp"
#include "zip_iterator.hpp"

namespace miniascape
{

template<typename T_traits>
class Stepper
{
  public:
    using traits_type = T_traits;
    using time_type   = typename traits_type::time_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using rule_type   = RuleBase<traits_type>;
    using world_type  = World<traits_type>;

    static time_type step(world_type& world, const rule_type& rule);
};

template<typename T_traits>
typename Stepper<T_traits>::time_type
Stepper<T_traits>::step(world_type& world, const rule_type& rule)
{
    std::vector<state_type> temp(world.size());

    for(auto cell = make_zip(world.cbegin(), temp.begin());
            cell != make_zip(world.cend(),   temp.end()); ++cell)
        *get<1>(cell) = rule.step(**get<0>(cell));

    for(auto cell = make_zip(world.begin(), temp.begin());
            cell != make_zip(world.end(),   temp.end()); ++cell)
        (*get<0>(cell))->state = *get<1>(cell);

    return rule.delta_t();
}

}

#endif /* MINIASCAPE_STEPPER */
