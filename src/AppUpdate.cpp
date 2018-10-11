#include "App.hpp"
#include <SFML/Graphics.hpp>

void App::Update()
{
    int idleTime = 0;
    sf::Time lastUpdate = m_Clock.getElapsedTime();
    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > 1000)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            if (!m_CurrentTetrimino->Move(m_Blocks, Tetrimino::Direction::Down))
            {
                idleTime++;
                if (idleTime >= 2)
                {
                    Place();
                }
            }
            m_Mutex.unlock();
        }
    }
}

void App::UpdateFutureTetriminoLayouts()
{
    int currentPosY = 0;
    for (unsigned int i = 0; i < m_FutureTetriminos.size(); i++)
    {
        auto& block = m_FutureTetriminos.at(i);
        if (block)
        {
            currentPosY++;
            block->SetPosition(1, currentPosY);
            currentPosY += block->GetLayout().size() + 1;
        }
    }
}