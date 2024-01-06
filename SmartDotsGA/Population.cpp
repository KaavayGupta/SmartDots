#include "Population.h"
#include "Utility.h"

Population::Population(size_t size, Goal* goal) : m_Goal(goal)
{
    for (int i = 0; i < size; i++)
    {
        m_Dots.push_back(Dot(goal));
    }
}

void Population::Update(olc::PixelGameEngine* pge)
{
    for (int i = 0; i < m_Dots.size(); i++)
    {
        if (m_Dots[i].m_DNA.m_Step > m_MinStep)
            m_Dots[i].m_IsDead = true;
        else
            m_Dots[i].Update(pge);
    }
}

void Population::Show(olc::PixelGameEngine* pge, bool showOnlyBest)
{
    if (m_Gen > 1 && showOnlyBest)
    {
        m_Dots[m_BestDot].Draw(pge);
    }
    else
    {
        for (int i = 0; i < m_Dots.size(); i++)
        {
            m_Dots[i].Draw(pge);
        }
        m_Dots[0].Draw(pge);
    }
}

void Population::CalculateFitness()
{
    for (int i = 0; i < m_Dots.size(); i++)
    {
        m_Dots[i].CalculateFitness();
    }
}

bool Population::AllDotsDead()
{
    for (int i = 0; i < m_Dots.size(); i++)
    {
        if (!m_Dots[i].m_IsDead && !m_Dots[i].m_ReachedGoal)
        {
            return false;
        }
    }

    return true;
}

void Population::NatrualSelection()
{
    std::vector<Dot> newDots;
    SetBestDot();
    CalculateFitnessSum();

    // Ensure the best dot from prev gen exists in new gen to compensate if gen is mutated negatively.
    newDots.push_back(m_Dots[m_BestDot].CreateChild());
    newDots[0].m_IsBest = true;

    for (int i = 1; i < m_Dots.size(); i++)
    {
        //TODO: implement crossover
        newDots.push_back(m_Dots[GetParentIndex()].CreateChild());
    }

    m_Dots = newDots;
    m_Gen++;
}

void Population::Mutate()
{
    for (int i = 1; i < m_Dots.size(); i++)
        m_Dots[i].m_DNA.Mutate(0.01f);
}

void Population::Reset()
{
    m_FitnessSum = 0.0f;
    m_MinStep = 10000;
    m_BestDot = -1;
    m_Gen = 1;

    for (int i = 0; i < m_Dots.size(); i++)
    {
        m_Dots[i] = Dot(m_Goal);
    }
}

int Population::GetParentIndex()
{
    float randFit = GetRandomFloat(0.0f, m_FitnessSum);
    float runningSum = 0.0f;
    for (int i = 0; i < m_Dots.size(); i++)
    {
        runningSum += m_Dots[i].m_Fitness;
        if (randFit <= runningSum)
            return i;
    }

    return -1;
}

void Population::CalculateFitnessSum()
{
    m_FitnessSum = 0.0f;
    for (int i = 0; i < m_Dots.size(); i++)
        m_FitnessSum += m_Dots[i].m_Fitness;
}

void Population::SetBestDot()
{
    float maxFit = 0.0f;
    int maxIndex = 0;
    for (int i = 0; i < m_Dots.size(); i++)
    {
        if (m_Dots[i].m_Fitness > maxFit)
        {
            maxFit = m_Dots[i].m_Fitness;
            maxIndex = i;
        }
    }

    m_BestDot = maxIndex;

    if (m_Dots[m_BestDot].m_ReachedGoal)
        m_MinStep = m_Dots[m_BestDot].m_DNA.m_Step;
}