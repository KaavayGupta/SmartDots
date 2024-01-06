#pragma once

#include "SimObject.h"
#include "Goal.h"
#include "DNA.h"
#include "Obstacles.h"

class Dot : public SimObject
{
public:
    Dot(Goal* goal);

    void Update(olc::PixelGameEngine* pge) override;
    void Draw(olc::PixelGameEngine* pge) override;
    void CalculateFitness();
    Dot CreateChild();
private:
    void Move();

private:
    olc::vf2d m_Velocity;
    olc::vf2d m_Acceleration;
    float m_MaxVelocity = 5;
    Goal* m_Goal;
public:
    bool m_IsDead = false;
    bool m_ReachedGoal = false;
    bool m_IsBest = false;
    float m_Fitness = 0.0f;
    DNA m_DNA = DNA(1000);
};