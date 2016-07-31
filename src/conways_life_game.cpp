#include "ConwaysLifeGameTraits.hpp"
#include "ConwaysLifeGameSimulator.hpp"
using namespace miniascape;

int main()
{
    ConwaysLifeGameSimulator simu(1000, 100, 100);
    ConwaysLifeGameRule rule;
    ConwaysLifeGameObserver obs(100, 100);

    simu.initialize();

    while(simu.step(rule))
    {
        simu.observe(obs);
    }

    simu.finalize();

    return EXIT_SUCCESS;
}
