#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "BlockGrid.hpp"

typedef std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> TetriminoLayout;

class Tetrimino
{
    public:
        enum Direction { Left, Right, Down };
    private:
        int m_PosX, m_PosY;
        unsigned int m_Size;
    public:
        Tetrimino(int posX, int posY, unsigned int size);
        virtual bool RotateClockwise(BlockGrid& tetriminos, int xOffset=0, int yOffset=0);
        virtual bool RotateAntiClockwise(BlockGrid& tetriminos, int xOffset=0, int yOffset=0);
        virtual bool Move(BlockGrid& tetriminos, Direction direction, unsigned int distance=1);
        virtual TetriminoLayout& GetLayout() = 0;
        void SetPosition(int posX, int posY);
        inline sf::Vector2u GetPosition() const { return sf::Vector2u(m_PosX, m_PosY); }
        void SetSize(unsigned int size);
        inline unsigned int GetSize() const { return m_Size; }
        void Draw(sf::RenderTarget* target);
        void Place(BlockGrid& blocks);
    private:
        bool CheckCollision(BlockGrid& blocks, TetriminoLayout& layout, int xOffset, int yOffset) const;
        void WriteToGrid(BlockGrid& blocks);
        void UpdateLayoutLocation();
};

