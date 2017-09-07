#ifndef BLOCKWORKING_H_INCLUDED
#define BLOCKWORKING_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Block.h"

std::vector <std::vector<Block> > create_rectangles_to_array(sf::RenderWindow &app, bool all_black);
void draw_rectangles_on_screen(std::vector <std::vector<Block> > &vec, sf::RenderWindow &app);
void next_gen(std::vector <std::vector<Block> > &vec);





#endif // !BLOCKWORKING_H_INCLUDED

