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

struct boolean
{
    boolean() : val(false){}
    boolean(const bool b) : val(b){}
    bool val;

    operator bool      &()       {return val;}
    operator bool const&() const {return val;}
};

template<>
class RandomStateGenerator<boolean>
{
  public:
    explicit RandomStateGenerator(const unsigned int s) : mt_(s), bn_(0.5){}
    ~RandomStateGenerator() = default;

    boolean operator()(){return bn_(mt_);}

    std::mt19937 mt_;
    std::bernoulli_distribution bn_;
};

struct IsingModelTypeTraits
{
    using size_type     = std::size_t;
    using time_type     = std::size_t;
    using state_type    = boolean;
    using cell_type     = Cell<8, state_type>;
    using neighbor_type = MooreNeighborhood;
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
        : mbeta_(-1.0 / (kB * T)), rng_(rng)
    {}
    ~IsingModelRule() override = default;

    state_type step(const cell_type& cell) const override;
    time_type  delta_t() const override {return 1;}

  private:
    const double mbeta_;
    const std::shared_ptr<RandomNumberGenerator> rng_;
};

inline typename IsingModelRule::state_type
IsingModelRule::step(const cell_type& cell) const
{
    const bool center = cell.state.val;
    int dE = 0;
    for(auto iter = cell.neighbors.cbegin();
            iter != cell.neighbors.cend(); ++iter)
    {
        if(center != (*iter)->state.val) --dE;
        else ++dE;
    }

    return (dE <= 0) ? (!center) :
        ((rng_->uniform_real<double>(0.,1.) < std::exp(mbeta_ * dE)) != center);
}

template<typename T_traits>
struct IsingModelSimulatorTraits
{
    using world_type    = SquareLattice<T_traits>;
    using rule_type     = IsingModelRule;
    using stepper_type  = AsynchronousRandomStepper<T_traits>;
    using observer_type = IsingModelVisualizer<T_traits>;
};

using IsingModelObserver =
    IsingModelVisualizer<IsingModelTypeTraits>;

}//miniascape

#endif /*MINIASCAPE_ISING_MODEL_TRAITS*/
