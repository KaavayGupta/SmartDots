#include "DNA.h"
#include "Utility.h"

DNA::DNA(size_t size) : m_Size(size)
{
    Randomize();
}

void DNA::Randomize()
{
    for (int i = 0; i < m_Size; i++)
    {
        float randAngle = GetRandomFloat(0.0f, 6.28f);
        m_Directions.push_back({ std::cos(randAngle), std::sin(randAngle) });
    }
}

DNA DNA::Clone()
{
    DNA cloned = DNA(m_Directions.size());
    cloned.m_Directions = m_Directions;
    return cloned;
}

void DNA::Mutate(float mutationRate)
{
    for (int i = 0; i < m_Directions.size(); i++)
    {
        float prob = GetRandomFloat(0.0f, 1.0f);
        if (prob < mutationRate)
        {
            float randAngle = GetRandomFloat(0.0f, 6.28f);
            m_Directions[i].x = std::cos(randAngle);
            m_Directions[i].y = std::sin(randAngle);
        }
    }
}