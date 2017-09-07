#include "Block.h"

Block::Block(unsigned int x, unsigned int y, unsigned int size, bool alive)
{
	this->next_gen_state = false;
	this->alive = alive;
	block.setPosition(x, y);

	if (alive)
	{
		block.setFillColor(sf::Color(255, 255, 255));
	}
	else
	{
		block.setFillColor(sf::Color(0, 0, 0));
	}
	block.setSize(sf::Vector2f(size, size));
}

Block::~Block()
{

}

void Block::set_alive(bool alive)
{
	this->alive = alive;

	if (alive)
	{
		block.setFillColor(sf::Color(255, 255, 255));
	}
	else
	{
		block.setFillColor(sf::Color(0, 0, 0));
	}

}