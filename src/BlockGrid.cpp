#include "BlockGrid.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

BlockGrid::BlockGrid(unsigned int totalColumns, unsigned int totalRows, unsigned int gridSize)
    : m_TotalColumns(totalColumns), m_TotalRows(totalRows), m_GridSize(gridSize)
{
    for (unsigned int row = 0; row < m_TotalRows; row++)
    {
        m_Blocks.push_back(std::vector<std::shared_ptr<sf::RectangleShape>>(m_TotalColumns));
    }
}

void BlockGrid::Draw(sf::RenderWindow& window) const
{
    for (unsigned int row = 0; row < m_TotalRows; row++)
    {
        for (unsigned int col = 0; col < m_TotalColumns; col++)
        {
            auto block = m_Blocks[row][col];
            if (block) 
            {
                window.draw(*block.get());
            }
        }
    }
}

void BlockGrid::CheckLineClear()
{
    int rowsRemoved = 0;
    for (int row = 0; row < m_TotalRows-rowsRemoved; row++)
    {
        bool isRowFull = true;
        for (int col = 0; col < m_TotalColumns; col++)
        {
            if (!m_Blocks[row][col])
            {
                isRowFull = false;
                break;
            }
        }
        if (isRowFull)
        {
            m_Blocks.erase(m_Blocks.begin()+row);
            rowsRemoved++;
            row--;
        }
    }
    for (int row = 0; row < rowsRemoved; row++)
    {
        m_Blocks.insert(m_Blocks.begin(), std::vector<std::shared_ptr<sf::RectangleShape>>(m_TotalColumns));
    }
    UpdateBlockLocations();   
}

void BlockGrid::UpdateBlockLocations()
{
    for (unsigned int row = 0; row < m_TotalRows; row++)
    {
        for (unsigned int col = 0; col < m_TotalColumns; col++)
        {
            auto block = m_Blocks[row][col];
            if (block) 
            {
                block->setPosition(sf::Vector2f(col*m_GridSize, row*m_GridSize));
            }
        }
    }
}