#include "App.hpp"
#include "Tetrimino/Tetrimino.hpp"
#include "Tetrimino/StandardBlocks.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <time.h>
#include <functional>

App::App(unsigned int width, unsigned int height, unsigned int fps, unsigned int blockSize)
    : m_Width(2*width), m_Height(height), m_Fps(fps), 
      m_BlockSize(blockSize), m_TotalColumns(width/blockSize), m_TotalRows(height/blockSize),
      m_Window(sf::VideoMode(2*width, height), "Tetris"),
      m_Blocks(width/blockSize, height/blockSize, blockSize),
      m_FutureTetriminos(5),
      m_RngEngine(time(NULL))
{
    m_CentrePanel.create(width, height);
    m_RightPanel.create(0.5*width, height);
    m_LeftPanel.create(0.5*width, height);

    m_SpawnX = m_TotalColumns/2 - 2; 
    m_SpawnY = 0;
    
    for (auto& block: m_FutureTetriminos) block = GetRandomBlock();
    UpdateFutureTetriminoLayouts();
    
    m_CurrentTetrimino = GetRandomBlock();
    m_StoredTetrimino = nullptr;
    
    m_Window.setFramerateLimit(m_Fps);
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
            case sf::Keyboard::LShift:
                Store();
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
    // centre panel
    m_CentrePanel.clear(sf::Color(0, 0, 0, 120));
    m_CurrentTetrimino->Draw(&m_CentrePanel);
    m_Blocks.Draw(&m_CentrePanel);
    m_CentrePanel.display();

    // right panel
    m_RightPanel.clear(sf::Color::Transparent);
    for (auto& block: m_FutureTetriminos)
    {
        if (block) block->Draw(&m_RightPanel);
    }
    m_RightPanel.display();

    // left panel
    m_LeftPanel.clear(sf::Color::Transparent);
    if (m_StoredTetrimino) m_StoredTetrimino->Draw(&m_LeftPanel);
    m_LeftPanel.display();

    // window
    m_Window.clear(sf::Color::White);
    
    sf::Sprite leftPanel(m_LeftPanel.getTexture());
    leftPanel.setPosition(sf::Vector2f(0, 0));
    m_Window.draw(leftPanel);

    static int centrePanelPosX = m_LeftPanel.getSize().x;
    sf::Sprite centrePanel(m_CentrePanel.getTexture());
    centrePanel.setPosition(sf::Vector2f(centrePanelPosX, 0));
    m_Window.draw(centrePanel);
    
    static int rightPanelPosX = centrePanelPosX + m_CentrePanel.getSize().x;
    sf::Sprite rightPanel(m_RightPanel.getTexture());
    rightPanel.setPosition(sf::Vector2f(rightPanelPosX, 0));
    m_Window.draw(rightPanel);

    

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

    m_CurrentTetrimino = m_FutureTetriminos[0]; 
    m_FutureTetriminos.erase(m_FutureTetriminos.begin());
    
    auto block = GetRandomBlock();
    m_FutureTetriminos.push_back(block);
    UpdateFutureTetriminoLayouts();
    
    m_CurrentTetrimino->SetPosition(m_SpawnX, m_SpawnY);
    m_CurrentTetrimino->SetSize(m_BlockSize);

    m_Blocks.CheckLineClear();
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

void App::UpdateFutureTetriminoLayouts()
{
    for (unsigned int i = 0; i < m_FutureTetriminos.size(); i++)
    {
        auto& block = m_FutureTetriminos.at(i);
        if (block)
        {
            block->SetPosition(1, 5*i+1);
        }
    }
}