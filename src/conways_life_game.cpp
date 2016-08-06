#include "ConwaysLifeGameTraits.hpp"
#include "ConwaysLifeGameSimulator.hpp"
#include <chrono>
#include <thread>
using namespace miniascape;

int main()
{
    ConwaysLifeGameSimulator simu(10, 3000, 960, 640);
    ConwaysLifeGameObserver  obs(960, 640);

    simu.initialize();
    while(simu.step())
    {
        simu.observe(obs);
        if(obs.closed()) break;
    }
    simu.finalize();

    return EXIT_SUCCESS;
}
