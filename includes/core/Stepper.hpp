#ifndef MINIASCAPE_STEPPER
#define MINIASCAPE_STEPPER
#include "core/World.hpp"
#include "core/Rule.hpp"
#include "core/RandomNumberGenerator.hpp"
#include "util/zip_iterator.hpp"

namespace miniascape
{

template<typename T_traits>
class SynchronousStepper
{
  public:
    using traits_type = T_traits;
    using time_type   = typename traits_type::time_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using rule_type   = RuleBase<traits_type>;
    using world_type  = World<traits_type>;

    SynchronousStepper() = default;
   ~SynchronousStepper() = default;
    time_type step(world_type& world, const rule_type& rule) const;
};

template<typename T_traits>
typename SynchronousStepper<T_traits>::time_type
SynchronousStepper<T_traits>::step(world_type& world, const rule_type& rule) const
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

template<typename T_traits>
class AsynchronousStepper
{
  public:
    using traits_type = T_traits;
    using time_type   = typename traits_type::time_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using rule_type   = RuleBase<traits_type>;
    using world_type  = World<traits_type>;

    AsynchronousStepper() = default;
   ~AsynchronousStepper() = default;
    time_type step(world_type& world, const rule_type& rule) const;

    const std::shared_ptr<RandomNumberGenerator> rng_;
};

template<typename T_traits>
typename AsynchronousStepper<T_traits>::time_type
AsynchronousStepper<T_traits>::step(world_type& world, const rule_type& rule) const
{
    std::size_t size = world.size();
    std::size_t cell_idx = rng_->uniform_int<std::size_t>(0, size);
    world.at(cell_idx)->state = rule.step(*(world.at(cell_idx)));

    return rule.delta_t();
}

}

#endif /* MINIASCAPE_STEPPER */
