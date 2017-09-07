#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <thread>
#include "Block.h"
#include "BlockWorking.h"

int main()
{
	srand(time(0));

	sf::Texture play_t, stop_t;
	play_t.loadFromFile("images/play.png");
	stop_t.loadFromFile("images/stop.png");

	sf::Sprite play, stop;
	play.setTexture(play_t);
	stop.setTexture(stop_t);

	sf::RenderWindow app(sf::VideoMode::getDesktopMode(), "Doooo", sf::Style::Fullscreen);
	app.setFramerateLimit(60);

	int x = 100;
	int y = 200;
	std::vector< std::vector <Block> > vec;

	vec = create_rectangles_to_array(app,false);
	bool do_next_gen = true;
	
	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) {
				app.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				app.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			{
				vec = create_rectangles_to_array(app,false);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) 
			{
				vec = create_rectangles_to_array(app,true);
				do_next_gen = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
			{
				if (!do_next_gen)
				{
					for (int i = 0; i < vec.size(); i++)
					{
						for (int j = 0; j < vec.at(i).size(); j++)
						{
							if (vec.at(i).at(j).is_mouse_over(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
							{
								vec.at(i).at(j).set_alive(!vec.at(i).at(j).is_alive());
								//app.draw(vec.at(i).at(j).get_block());
							}

						}
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				do_next_gen = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				do_next_gen = false;
			}
		}

		//app.clear(sf::Color(255, 255, 255));
		if (do_next_gen)
		{
			next_gen(vec);
		}
		draw_rectangles_on_screen(vec, app);

		if (do_next_gen)
			app.draw(play);
		else
			app.draw(stop);

		app.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}




	return 0;
}
