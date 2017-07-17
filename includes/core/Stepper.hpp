#ifndef MINIASCAPE_STEPPER
#define MINIASCAPE_STEPPER
#include "core/World.hpp"
#include "core/Rule.hpp"
#include "core/RandomNumberGenerator.hpp"
#include <pseudo/zip_iterator.hpp>

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
SynchronousStepper<T_traits>::step(
        world_type& world, const rule_type& rule) const
{
    std::vector<state_type> temp(world.size());

    for(auto cell = psd::make_zip_iterator(world.cbegin(), temp.begin());
            cell != psd::make_zip_iterator(world.cend(),   temp.end()); ++cell)
        *psd::get<1>(cell) = rule.step(**psd::get<0>(cell));

    for(auto cell = psd::make_zip_iterator(world.begin(), temp.begin());
            cell != psd::make_zip_iterator(world.end(),   temp.end()); ++cell)
        (*psd::get<0>(cell))->state = std::move(*psd::get<1>(cell));

    return rule.delta_t();
}



template<typename T_traits>
class AsynchronousRandomStepper
{
  public:
    using traits_type = T_traits;
    using time_type   = typename traits_type::time_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using rule_type   = RuleBase<traits_type>;
    using world_type  = World<traits_type>;

    AsynchronousRandomStepper(const std::shared_ptr<RandomNumberGenerator>& rng)
        : rng_(rng)
    {}
    ~AsynchronousRandomStepper() = default;
    time_type step(world_type& world, const rule_type& rule) const;

    const std::shared_ptr<RandomNumberGenerator> rng_;
};

template<typename T_traits>
inline typename AsynchronousRandomStepper<T_traits>::time_type
AsynchronousRandomStepper<T_traits>::step(
        world_type& world, const rule_type& rule) const
{
    const std::size_t idx = rng_->uniform_int<std::size_t>(0, world.size()-1);
    world.at(idx)->state = rule.step(*(world.at(idx)));

    return rule.delta_t();
}


template<typename T_traits>
class AsynchronousSuccessiveStepper
{
  public:
    using traits_type = T_traits;
    using time_type   = typename traits_type::time_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using rule_type   = RuleBase<traits_type>;
    using world_type  = World<traits_type>;

    AsynchronousSuccessiveStepper() = default;
    ~AsynchronousSuccessiveStepper() = default;
    time_type step(world_type& world, const rule_type& rule) const;

    const std::shared_ptr<RandomNumberGenerator> rng_;
};

template<typename T_traits>
inline typename AsynchronousSuccessiveStepper<T_traits>::time_type
AsynchronousSuccessiveStepper<T_traits>::step(
        world_type& world, const rule_type& rule) const
{
    for(auto cell = world.cbegin(); cell != world.cend(); ++cell)
        (*cell)->state = rule.step(**cell);

    return rule.delta_t();
}

}

#endif /* MINIASCAPE_STEPPER */
