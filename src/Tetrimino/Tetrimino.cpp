#include "Tetrimino.hpp"
#include <SFML/Graphics.hpp>

Tetrimino::Tetrimino(int posX, int posY, unsigned int size)
    : m_PosX(posX), m_PosY(posY),
      m_Size(size)
{
    // UpdateLayoutLocation();
}

void Tetrimino::RotateClockwise(BlockGrid& blocks)
{
    auto& layout = GetLayout();
    TetriminoLayout tmpLayout = {};
    bool rowExists = true;
    for (int col = 0; rowExists; col++)
    {
        std::vector<std::shared_ptr<sf::RectangleShape>> tmpRow(0);
        rowExists = false;
        for (int row = layout.size()-1; row >= 0; row--)
        {
            auto& layoutRow = layout[row];
            if (col < layoutRow.size())
            {
                tmpRow.push_back(layoutRow[col]);
                rowExists = true;
            }
            else
            {
                tmpRow.push_back(nullptr);
            }
        }
        if (rowExists)
            tmpLayout.push_back(tmpRow);
    }
    if (!CheckCollision(blocks, tmpLayout, 0, 0))
    {
        layout = tmpLayout;
        UpdateLayoutLocation();
    }
}

void Tetrimino::RotateAntiClockwise(BlockGrid& blocks)
{
    auto& layout = GetLayout();
    TetriminoLayout tmpLayout = {};
    bool rowExists = true;
    for (int col = 0; rowExists; col++)
    {
        std::vector<std::shared_ptr<sf::RectangleShape>> tmpRow(0);
        rowExists = false;
        for (int row = 0; row < layout.size(); row++)
        {
            auto& layoutRow = layout[row];
            if (col < layoutRow.size())
            {
                tmpRow.push_back(layoutRow[layoutRow.size()-col-1]);
                rowExists = true;
            }
            else
            {
                tmpRow.push_back(nullptr);
            }
        }
        if (rowExists)
            tmpLayout.push_back(tmpRow);
    }
    if (!CheckCollision(blocks, tmpLayout, 0, 0))
    {
        layout = tmpLayout;
        UpdateLayoutLocation();
    }
}

void Tetrimino::Move(BlockGrid& blocks, Direction direction)
{
    switch (direction)
    {
    case Direction::Right:
        if (!CheckCollision(blocks, GetLayout(), 1, 0))
        {
            m_PosX += 1;
            UpdateLayoutLocation();
        }
        break;
    case Direction::Left:
        if (!CheckCollision(blocks, GetLayout(), -1, 0))
        {
            m_PosX -= 1;
            UpdateLayoutLocation();
        }
        break;
    case Direction::Down:
        if (!CheckCollision(blocks, GetLayout(), 0, 1))
        {
            m_PosY += 1;
            UpdateLayoutLocation();
        }
        break;
    }

}

void Tetrimino::Draw(sf::RenderWindow& window)
{
    for (auto& row: GetLayout())
    {
        for (auto& block: row)
        {
            if (block)
            {
                window.draw(*block);
            }
        }
    }
}

void Tetrimino::Place(BlockGrid& blocks)
{
    // get min height from blocks
    int yOffset = 0;
    while (!CheckCollision(blocks, GetLayout(), 0, yOffset))
        yOffset += 1;
    m_PosY += yOffset-1;
    UpdateLayoutLocation();
    WriteToGrid(blocks);
}

void Tetrimino::UpdateLayoutLocation()
{
    for (unsigned int row = 0; row < GetLayout().size(); row++)
    {
        auto& gridRow = GetLayout()[row];
        for (unsigned int col = 0; col < gridRow.size(); col++)
        {
            auto& block = gridRow[col];
            if (block)
            {
                block->setPosition(sf::Vector2f((m_PosX+col)*m_Size, (m_PosY+row)*m_Size));
            }
        }
    }
}

void Tetrimino::WriteToGrid(BlockGrid& blocks)
{
    for (unsigned int row = 0; row < GetLayout().size(); row++)
    {
        auto& gridRow = GetLayout()[row];
        for (unsigned int col = 0; col < gridRow.size(); col++)
        {
            auto& block = gridRow[col];
            if (block)
            {
                int x = m_PosX+col;
                int y = m_PosY+row;
                if (x >= 0 && x < blocks.GetTotalColumns() && 
                    y >= 0 && y < blocks.GetTotalRows())
                    blocks[y][x] = block; 
            }
        }
    }
}

bool Tetrimino::CheckCollision(BlockGrid& blocks, TetriminoLayout& layout, int xOffset, int yOffset) const
{
    for (unsigned int row = 0; row < layout.size(); row++)
    {
        auto& layoutRow = layout[row];
        for (unsigned int col = 0; col < layoutRow.size(); col++)
        {
            auto& layoutBlock = layoutRow[col];
            if (layoutBlock)
            {
                int xPos = m_PosX+col+xOffset;
                int yPos = m_PosY+row+yOffset;
                if (xPos < 0 || xPos >= blocks.GetTotalColumns()) return true;
                if (yPos < 0 || yPos >= blocks.GetTotalRows())    return true;
                if (blocks[yPos][xPos])                           return true;
            }
        }
    }
    return false;
}
