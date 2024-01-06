#include "Goal.h"

#include "Utility.h"

void Goal::Update(olc::PixelGameEngine* pge)
{
    if (SimObject::m_MouseState == SimObject::MouseState::IDLE)
    {
        if (SqrDistance(pge->GetMousePos(), m_Position) < 70.0f)
        {
            m_Color = olc::DARK_RED;
            if (pge->GetMouse(0).bPressed)
                SimObject::m_MouseState = SimObject::MouseState::MOVING_GOAL;
        }
        else
            m_Color = olc::RED;
    }

    if (SimObject::m_MouseState == SimObject::MouseState::MOVING_GOAL)
    {
        m_Position = pge->GetMousePos();
        if (pge->GetMouse(0).bReleased)
        {
            SimObject::m_MouseState = SimObject::MouseState::IDLE;
            m_Color = olc::RED;
        }
    }
}

void Goal::Draw(olc::PixelGameEngine* pge)
{
    pge->FillCircle(m_Position, 8, m_Color);
}