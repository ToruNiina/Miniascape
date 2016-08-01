#include "ConwaysLifeGameTraits.hpp"
#include "ConwaysLifeGameSimulator.hpp"
#include <chrono>
#include <thread>
using namespace miniascape;

int main()
{
    ConwaysLifeGameSimulator simu(10, 1000, 640, 480);
    ConwaysLifeGameObserver  obs(640, 480);

    simu.initialize();
    while(simu.step())
    {
        simu.observe(obs);
    }
    simu.finalize();

    return EXIT_SUCCESS;
}
