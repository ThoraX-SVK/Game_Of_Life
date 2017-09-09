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


	sf::Font font;
	font.loadFromFile("BebasNeue.otf");

	sf::Text run;
	run.setFont(font);
	run.setPosition(sf::Vector2f(app.getSize().x / 2 - 120, 150));
	run.setString("Run!");
	run.setCharacterSize(150);

	sf::Text exit;
	exit.setFont(font);
	exit.setPosition(sf::Vector2f(app.getSize().x / 2 - 118, 350));
	exit.setString("Exit");
	exit.setCharacterSize(150);

	

	int x = 100;
	int y = 200;
	std::vector< std::vector <Block> > vec;
	bool do_next_gen;
	bool in_menu = true;

	while (app.isOpen())
	{

		while (in_menu)
		{
			sf::Event e;
			while (app.pollEvent(e))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2f mouse = (sf::Vector2f) sf::Mouse::getPosition();
					sf::FloatRect txt = run.getGlobalBounds();
					sf::FloatRect exit_t = exit.getGlobalBounds();
					
					if (txt.contains(mouse))
					{
						vec = create_rectangles_to_array(app, false);
						do_next_gen = true;
						in_menu = false;
						break;
					}
					else if (exit_t.contains(mouse))
					{
						app.close();
					}

				}
			}
			app.clear(sf::Color(0, 0, 0));
			app.draw(run);
			app.draw(exit);
			app.display();
		}

		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) {
				app.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				in_menu = true;
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
								app.draw(vec.at(i).at(j).get_block());
								app.display();
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
