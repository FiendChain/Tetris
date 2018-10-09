#include "StandardBlocks.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

static std::shared_ptr<sf::RectangleShape> CreateGenericBlock(unsigned int size, const sf::Color& colour)
{
	std::shared_ptr<sf::RectangleShape> block = std::make_shared<sf::RectangleShape>(sf::Vector2f(size, size));
    block->setFillColor(colour);
    block->setOutlineColor(sf::Color::Black);
    block->setOutlineThickness(1.0f);
    return block;
}

namespace blocks
{

// L shape
LShape::LShape(int posX, int posY, unsigned int size)
    : Tetrimino(posX, posY, size),
      m_Layout {
        {CreateBlock(size), nullptr},
        {CreateBlock(size), nullptr},
        {CreateBlock(size), CreateBlock(size)}}
{}

std::shared_ptr<sf::RectangleShape> LShape::CreateBlock(unsigned int size)
{
	return CreateGenericBlock(size, sf::Color(239, 160, 2));
}

// j shape
JShape::JShape(int posX, int posY, unsigned int size)
    : Tetrimino(posX, posY, size),
	  m_Layout {
        {nullptr,			CreateBlock(size)},
        {nullptr, 			CreateBlock(size)},
        {CreateBlock(size), CreateBlock(size)}}
{}

std::shared_ptr<sf::RectangleShape> JShape::CreateBlock(unsigned int size)
{
	return CreateGenericBlock(size, sf::Color(1, 1, 240));
}

// o shape
OShape::OShape(int posX, int posY, unsigned int size)
    : Tetrimino(posX, posY, size),
      m_Layout {
          {CreateBlock(size), CreateBlock(size)},
          {CreateBlock(size), CreateBlock(size)}}
{}

std::shared_ptr<sf::RectangleShape> OShape::CreateBlock(unsigned int size)
{
	return CreateGenericBlock(size, sf::Color(240, 240, 1));
}

// t shape
TShape::TShape(int posX, int posY, unsigned int size)
    : Tetrimino(posX, posY, size),
      m_Layout {
        {nullptr,           CreateBlock(size), nullptr},
        {CreateBlock(size), CreateBlock(size), CreateBlock(size)}}
{}

std::shared_ptr<sf::RectangleShape> TShape::CreateBlock(unsigned int size)
{
	return CreateGenericBlock(size, sf::Color(160, 0, 241));
}

// z shape
ZShape::ZShape(int posX, int posY, unsigned int size)
    : Tetrimino(posX, posY, size),
      m_Layout {
        {CreateBlock(size), CreateBlock(size), nullptr},
        {nullptr,           CreateBlock(size), CreateBlock(size)}}
{}

std::shared_ptr<sf::RectangleShape> ZShape::CreateBlock(unsigned int size)
{
	return CreateGenericBlock(size, sf::Color(240, 1, 0));
}

// s shape
SShape::SShape(int posX, int posY, unsigned int size)
    : Tetrimino(posX, posY, size),
      m_Layout {
        {nullptr,           CreateBlock(size), CreateBlock(size),},
        {CreateBlock(size), CreateBlock(size), nullptr}}
{}

std::shared_ptr<sf::RectangleShape> SShape::CreateBlock(unsigned int size)
{
	return CreateGenericBlock(size, sf::Color(0, 240, 0));
}

// i shape
IShape::IShape(int posX, int posY, unsigned int size)
    : Tetrimino(posX, posY, size),
      m_Layout {
        {CreateBlock(size), CreateBlock(size), CreateBlock(size), CreateBlock(size)}}
{}

std::shared_ptr<sf::RectangleShape> IShape::CreateBlock(unsigned int size)
{
	return CreateGenericBlock(size, sf::Color(1, 240, 241));
}


}
