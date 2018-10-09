#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tetrimino/Tetrimino.hpp"
#include "BlockGrid.hpp"

class App
{
    private:
        sf::RenderWindow m_Window;
        const unsigned int m_BlockSize, m_TotalColumns, m_TotalRows;
        const unsigned int m_Width, m_Height, m_Fps;
        BlockGrid m_Blocks;
        sf::Clock m_Clock;
        std::unique_ptr<Tetrimino> m_CurrentTetrimino;
    public:
        App(unsigned int width, unsigned int height, unsigned int fps, unsigned int blockSize=20);
        ~App();
        void Run();
    private:
        void PollEvents();
        void Render();
        void Update();
        void Place();
        std::unique_ptr<Tetrimino> GetRandomBlock();
};