#ifndef MINIASCAPE_STEPPER
#define MINIASCAPE_STEPPER
#include "Space.hpp"
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
    using space_type  = Space<traits_type>;

    static time_type step(space_type& space, const rule_type& rule);
};

template<typename T_traits>
typename Stepper<T_traits>::time_type
Stepper<T_traits>::step(space_type& space, const rule_type& rule)
{
    for(auto cell = make_zip(space.world().cbegin(),space.temp().begin());
            cell != make_zip(space.world().cend(),  space.temp().end()); ++cell)
        *get<1>(cell) = rule.step(**get<0>(cell));

    for(auto cell = make_zip(space.world().begin(), space.temp().begin());
            cell != make_zip(space.world().end(),   space.temp().end()); ++cell)
        (*get<0>(cell))->state = *get<1>(cell);

    return rule.delta_t();
}

}

#endif /* MINIASCAPE_STEPPER */
