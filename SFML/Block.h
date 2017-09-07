#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <SFML\Graphics.hpp>

class Block
{
public:
	
	Block(unsigned int x, unsigned int y, unsigned int size, bool alive);
	~Block();
	sf::RectangleShape get_block() { return block; }
	int get_posx() { return block.getPosition().x; }
	int get_posy() { return block.getPosition().y; }
	sf::Color get_color() { return block.getFillColor(); }
	bool is_alive() { return alive; }
	bool is_mouse_over(int x, int y) {
		return x > get_posx() && x < get_posx() + block.getSize().x
			&& y > get_posy() && y < get_posy() + block.getSize().y;
	}

	void set_posx(unsigned int x) { block.setPosition(sf::Vector2f(x, block.getPosition().y)); }
	void set_posy(unsigned int y) { block.setPosition(sf::Vector2f(block.getPosition().x, y)); }
	void set_color(unsigned int r, unsigned int g, unsigned int b) { block.setFillColor(sf::Color(r, g, b)); }
	void set_alive(bool alive);

	void set_next_gen_state(bool next_gen) { next_gen_state = next_gen; }
	void advance_generation() { set_alive(next_gen_state); }

private:
	bool alive;
	bool next_gen_state;
	sf::RectangleShape block;
};

#endif // !BLOCK_H_INCLUDED

