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
        sf::RenderTexture m_CentrePanel;
        sf::RenderTexture m_RightPanel;
        sf::RenderTexture m_LeftPanel;
        const unsigned int m_BlockSize, m_TotalColumns, m_TotalRows;
        const unsigned int m_Width, m_Height, m_Fps;
        unsigned int m_SpawnX, m_SpawnY;
        BlockGrid m_Blocks;
        sf::Clock m_Clock;
        std::vector<std::shared_ptr<Tetrimino>> m_FutureTetriminos;
        std::shared_ptr<Tetrimino> m_CurrentTetrimino;
        std::shared_ptr<Tetrimino> m_StoredTetrimino;
        std::mt19937 m_RngEngine;
    public:
        App(unsigned int width, unsigned int height, unsigned int fps, unsigned int blockSize=20);
        ~App();
        void Run();
    private:
        void PollEvents();
        void Render();
        void Update();
        void Store();
        void Place();
        void UpdateFutureTetriminoLayouts();
        std::shared_ptr<Tetrimino> GetRandomBlock();
};