#include "BlockWorking.h"

std::vector <std::vector<Block> > create_rectangles_to_array(sf::RenderWindow &app, bool all_black)
{
	uint8_t block_size = 10;

	std::vector< std::vector <Block> > vec;


	for (int i = 0; i < (app.getSize().x / block_size) + 1; i++)
	{
		std::vector<Block> riadok;

		for (int j = 0; j < (app.getSize().y / block_size) + 1; j++)
		{
			if (!all_black)
			{
				uint8_t rando = rand() % 2;


				Block b(i*block_size, j*block_size, block_size, rando);
				riadok.push_back(b);
			}
			else
			{
				Block b(i*block_size, j*block_size, block_size, false);
				riadok.push_back(b);
			}
		}

		vec.push_back(riadok);

	}

	return vec;
}

void draw_rectangles_on_screen(std::vector <std::vector<Block> > &vec, sf::RenderWindow &app)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec.at(i).size(); j++)
		{
			Block *b = &vec.at(i).at(j);

			app.draw(vec.at(i).at(j).get_block());
		}
	}
}

void next_gen(std::vector <std::vector<Block> > &vec) {

	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec.at(i).size(); j++)
		{
			uint8_t alive_around = 0;

			Block *b = &vec.at(i).at(j);


			if (i != 0)
			{
				if (vec.at(i - 1).at(j).is_alive())
				{
					alive_around++;
				}

				if (j != 0)
				{
					if (vec.at(i - 1).at(j - 1).is_alive())
					{
						alive_around++;
					}
				}
				if (j != vec.at(i).size() - 1)
				{
					if (vec.at(i - 1).at(j + 1).is_alive())
					{
						alive_around++;
					}
				}
			}

			if (i != vec.size() - 1)
			{
				if (vec.at(i + 1).at(j).is_alive())
				{
					alive_around++;
				}

				if (j != 0)
				{
					if (vec.at(i + 1).at(j - 1).is_alive())
					{
						alive_around++;
					}
				}
				if (j != vec.at(i).size() - 1)
				{
					if (vec.at(i + 1).at(j + 1).is_alive())
					{
						alive_around++;
					}
				}
			}

			if (j != 0)
			{
				if (vec.at(i).at(j - 1).is_alive())
				{
					alive_around++;
				}
			}
			if (j != vec.at(i).size() - 1)
			{
				if (vec.at(i).at(j + 1).is_alive())
				{
					alive_around++;
				}
			}

			if (b->is_alive()) {
				if (alive_around == 2 || alive_around == 3)
				{
					b->set_next_gen_state(true);
				}
				else
				{
					b->set_next_gen_state(false);
				}
			}
			else
			{
				if (alive_around == 3)
				{
					b->set_next_gen_state(true);
				}
				else
				{
					b->set_next_gen_state(false);
				}
			}
		}

	}

	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec.at(i).size(); j++)
		{
			Block *b = &vec.at(i).at(j);
			b->advance_generation();
		}
	}
}