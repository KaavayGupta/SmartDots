#pragma once

#include "olcPixelGameEngine.h"

class DNA
{
public:
    DNA(size_t size);

    DNA Clone();
    void Mutate(float mutationRate);
private:
    void Randomize();

private:
    size_t m_Size;
public:
    std::vector<olc::vf2d> m_Directions;
    int m_Step = 0;
};
