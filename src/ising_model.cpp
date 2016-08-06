#include "IsingModelTraits.hpp"
#include "IsingModelSimulator.hpp"
#include <chrono>
#include <thread>
using namespace miniascape;

int main()
{
    IsingModelSimulator simu(100, 1000, 640, 480);
    IsingModelObserver  obs(640, 480);

    simu.initialize();
    while(simu.step())
    {
        simu.observe(obs);
        if(obs.closed()) break;
    }
    simu.finalize();

    return EXIT_SUCCESS;
}
