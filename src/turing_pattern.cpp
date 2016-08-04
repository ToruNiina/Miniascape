#include "TuringPatternTraits.hpp"
#include "TuringPatternSimulator.hpp"
#include <chrono>
using namespace miniascape;

int main()
{
    TuringPatternSimulator simu(100, 1000, 640, 480,
                                0.03, 0.015, 0.054, 0.063);
    TuringPatternObserver vis(640, 480);

    simu.initialize();
    while(simu.step())
    {
        simu.observe(vis);
    }
    simu.finalize();

    return EXIT_SUCCESS;
}
