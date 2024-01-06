#define OLC_PGE_APPLICATION
#include "Simulation.h"

int main()
{
    Simulation simulation;
    if (simulation.Construct(800, 600, 1, 1, false))
        simulation.Start();

    return 0;
}
