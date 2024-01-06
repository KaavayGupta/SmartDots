#pragma once

#include "olcPixelGameEngine.h"

class SimObject
{
public:
    static int m_ScreenWidth;
    static int m_ScreenHeight;

    olc::vf2d m_Position;

    enum class MouseState
    {
        IDLE = 0,
        MOVING_GOAL,
        DRAWING_OBSTACLE
    };

    static MouseState m_MouseState;

public:
    virtual void Update(olc::PixelGameEngine* pge) { }
    virtual void Draw(olc::PixelGameEngine* pge) { }
};