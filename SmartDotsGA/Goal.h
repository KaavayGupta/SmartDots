#pragma once

#include "SimObject.h"

class Goal : public SimObject
{
public:
    void Update(olc::PixelGameEngine* pge) override;
    void Draw(olc::PixelGameEngine* pge) override;

private:
    olc::Pixel m_Color = olc::RED;
};

