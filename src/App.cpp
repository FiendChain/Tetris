#include "App.hpp"
#include "Tetrimino/Tetrimino.hpp"
#include "Tetrimino/StandardBlocks.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

App::App(unsigned int width, unsigned int height, unsigned int fps, unsigned int blockSize)
    : m_Width(width), m_Height(height), m_Fps(fps), 
      m_BlockSize(blockSize), m_TotalColumns(width/blockSize), m_TotalRows(height/blockSize),
      m_Window(sf::VideoMode(width, height), "Tetris"),
      m_Blocks(width/blockSize, height/blockSize, blockSize)
{
    m_CurrentTetrimino = GetRandomBlock();
}

App::~App()
{

}

void App::Run()
{
    sf::Thread updateThread(std::bind(&Update, this));
    updateThread.launch();
    while (m_Window.isOpen())
    {
        Render();
        PollEvents();
    }
}

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
            case sf::Keyboard::Space:
                Place();
                break;
            }
        }
    }
}

void App::Render()
{
    m_Window.clear(sf::Color::White);
    m_CurrentTetrimino->Draw(m_Window);
    m_Blocks.Draw(m_Window);
    m_Window.display();
}

void App::Update()
{
    sf::Time lastUpdate = m_Clock.getElapsedTime();
    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > 1000)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_CurrentTetrimino->Move(m_Blocks, Tetrimino::Direction::Down);
        }
    }
}

void App::Place()
{
    m_CurrentTetrimino->Place(m_Blocks);
    m_CurrentTetrimino = GetRandomBlock();
    m_Blocks.CheckLineClear();
}

std::unique_ptr<Tetrimino> App::GetRandomBlock()
{
    static int i = 0;
    if (i < 6)
        i++;
    else    
        i = 0;
    switch (i)
    {
    case 0:
        return std::make_unique<blocks::LShape>(0, 0, m_BlockSize);
    case 1:
        return std::make_unique<blocks::JShape>(0, 0, m_BlockSize);
    case 2:
        return std::make_unique<blocks::OShape>(0, 0, m_BlockSize);
    case 3:
        return std::make_unique<blocks::TShape>(0, 0, m_BlockSize);
    case 4:
        return std::make_unique<blocks::ZShape>(0, 0, m_BlockSize);
    case 5:
        return std::make_unique<blocks::SShape>(0, 0, m_BlockSize);
    case 6:
    default:
        return std::make_unique<blocks::IShape>(0, 0, m_BlockSize); 
    }
}