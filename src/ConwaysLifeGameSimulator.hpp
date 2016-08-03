#ifndef MINIASCAPE_CONWAYS_LIFEGAME_SIMULATOR
#define MINIASCAPE_CONWAYS_LIFEGAME_SIMULATOR
#include "core/Simulator.hpp"
#include "core/SquareLattice.hpp"
#include "core/RandomNumberGenerator.hpp"
#include "ConwaysLifeGameTraits.hpp"

namespace miniascape
{

class ConwaysLifeGameSimulator
    : public Simulator<ConwaysLifeGameSimulatorTraits, ConwaysLifeGameTypeTraits>
{
  public:
    using traits_type = ConwaysLifeGameTypeTraits;
    template<typename T>
    using simulator_traits = ConwaysLifeGameSimulatorTraits<T>;
    using base_type    = Simulator<simulator_traits, traits_type>;
    using rule_type    = typename base_type::rule_type;
    using stepper_type = typename base_type::stepper_type;

  public:
    ConwaysLifeGameSimulator(const unsigned int seed, const time_type t_end,
            const std::size_t v, const std::size_t h)
        : Simulator(t_end), seed_(seed), vertical_(v), horizontal_(h),
          rule_(), stepper_()
    {}
    ~ConwaysLifeGameSimulator() = default;

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

inline void ConwaysLifeGameSimulator::initialize()
{
    this->world_.create(vertical_, horizontal_);
    RandomStateGenerator<state_type> rsg(seed_);
    this->world_.randomize(rsg);
}

inline bool ConwaysLifeGameSimulator::step()
{
    return this->step_(rule_, stepper_);
}

inline void ConwaysLifeGameSimulator::finalize()
{
    return ;
}



}

#endif /* MINIASCAPE_CONWAYS_LIFEGAME_SIMULATOR */
