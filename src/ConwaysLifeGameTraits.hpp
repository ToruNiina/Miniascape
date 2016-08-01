#ifndef MINIASCAPE_CONWAYS_LIFE_GAME_TRAITS
#define MINIASCAPE_CONWAYS_LIFE_GAME_TRAITS
#include "core/Cell.hpp"
#include "core/Rule.hpp"
#include "core/Observer.hpp"
#include "core/NeighborhoodIndex.hpp"
#include "core/PeriodicBoundary.hpp"
#include "core/RandomStateGenerator.hpp"
#include "core/SquareLattice.hpp"
#include "core/Stepper.hpp"
#include "ConwaysLifeGameVisualizer.hpp"

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

struct ConwaysLifeGameTypeTraits
{
    using size_type     = std::size_t;
    using time_type     = std::size_t;
    using state_type    = boolean;
    using cell_type     = Cell<8, state_type>;
    using neighbor_type = MooreNeighborhood;
    using boundary_type = PeriodicBoundary<neighbor_type>;
};

class ConwaysLifeGameRule : public RuleBase<ConwaysLifeGameTypeTraits>
{
  public:
    using base_type  = RuleBase<ConwaysLifeGameTypeTraits>;
    using time_type  = typename base_type::time_type;
    using state_type = typename base_type::state_type;
    using cell_type  = typename base_type::cell_type;

  public:
    ConwaysLifeGameRule() = default;
    ~ConwaysLifeGameRule() override = default;

    state_type step(const cell_type& cell) override;
    time_type  delta_t() override {return 1;}
};

inline typename ConwaysLifeGameRule::state_type
ConwaysLifeGameRule::step(const cell_type& cell)
{
    std::size_t lives = 0;
    for(auto iter = cell.neighbors.cbegin();
            iter != cell.neighbors.cend(); ++iter)
        if((*iter)->state.val) ++lives;

    return (cell.state) ? (lives == 2 or lives == 3) : (lives == 3);
}

template<typename T_traits>
struct ConwaysLifeGameSimulatorTraits
{
    using world_type    = SquareLattice<T_traits>;
    using rule_type     = ConwaysLifeGameRule;
    using stepper_type  = SynchronousStepper<T_traits>;
    using observer_type = ConwaysLifeGameVisualizer<T_traits>;
};

template<>
class RandomStateGenerator<boolean>
{
  public:
    explicit RandomStateGenerator(const unsigned int s) : mt_(s), bn_(0.2){}
    ~RandomStateGenerator() = default;

    boolean operator()(){return bn_(mt_);}

    std::mt19937 mt_;
    std::bernoulli_distribution bn_;
};

using ConwaysLifeGameObserver =
    ConwaysLifeGameVisualizer<ConwaysLifeGameTypeTraits>;

}

#endif /* MINIASCAPE_CONWAYS_LIFE_GAME_TRAITS */
