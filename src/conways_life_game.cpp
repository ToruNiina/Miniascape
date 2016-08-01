#include "ConwaysLifeGameTraits.hpp"
#include "ConwaysLifeGameSimulator.hpp"
#include <chrono>
#include <thread>
using namespace miniascape;

int main()
{
    ConwaysLifeGameSimulator simu(1000, 640, 480);
    ConwaysLifeGameRule rule;
    ConwaysLifeGameObserver obs(640, 480);

    simu.initialize();

    while(simu.step(rule))
    {
        simu.observe(obs);
    }

    simu.finalize();

    return EXIT_SUCCESS;
}
