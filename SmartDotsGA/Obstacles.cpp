#include "Obstacles.h"

#include "Utility.h"

std::map<int, ObstacleDimensions> Obstacles::m_Obstacles = std::map<int, ObstacleDimensions>();
int Obstacles::m_MouseOverIndex = -1;

void Obstacles::HandleObstacleCreation(olc::PixelGameEngine* pge)
{
	if (SimObject::m_MouseState == SimObject::MouseState::IDLE && pge->GetMouse(0).bPressed)
	{
		SimObject::m_MouseState = SimObject::MouseState::DRAWING_OBSTACLE;
		m_InitialMousePos = pge->GetMousePos();
	}

	if (SimObject::m_MouseState == SimObject::MouseState::DRAWING_OBSTACLE && pge->GetMouse(0).bReleased)
	{
		SimObject::m_MouseState = SimObject::MouseState::IDLE;
		m_Obstacles.insert({ m_ObstacleCount, ObstacleDimensions(m_InitialMousePos, pge->GetMousePos(), olc::CYAN) });
		m_ObstacleCount++;
	}
}

void Obstacles::HandleObstacleDeletion(olc::PixelGameEngine* pge)
{
	if (pge->GetKey(olc::D).bPressed)
	{
		if (m_MouseOverIndex != -1)
		{
			m_Obstacles.erase(m_MouseOverIndex);
		}
		else
		{
			m_Obstacles.clear();
			m_ObstacleCount = 0;
		}

		m_MouseOverIndex = -1;
	}
}

void Obstacles::Update(olc::PixelGameEngine* pge)
{
	HandleObstacleCreation(pge);
	HandleObstacleDeletion(pge);
}

void Obstacles::Draw(olc::PixelGameEngine * pge)
{
	// Draw All Obstacles.
	for (auto const& o : m_Obstacles)
	{
		pge->FillRect(o.second.TopLeft, o.second.Size, o.second.Color);
	}

	// Handle Rendering while Creating Obstacles.
	if (m_MouseState == MouseState::DRAWING_OBSTACLE)
	{
		auto dims = ObstacleDimensions(m_InitialMousePos, pge->GetMousePos());
		pge->FillRect(dims.TopLeft, dims.Size, olc::CYAN);
	}

	// Handle Highlight Color.
	if (IsPointIntersecting(pge->GetMousePos(), true))
	{
		if (m_MouseOverIndex != -1)
			m_Obstacles[m_MouseOverIndex].Color = olc::DARK_CYAN;
	}
	else
	{
		if (m_MouseOverIndex != -1)
			m_Obstacles[m_MouseOverIndex].Color = olc::CYAN;

		m_MouseOverIndex = -1;
	}
}

bool Obstacles::IsPointIntersecting(const olc::vf2d& p, bool isMouse)
{
	for (auto const& o : m_Obstacles)
	{
		if (p.x > o.second.TopLeft.x && p.y > o.second.TopLeft.y &&
			p.x < o.second.BottomRight.x && p.y < o.second.BottomRight.y)
		{
			if (isMouse)
				m_MouseOverIndex = o.first;
			return true;
		}
	}

	return false;
}