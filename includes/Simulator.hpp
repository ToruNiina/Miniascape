#ifndef MINIASCAPE_SIMULATOR
#define MINIASCAPE_SIMULATOR
#include "Stepper.hpp"
#include "Observer.hpp"
#include "World.hpp"

namespace miniascape
{

template<template<typename T>class T_world, typename T_traits>
class Simulator
{
  public:
    using traits_type   = T_traits;
    using time_type     = typename traits_type::time_type;
    using state_type    = typename traits_type::state_type;
    using cell_type     = typename traits_type::cell_type;
    using stepper_type  = Stepper<traits_type>;
    using rule_type     = RuleBase<traits_type>;
    using observer_type = Observer<traits_type>;
    using world_base    = World<traits_type>;
    using world_type    = T_world<traits_type>;

    static_assert(std::is_base_of<world_base, world_type>::value,
                  "invalid world type");

  public:
    Simulator(const time_type t_end)
        : t_(0), t_end_(t_end)
    {}
    ~Simulator() = default;

    virtual void initialize();
            bool step(const rule_type& rule);
            void observe(std::ostream& os, observer_type& obs);
    virtual void finalize();

  protected:

    time_type  t_;
    time_type  t_end_;
    world_type world_;
};

template<template<typename T>class T_world, typename T_traits>
inline void Simulator<T_world, T_traits>::initialize()
{
    return;
}

template<template<typename T>class T_world, typename T_traits>
inline bool Simulator<T_world, T_traits>::step(const rule_type& rule)
{
    this->t_ += stepper_type::step(world_, rule);
    return (t_ >= t_end_) ? false : true;
}

template<template<typename T>class T_world, typename T_traits>
inline void
Simulator<T_world, T_traits>::observe(std::ostream& os, observer_type& obs)
{
    obs.observe(os, this->t_, this->world_);
    return;
}

template<template<typename T>class T_world, typename T_traits>
inline void Simulator<T_world, T_traits>::finalize()
{
    return;
}

}

#endif /* MINIASCAPE_SIMULATOR */
