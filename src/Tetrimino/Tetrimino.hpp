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
        void RotateClockwise(BlockGrid& tetriminos);
        void RotateAntiClockwise(BlockGrid& tetriminos);
        void Move(BlockGrid& tetriminos, Direction direction);
        virtual TetriminoLayout& GetLayout() = 0;
        void Draw(sf::RenderWindow& window);
        void Place(BlockGrid& blocks);
    private:
        bool CheckCollision(BlockGrid& blocks, TetriminoLayout& layout, int xOffset, int yOffset) const;
        void WriteToGrid(BlockGrid& blocks);
        void UpdateLayoutLocation();
};

