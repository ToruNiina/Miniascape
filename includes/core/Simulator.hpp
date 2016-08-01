#ifndef MINIASCAPE_SIMULATOR
#define MINIASCAPE_SIMULATOR
#include "core/Stepper.hpp"
#include "core/Observer.hpp"
#include "core/World.hpp"

namespace miniascape
{

template<template<typename T>class T_simulator_traits, typename T_traits>
class Simulator
{
  public:
    using traits_type      = T_traits;
    using simulator_traits = T_simulator_traits<traits_type>;
    using time_type        = typename traits_type::time_type;
    using state_type       = typename traits_type::state_type;
    using cell_type        = typename traits_type::cell_type;
    using world_base       = World<traits_type>;
    using rule_base        = RuleBase<traits_type>;
    using observer_base    = Observer<traits_type>;
    using world_type       = typename simulator_traits::world_type;
    using rule_type        = typename simulator_traits::rule_type;
    using observer_type    = typename simulator_traits::observer_type;
    using stepper_type     = typename simulator_traits::stepper_type;
 
  public:
    Simulator(const time_type t_end)
        : t_(0), t_end_(t_end)
    {}
    virtual ~Simulator() = default;

    virtual void initialize(){};
            bool step_(const rule_type& rule, stepper_type& stepper);
            void observe(observer_type& obs) const;
    virtual void finalize(){};

  protected:

    time_type  t_;
    time_type  t_end_;
    world_type world_;
};

template<template<typename T>class T_simulator_traits, typename T_traits>
inline bool Simulator<T_simulator_traits, T_traits>::step_(
        const rule_type& rule, stepper_type& stepper)
{
    this->t_ += stepper.step(world_, rule);
    return (t_ >= t_end_) ? false : true;
}

template<template<typename T>class T_simulator_traits, typename T_traits>
inline void Simulator<T_simulator_traits, T_traits>::observe(observer_type& obs) const
{
    obs.observe(this->t_, this->world_);
    return;
}

}//miniascape

#endif /* MINIASCAPE_SIMULATOR */
