#ifndef MINIASCAPE_LOCALIZED_ISING_MODEL_TRAITS
#define MINIASCAPE_LOCALIZED_ISING_MODEL_TRAITS
#include "core/Cell.hpp"
#include "core/Rule.hpp"
#include "core/Observer.hpp"
#include "core/NeighborhoodIndex.hpp"
#include "core/PeriodicBoundary.hpp"
#include "core/RandomNumberGenerator.hpp"
#include "core/SquareLattice.hpp"
#include "core/Stepper.hpp"
#include "IsingModelVisualizer.hpp"

namespace miniascape
{

template<>
class RandomStateGenerator<bool>
{
  public:
    explicit RandomStateGenerator(const unsigned int s) : mt_(s), bn_(0.5){}
    ~RandomStateGenerator() = default;

    bool operator()(){return bn_(mt_);}

    std::mt19937 mt_;
    std::bernoulli_distribution bn_;
};

struct IsingModelTypeTraits
{
    using size_type     = std::size_t;
    using time_type     = std::size_t;
    using state_type    = bool;
    using neighbor_type = VonNeumannNeighborhood;
    using cell_type     = Cell<neighbor_type::num_neighbor, state_type>;
    using boundary_type = PeriodicBoundary<neighbor_type>;
};

class IsingModelRule : public RuleBase<IsingModelTypeTraits>
{
  public:
    using base_type  = RuleBase<IsingModelTypeTraits>;
    using time_type  = typename base_type::time_type;
    using state_type = typename base_type::state_type;
    using cell_type  = typename base_type::cell_type;

  public:
    IsingModelRule(const std::shared_ptr<RandomNumberGenerator>& rng,
                   const double kB = 1., const double T = 1.)
        : probs{{1.0, std::exp(-1./(kB * T)), std::exp(-2./(kB * T)),
                      std::exp(-3./(kB * T)), std::exp(-4./(kB * T))}},
          rng_(rng)
    {}
    ~IsingModelRule() override = default;

    state_type step(const cell_type& cell) const override;
    time_type  delta_t() const override {return 1;}

  private:
    const std::array<double, 5> probs;
    const std::shared_ptr<RandomNumberGenerator> rng_;
};

inline typename IsingModelRule::state_type
IsingModelRule::step(const cell_type& cell) const
{
    const bool center = cell.state;
    short dE = 0;
    for(auto iter = cell.neighbors.cbegin();
            iter != cell.neighbors.cend(); ++iter)
    {
        if(center != (*iter)->state) --dE;
        else ++dE;
    }

    return (dE <= 0) ? (!center) :
        ((rng_->uniform_real<float>(0.,1.) < probs.at(dE)) != center);
}

template<typename T_traits>
struct IsingModelSimulatorTraits
{
    using world_type    = SquareLattice<T_traits>;
    using rule_type     = IsingModelRule;
    using stepper_type  = AsynchronousSuccessiveStepper<T_traits>;
    using observer_type = IsingModelVisualizer<T_traits>;
};

using IsingModelObserver =
    IsingModelVisualizer<IsingModelTypeTraits>;

}//miniascape

#endif /*MINIASCAPE_ISING_MODEL_TRAITS*/
