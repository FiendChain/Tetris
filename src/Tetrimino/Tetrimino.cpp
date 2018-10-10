#include "Tetrimino.hpp"
#include <SFML/Graphics.hpp>

Tetrimino::Tetrimino(int posX, int posY, unsigned int size)
    : m_PosX(posX), m_PosY(posY),
      m_Size(size)
{
    
}

bool Tetrimino::RotateClockwise(BlockGrid& blocks, int xOffset, int yOffset)
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
    if (!CheckCollision(blocks, tmpLayout, xOffset, yOffset))
    {
        layout = tmpLayout;
        m_PosX += xOffset;
        m_PosY += yOffset;
        return true;
    }
    return false;
}

bool Tetrimino::RotateAntiClockwise(BlockGrid& blocks, int xOffset, int yOffset)
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
    if (!CheckCollision(blocks, tmpLayout, xOffset, yOffset))
    {
        layout = tmpLayout;
        m_PosX += xOffset;
        m_PosY += yOffset;
        return true;
    }
    return false;
        
}

bool Tetrimino::Move(BlockGrid& blocks, Direction direction, unsigned int distance)
{
    switch (direction)
    {
    case Direction::Right:
        if (!CheckCollision(blocks, GetLayout(), distance, 0))
        {
            m_PosX += distance;
            return true;
        }
        break;
    case Direction::Left:
        if (!CheckCollision(blocks, GetLayout(), -distance, 0))
        {
            m_PosX -= distance;
            return true;
        }
        break;
    case Direction::Down:
        if (!CheckCollision(blocks, GetLayout(), 0, distance))
        {
            m_PosY += distance;
            return true;
        }
        break;
    }
    return false;
}

void Tetrimino::Draw(sf::RenderTarget* target)
{
    UpdateLayoutLocation();
    for (auto& row: GetLayout())
    {
        for (auto& block: row)
        {
            if (block)
            {
                target->draw(*block);
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
    UpdateLayoutLocation(); // when placing into block grid, update location
    WriteToGrid(blocks);
}

void Tetrimino::SetPosition(int posX, int posY)
{
    m_PosX = posX;
    m_PosY = posY;
}

void Tetrimino::SetSize(unsigned int size)
{
    m_Size = size;
    for (auto& row: GetLayout())
    {
        for (auto& block: row)
        {
            if (block) block->setSize(sf::Vector2f(size, size));
        }
    }
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
