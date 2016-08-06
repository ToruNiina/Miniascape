#include "TuringPatternTraits.hpp"
#include "TuringPatternSimulator.hpp"
#include <chrono>
using namespace miniascape;

int main()
{
    TuringPatternSimulator simu(100, 5000, 960, 640,
                                0.05, 0.025, 0.026, 0.055);
    TuringPatternObserver vis(960, 640);

    simu.initialize();
    while(simu.step())
    {
        simu.observe(vis);
        if(vis.closed()) break;
    }
    simu.finalize();

    return EXIT_SUCCESS;
}
