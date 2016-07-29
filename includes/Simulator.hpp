#ifndef MINIASCAPE_SIMULATOR
#define MINIASCAPE_SIMULATOR
#include "Stepper.hpp"
#include "Observer.hpp"
#include "World.hpp"

namespace miniascape
{

template<typename T_traits>
class Simulator
{
  public:
    using traits_type   = T_traits;
    using time_type     = typename traits_type::time_type;
    using state_type    = typename traits_type::state_type;
    using cell_type     = typename traits_type::cell_type;
    using world_type    = World<traits_type>;
    using space_type    = Space<traits_type>;
    using stepper_type  = Stepper<traits_type>;
    using rule_type     = RuleBase<traits_type>;
    using observer_type = Observer<traits_type>;

  public:
    explicit Simulator(const time_type t_end) : t_end_(t_end){};
    ~Simulator() = default;

    virtual void initialize();
            bool step(const rule_type& rule);
            void observe(std::ostream& os, const observer_type& obs);
    virtual void finalize();

  protected:

    time_type  t_;
    time_type  t_end_;
    space_type space_;
};

template<typename T>
inline void Simulator<T>::initialize()
{
    return;
}

template<typename T>
inline bool Simulator<T>::step(const rule_type& rule)
{
    this->t_ += stepper_type::step(space_, rule);
    return (t_ > t_end_) ? false : true;
}

template<typename T>
inline void Simulator<T>::observe(std::ostream& os, const observer_type& obs)
{
    obs.observe(os, this->t_, this->space_);
    return;
}

template<typename T>
inline void Simulator<T>::finalize()
{
    return;
}

}

#endif /* MINIASCAPE_SIMULATOR */
