#include "ConwaysLifeGameTraits.hpp"
#include "ConwaysLifeGameSimulator.hpp"
using namespace miniascape;

int main()
{
    ConwaysLifeGameSimulator simu(100, 100, 100);
    ConwaysLifeGameRule rule;
    ConwaysLifeGameObserver obs;

    simu.initialize();

    while(simu.step(rule))
    {
        simu.observe(obs);
    }

    simu.finalize();

    return EXIT_SUCCESS;
}
