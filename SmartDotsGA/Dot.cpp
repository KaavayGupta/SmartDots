#include "Dot.h"

#include "Utility.h"

Dot::Dot(Goal* goal) : m_Goal(goal)
{
    m_Position.x = SimObject::m_ScreenWidth / 2;
    m_Position.y = SimObject::m_ScreenHeight - 10;
    m_Velocity.x = m_Velocity.y = 0.0f;;
    m_Acceleration.x = m_Acceleration.y = 0.0f;
}

void Dot::Move()
{
    if (m_DNA.m_Directions.size() > m_DNA.m_Step)
    {
        m_Acceleration = m_DNA.m_Directions[m_DNA.m_Step];
        m_DNA.m_Step++;
    }
    else
    {
        m_IsDead = true;
    }

    m_Velocity += m_Acceleration;
    float mag = m_Velocity.mag();
    if (mag > m_MaxVelocity)
    {
        m_Velocity /= mag;
        m_Velocity *= m_MaxVelocity;
    }
    m_Position += m_Velocity;
}

void Dot::Update(olc::PixelGameEngine* pge)
{
    if (!m_IsDead && !m_ReachedGoal)
    {
        Move();
        if (m_Position.x < 1.5f || m_Position.x > m_ScreenWidth - 1.5f || m_Position.y < 1.5f || m_Position.y > m_ScreenHeight - 1.5f)
            m_IsDead = true;
        else if (SqrDistance(m_Position, m_Goal->m_Position) <= 64.0f)
            m_ReachedGoal = true;
        else if (Obstacles::IsPointIntersecting(m_Position))
            m_IsDead = true;
    }
}

void Dot::Draw(olc::PixelGameEngine* pge)
{
    pge->FillCircle(m_Position, 3, m_IsBest ? olc::GREEN : olc::BLACK);
}

void Dot::CalculateFitness()
{
    if (m_ReachedGoal)
    {
        m_Fitness = 1.0f / 16.0f + 10000.0f / (float)(m_DNA.m_Step * m_DNA.m_Step);
    }
    else
    {
        float sqrDistToGoal = SqrDistance(m_Position, m_Goal->m_Position);
        m_Fitness = 1.0f / (sqrDistToGoal);
    }
}

Dot Dot::CreateChild()
{
    Dot child = Dot(m_Goal);
    child.m_DNA = m_DNA.Clone();
    return child;
}