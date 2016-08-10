#ifndef MINIASCAPE_TURING_PATTERN_TRAITS
#define MINIASCAPE_TURING_PATTERN_TRAITS
#include "core/Cell.hpp"
#include "core/Rule.hpp"
#include "core/Observer.hpp"
#include "core/NeighborhoodIndex.hpp"
#include "core/PeriodicBoundary.hpp"
#include "core/RandomNumberGenerator.hpp"
#include "core/SquareLattice.hpp"
#include "core/Stepper.hpp"
#include "TuringPatternVisualizer.hpp"

namespace miniascape
{

struct Molecules
{
    double u;
    double v;
};

template<>
class RandomStateGenerator<Molecules>
{
  public:
    explicit RandomStateGenerator(const unsigned int s) : mt_(s), bn_(0.9){}
    ~RandomStateGenerator() = default;

    Molecules operator()(){return (bn_(mt_)) ? Molecules{0.9, 0.0} : Molecules{1.0, 0.3};}

    std::mt19937 mt_;
    std::bernoulli_distribution bn_;
};

struct TuringPatternTypeTraits
{
    using size_type     = std::size_t;
    using time_type     = std::size_t;
    using state_type    = Molecules;
    using cell_type     = Cell<4, state_type>;
    using neighbor_type = VonNeumannNeighborhood;
    using boundary_type = PeriodicBoundary<neighbor_type>;
};

// Gray-Scott model
class TuringPatternRule : public RuleBase<TuringPatternTypeTraits>
{
  public:
    using base_type  = RuleBase<TuringPatternTypeTraits>;
    using time_type  = typename base_type::time_type;
    using state_type = typename base_type::state_type;
    using cell_type  = typename base_type::cell_type;

  public:
    TuringPatternRule(const double Du, const double Dv, const double F, const double k)
        : Du_(Du), Dv_(Dv), F_(F), k_(k)
    {}
    ~TuringPatternRule() override = default;

    state_type step(const cell_type& cell) const override;
    time_type  delta_t() const override {return 1;}

  private:
    const double Du_;
    const double Dv_;
    const double F_;
    const double k_;
};

inline typename TuringPatternRule::state_type
TuringPatternRule::step(const cell_type& cell) const
{
    Molecules dconc{0.,0.};
    const double u = cell.state.u;
    const double v = cell.state.v;

    for(auto iter = cell.neighbors.cbegin();
            iter != cell.neighbors.cend(); ++iter)
    {
        dconc.u += (*iter)->state.u;
        dconc.v += (*iter)->state.v;
    }
    dconc.u -= cell.neighbors.size() * u;
    dconc.v -= cell.neighbors.size() * v;
    dconc.u *= Du_;
    dconc.v *= Dv_;

    const double uvv = u * v * v;

    dconc.u += 0.5 * ((-1.0 * uvv) + (F_ * (1.0 - u)));
    dconc.v += 0.5 * (        uvv  - ((F_ + k_) * v));

    return Molecules{u + dconc.u, v + dconc.v};
}

template<typename T_traits>
struct TuringPatternSimulatorTraits
{
    using world_type    = SquareLattice<T_traits>;
    using rule_type     = TuringPatternRule;
    using stepper_type  = SynchronousStepper<T_traits>;
    using observer_type = TuringPatternVisualizer<T_traits>;
};

using TuringPatternObserver = TuringPatternVisualizer<TuringPatternTypeTraits>;

}

#endif /* MINIASCAPE_TURING_PATTERN_TRAITS */
