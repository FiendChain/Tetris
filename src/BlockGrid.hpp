#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class BlockGrid
{
    private:
        std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> m_Blocks;
        const unsigned int m_TotalColumns, m_TotalRows, m_GridSize;
    public:
        BlockGrid(unsigned int totalColumns, unsigned int totalRows, unsigned int gridSize);
        std::vector<std::shared_ptr<sf::RectangleShape>>& operator [](int index) 
        {
            return m_Blocks[index];
        }
        inline unsigned int GetTotalColumns() const { return m_TotalColumns; }
        inline unsigned int GetTotalRows() const { return m_TotalRows; }
        void Draw(sf::RenderTarget* target) const;
        void CheckLineClear();
    private:
        void UpdateBlockLocations();
};