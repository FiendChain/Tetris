#include "Tetrimino.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

namespace blocks
{

// L
class LShape: public Tetrimino
{
    private:
        TetriminoLayout m_Layout;
    public:
        LShape(int posX, int posY, unsigned int size);
        inline TetriminoLayout& GetLayout() override { return m_Layout; }
    private:
        std::shared_ptr<sf::RectangleShape> CreateBlock(unsigned int size);
};

// J
class JShape: public Tetrimino
{
    private:
        TetriminoLayout m_Layout;
    public:
        JShape(int posX, int posY, unsigned int size);
        inline TetriminoLayout& GetLayout() override { return m_Layout; }
    private:
        std::shared_ptr<sf::RectangleShape> CreateBlock(unsigned int size);
};

// O
class OShape: public Tetrimino
{
    private:
        TetriminoLayout m_Layout;
    public:
        OShape(int posX, int posY, unsigned int size);
        inline TetriminoLayout& GetLayout() override { return m_Layout; }
    private:
        std::shared_ptr<sf::RectangleShape> CreateBlock(unsigned int size);
};

// T
class TShape: public Tetrimino
{
    private:
        TetriminoLayout m_Layout;
    public:
        TShape(int posX, int posY, unsigned int size);
        inline TetriminoLayout& GetLayout() override { return m_Layout; }
    private:
        std::shared_ptr<sf::RectangleShape> CreateBlock(unsigned int size);
};


// Z
class ZShape: public Tetrimino
{
    private:
        TetriminoLayout m_Layout;
    public:
        ZShape(int posX, int posY, unsigned int size);
        inline TetriminoLayout& GetLayout() override { return m_Layout; }
    private:
        std::shared_ptr<sf::RectangleShape> CreateBlock(unsigned int size);
};

// S
class SShape: public Tetrimino
{
    private:
        TetriminoLayout m_Layout;
    public:
        SShape(int posX, int posY, unsigned int size);
        inline TetriminoLayout& GetLayout() override { return m_Layout; }
    private:
        std::shared_ptr<sf::RectangleShape> CreateBlock(unsigned int size);
};

class IShape: public Tetrimino
{
    private:
        TetriminoLayout m_Layout;
    public:
        IShape(int posX, int posY, unsigned int size);
        inline TetriminoLayout& GetLayout() override { return m_Layout; }
    private:
        std::shared_ptr<sf::RectangleShape> CreateBlock(unsigned int size);
};

}