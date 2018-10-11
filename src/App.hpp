#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <vector>
#include "Tetrimino/Tetrimino.hpp"
#include "BlockGrid.hpp"

class App
{
    private:
        sf::RenderWindow m_Window;
        sf::RenderTexture m_LeftPanel, m_CentrePanel, m_RightPanel;
        const unsigned int m_BlockSize, m_TotalColumns, m_TotalRows;
        const unsigned int m_Width, m_Height, m_Fps;
        unsigned int m_SpawnX, m_SpawnY;
        unsigned int m_TotalLinesCleared;
        BlockGrid m_Blocks;
        sf::Clock m_Clock;
        std::vector<std::shared_ptr<Tetrimino>> m_FutureTetriminos;
        std::shared_ptr<Tetrimino> m_CurrentTetrimino;
        std::shared_ptr<Tetrimino> m_StoredTetrimino;
        std::mt19937 m_RngEngine;
        sf::Mutex m_Mutex;
    public:
        App(unsigned int width, unsigned int height, unsigned int fps, unsigned int blockSize=20);
        void Run();
    private:
        void CreateGame();
        void Render();
        void RenderPanel(const sf::RenderTexture& panel, const sf::Vector2f& position);
        void Update();
        void PollEvents(); // inputs
        void Store();
        void Place();
        void Reset();
        void UpdateFutureTetriminoLayouts(); // tetriminos
        std::shared_ptr<Tetrimino> GetRandomBlock();
};