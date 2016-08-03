#include "IsingModelTraits.hpp"
#include "IsingModelSimulator.hpp"
#include <chrono>
#include <thread>
using namespace miniascape;

int main()
{
    IsingModelSimulator simu(100, 5000000, 640, 480);
    IsingModelObserver  obs(640, 480);

    simu.initialize();
    std::size_t index = 0;
    while(simu.step())
    {
        if(index % 5000 == 0)
            simu.observe(obs);
        ++index;
    }
    simu.finalize();

    return EXIT_SUCCESS;
}
