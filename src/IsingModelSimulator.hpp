#ifndef MINIASCAPE_ISING_MODEL_SIMULATOR
#define MINIASCAPE_ISING_MODEL_SIMULATOR
#include "core/Simulator.hpp"
#include "core/SquareLattice.hpp"
#include "core/RandomNumberGenerator.hpp"
#include "IsingModelTraits.hpp"

namespace miniascape
{

class IsingModelSimulator
    : public Simulator<IsingModelSimulatorTraits, IsingModelTypeTraits>
{
  public:
    using traits_type = IsingModelTypeTraits;
    template<typename T>
    using simulator_traits = IsingModelSimulatorTraits<T>;
    using base_type    = Simulator<simulator_traits, traits_type>;
    using rule_type    = typename base_type::rule_type;
    using stepper_type = typename base_type::stepper_type;

  public:
    IsingModelSimulator(const unsigned int seed, const time_type t_end,
            const std::size_t v, const std::size_t h)
        : Simulator(t_end), rng_(std::make_shared<RandomNumberGenerator>(seed)),
          seed_(seed), vertical_(v), horizontal_(h), rule_(rng_), stepper_(rng_)
    {}
    ~IsingModelSimulator() = default;

    void initialize() override;
    bool step();
    void finalize() override;

  private:
    const std::shared_ptr<RandomNumberGenerator> rng_;
    const unsigned int seed_;
    const std::size_t  vertical_;
    const std::size_t  horizontal_;
    rule_type    rule_;
    stepper_type stepper_;
};

inline void IsingModelSimulator::initialize()
{
    this->world_.create(vertical_, horizontal_);
    RandomStateGenerator<state_type> rsg(seed_);
    this->world_.randomize(rsg);
}

inline bool IsingModelSimulator::step()
{
    return this->step_(rule_, stepper_);
}

inline void IsingModelSimulator::finalize()
{
    return ;
}



}

#endif /* MINIASCAPE_CONWAYS_LIFEGAME_SIMULATOR */
