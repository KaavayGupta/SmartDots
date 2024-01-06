#pragma once

#include "olcPixelGameEngine.h"
#include "Population.h"
#include "Goal.h"
#include "Obstacles.h"

class Simulation : public olc::PixelGameEngine
{
public:
    Simulation()
    {
        sAppName = "Smart Dots with Genetic Algorithm";
    }

    ~Simulation()
    {
        delete m_Population;
    }

public:
    bool OnUserCreate();
    bool OnUserUpdate(float fElapsedTime);
private:
    void DrawMenu();

private:
    Population* m_Population;
    Obstacles m_Obstacles;
    Goal m_Goal;

    float m_TargetFrameTime = 1.0f / 100.0f; // Virtual FPS of 100fps
    float m_AccumulatedTime = 0.0f;

    bool m_ShowOnlyBest = false;
};
