#pragma once

#include "Dot.h"

class Population
{
public:
    Population(size_t size, Goal* goal);

    void Update(olc::PixelGameEngine* pge);
    void Show(olc::PixelGameEngine* pge, bool showOnlyBest = false);
    void CalculateFitness();
    bool AllDotsDead();
    void NatrualSelection();
    void Mutate();
    void Reset();
private:
    int GetParentIndex();
    void CalculateFitnessSum();
    void SetBestDot();

private:
    std::vector<Dot> m_Dots;
    float m_FitnessSum = 0.0f;
    int m_BestDot = -1;
    int m_MinStep = 10000;
    Goal* m_Goal;
public:
    int m_Gen = 1;

};
