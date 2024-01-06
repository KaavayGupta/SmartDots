#pragma once

#include "olcPixelGameEngine.h"
#include "SimObject.h"

struct ObstacleDimensions
{
	olc::vf2d Size;
	olc::vf2d TopLeft, BottomRight;
	olc::Pixel Color = olc::CYAN;

	ObstacleDimensions() {};

	ObstacleDimensions(olc::vf2d initialPos, olc::vf2d finalPos, olc::Pixel c=olc::CYAN) : Color(c)
	{
		if (finalPos.x >= initialPos.x && finalPos.y >= initialPos.y)
		{
			TopLeft = initialPos;
			Size = finalPos - initialPos;
		}
		else if (finalPos.x < initialPos.x && finalPos.y < initialPos.y)
		{
			TopLeft = finalPos;
			Size = initialPos - finalPos;
		}
		else if (finalPos.x < initialPos.x && finalPos.y > initialPos.y)
		{
			TopLeft = olc::vf2d(finalPos.x, initialPos.y);
			Size = olc::vf2d(initialPos.x - finalPos.x, finalPos.y - initialPos.y);
		}
		else if (finalPos.x > initialPos.x && finalPos.y < initialPos.y)
		{
			TopLeft = olc::vf2d(initialPos.x, finalPos.y);
			Size = olc::vf2d(finalPos.x - initialPos.x, initialPos.y - finalPos.y);
		}
		
		BottomRight = TopLeft + Size;
	}
};

class Obstacles : public SimObject
{
public:
	void Update(olc::PixelGameEngine* pge) override;
	void Draw(olc::PixelGameEngine* pge) override;

	static bool IsPointIntersecting(const olc::vf2d& p, bool isMouse = false);
private:
	void HandleObstacleCreation(olc::PixelGameEngine* pge);
	void HandleObstacleDeletion(olc::PixelGameEngine* pge);

private:
	static std::map<int, ObstacleDimensions> m_Obstacles;
	static int m_MouseOverIndex;
	olc::vf2d m_InitialMousePos;
	olc::Pixel m_Color = olc::CYAN;
	int m_ObstacleCount = 0;
};

