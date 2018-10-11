#include "App.hpp"
#include "Tetrimino/Tetrimino.hpp"
#include "Tetrimino/StandardBlocks.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <time.h>
#include <functional>
#include <iostream>

#define MAX_BLOCK_WIDTH 6
#define TOTAL_DISPLAY_PANELS 2

App::App(unsigned int width, unsigned int height, unsigned int fps, unsigned int blockSize)
    : m_Width(width+MAX_BLOCK_WIDTH*TOTAL_DISPLAY_PANELS*blockSize), m_Height(height), m_Fps(fps), 
      m_BlockSize(blockSize), m_TotalColumns(width/blockSize), m_TotalRows(height/blockSize),
      m_Window(sf::VideoMode(width+MAX_BLOCK_WIDTH*TOTAL_DISPLAY_PANELS*blockSize, height), "Tetris"),
      m_Blocks(width/blockSize, height/blockSize, blockSize),
      m_FutureTetriminos(5), m_StoredTetrimino(nullptr),
      m_RngEngine(time(NULL)),
      m_TotalLinesCleared(0)
{
    m_SpawnX = m_TotalColumns/2 - 2; m_SpawnY = 0;

    m_CentrePanel.create(width, height);
    m_RightPanel.create(MAX_BLOCK_WIDTH*blockSize, height);
    m_LeftPanel.create(MAX_BLOCK_WIDTH*blockSize, height);

    CreateGame();
    
    m_Window.setFramerateLimit(m_Fps);
}

void App::CreateGame()
{
    m_Blocks.Reset();
    for (auto& block: m_FutureTetriminos) 
    {
        block = GetRandomBlock();
    }
    UpdateFutureTetriminoLayouts();
    m_CurrentTetrimino = GetRandomBlock();
    m_StoredTetrimino = nullptr;
}

void App::Run()
{
    sf::Thread updateThread(std::bind(&Update, this));
    updateThread.launch();

    int frameTime = 1000.0f/m_Fps;
    sf::Time lastUpdate = m_Clock.getElapsedTime();
    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > frameTime)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            Render();
            PollEvents();
            m_Mutex.unlock();
        }
    }
}

std::shared_ptr<Tetrimino> App::GetRandomBlock()
{
    static std::uniform_int_distribution<int> blockType(0, 6);
    switch (blockType(m_RngEngine))
    {
    case 0:
        return std::make_shared<blocks::LShape>(m_SpawnX, m_SpawnY, m_BlockSize);
    case 1:
        return std::make_shared<blocks::JShape>(m_SpawnX, m_SpawnY, m_BlockSize);
    case 2:
        return std::make_shared<blocks::OShape>(m_SpawnX, m_SpawnY, m_BlockSize);
    case 3:
        return std::make_shared<blocks::TShape>(m_SpawnX, m_SpawnY, m_BlockSize);
    case 4:
        return std::make_shared<blocks::ZShape>(m_SpawnX, m_SpawnY, m_BlockSize);
    case 5:
        return std::make_shared<blocks::SShape>(m_SpawnX, m_SpawnY, m_BlockSize);
    case 6:
    default:
        return std::make_shared<blocks::IShape>(m_SpawnX, m_SpawnY, m_BlockSize); 
    }
}