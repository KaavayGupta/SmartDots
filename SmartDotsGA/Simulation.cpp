#include "Simulation.h"

void Simulation::DrawMenu()
{
    DrawString(1, 1, "Generation: " + std::to_string(m_Population->m_Gen), olc::BLUE);
    DrawString(1, 10, "Draw Obstacles by Dragging the Mouse", olc::DARK_BLUE);
    DrawString(1, 20, "Drag the Goal to Change its Position", olc::DARK_BLUE);

    DrawString(1, ScreenHeight() - 50, "R: Reset Population", olc::BLACK);
    DrawString(1, ScreenHeight() - 40, "Hold S: Limit to 100 FPS", olc::BLACK);
    DrawString(1, ScreenHeight() - 30, "B: Toggle Only Show Best From Prev Gen", olc::BLACK);
    DrawString(1, ScreenHeight() - 20, "D(When Over Obstacle): Delete that obstacle", olc::BLUE);
    DrawString(1, ScreenHeight() - 10, "D: Delete all obstacles", olc::BLUE);
}

bool Simulation::OnUserCreate()
{
    std::srand(std::time(nullptr));

    SimObject::m_ScreenHeight = ScreenHeight();
    SimObject::m_ScreenWidth = ScreenWidth();

    m_Goal.m_Position.x = ScreenWidth() / 2;
    m_Goal.m_Position.y = 20;
    m_Population = new Population(100, &m_Goal);

    return true;
}

bool Simulation::OnUserUpdate(float fElapsedTime)
{
    if (GetKey(olc::Key::B).bPressed)
        m_ShowOnlyBest = !m_ShowOnlyBest;

    // Handle FPS Limitation
    if (GetKey(olc::Key::S).bHeld)
    {
        m_AccumulatedTime += fElapsedTime;
        if (m_AccumulatedTime >= m_TargetFrameTime)
        {
            m_AccumulatedTime -= m_TargetFrameTime;
            fElapsedTime = m_TargetFrameTime;
        }
        else
            return true; // Don't do anything this frame
    }

    Clear(olc::WHITE);

    m_Goal.Update(this);
    m_Obstacles.Update(this);

    m_Obstacles.Draw(this);
    m_Goal.Draw(this);

    // Reset Population
    if (GetKey(olc::Key::R).bPressed || SimObject::m_MouseState != SimObject::MouseState::IDLE)
    {
        m_Population->Reset();
        return true;
    }

    if (m_Population->AllDotsDead())
    {
        m_Population->CalculateFitness();
        m_Population->NatrualSelection();
        m_Population->Mutate();
    }
    else
    {
        m_Population->Update(this);
        m_Population->Show(this, m_ShowOnlyBest);
    }

    DrawMenu();

    return true;
}