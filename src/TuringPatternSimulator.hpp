#ifndef MINIASCAPE_TURING_PATTERN_SIMULATOR
#define MINIASCAPE_TURING_PATTERN_SIMULATOR
#include "core/Simulator.hpp"
#include "core/SquareLattice.hpp"
#include "core/RandomNumberGenerator.hpp"
#include "TuringPatternTraits.hpp"

namespace miniascape
{

class TuringPatternSimulator
    : public Simulator<TuringPatternSimulatorTraits, TuringPatternTypeTraits>
{
  public:
    using traits_type = TuringPatternTypeTraits;
    template<typename T>
    using simulator_traits = TuringPatternSimulatorTraits<T>;
    using base_type    = Simulator<simulator_traits, traits_type>;
    using rule_type    = typename base_type::rule_type;
    using stepper_type = typename base_type::stepper_type;

  public:
    TuringPatternSimulator(const unsigned int seed, const time_type t_end,
            const std::size_t v, const std::size_t h,
            const double Du, const double Dv, const double b, const double c)
        : Simulator(t_end), seed_(seed), vertical_(v), horizontal_(h),
          rule_(Du, Dv, b, c), stepper_()
    {}
    ~TuringPatternSimulator() = default;

    void initialize() override;
    bool step();
    void finalize() override;

  private:
    const unsigned int seed_;
    const std::size_t  vertical_;
    const std::size_t  horizontal_;
    rule_type    rule_;
    stepper_type stepper_;
};

inline void TuringPatternSimulator::initialize()
{
    this->world_.create(vertical_, horizontal_);
    RandomStateGenerator<state_type> rsg(seed_);
    this->world_.randomize(rsg);
}

inline bool TuringPatternSimulator::step()
{
    return this->step_(rule_, stepper_);
}

inline void TuringPatternSimulator::finalize()
{
    return ;
}



}

#endif /* MINIASCAPE_CONWAYS_LIFEGAME_SIMULATOR */
