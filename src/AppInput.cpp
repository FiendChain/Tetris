#include "App.hpp"

void App::PollEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            m_Window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                m_CurrentTetrimino->RotateClockwise(m_Blocks);
                break;
            case sf::Keyboard::LControl:
                m_CurrentTetrimino->RotateAntiClockwise(m_Blocks);
                break;
            case sf::Keyboard::Left:
                m_CurrentTetrimino->Move(m_Blocks, Tetrimino::Direction::Left);
                break;
            case sf::Keyboard::Right:
                m_CurrentTetrimino->Move(m_Blocks, Tetrimino::Direction::Right);
                break;
            case sf::Keyboard::Down:
                m_CurrentTetrimino->Move(m_Blocks, Tetrimino::Direction::Down);
                break;
            case sf::Keyboard::LShift:
                Store();
                break;
            case sf::Keyboard::Space:
                Place();
                break;
            case sf::Keyboard::R:
                Reset();
                break;
            }
        }
    }
}

void App::Place()
{
    m_CurrentTetrimino->Place(m_Blocks);

    m_CurrentTetrimino = m_FutureTetriminos[0]; 
    m_FutureTetriminos.erase(m_FutureTetriminos.begin());
    
    auto block = GetRandomBlock();
    m_FutureTetriminos.push_back(block);
    UpdateFutureTetriminoLayouts();
    
    m_CurrentTetrimino->SetPosition(m_SpawnX, m_SpawnY);
    m_CurrentTetrimino->SetSize(m_BlockSize);

    m_TotalLinesCleared += m_Blocks.CheckLineClear();
}

void App::Store()
{
    std::shared_ptr<Tetrimino> storedTetrimino = m_StoredTetrimino;
    m_StoredTetrimino = m_CurrentTetrimino;
    m_StoredTetrimino->SetPosition(1, 1);

    m_CurrentTetrimino = storedTetrimino;
    if (!m_CurrentTetrimino) m_CurrentTetrimino = GetRandomBlock();
    m_CurrentTetrimino->SetPosition(m_SpawnX, m_SpawnY);
}

void App::Reset()
{
    CreateGame();
    m_TotalLinesCleared = 0;
}