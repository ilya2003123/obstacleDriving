#include <SFML/Graphics.hpp>
#include <conio.h>
#include <ctime>

int main() 
{
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Car!");
	srand(NULL(time));

	sf::Texture T;
	T.loadFromFile("Paint/track.png");
	sf::Sprite track(T);

	sf::Texture c;
	c.loadFromFile("Paint/car.png");
	sf::Sprite car(c);
	car.setScale(0.5, 0.5);
	car.setPosition(50, 250);

	sf::Texture S;
	S.loadFromFile("Paint/stone.png");
	sf::Sprite stone[3];
	int se[3];
	for (int i = 0; i < 3; i++) 
	{
		stone[i].setTexture(S);
		stone[i].setTextureRect(sf::IntRect(0, 0, 110, 105));
		stone[i].setScale(1, 0.94);
		se[i] = rand() % 4;
		stone[i].setPosition(1000, 50 + 100 * se[i]);
	}
	float Frame = 0;
	int q = 0;
	bool game = true;

	sf::Texture GO;
	GO.loadFromFile("Paint/GameOver.png");
	sf::Sprite over(GO);
	over.setPosition(1000, 150);

	sf::Texture score;
	score.loadFromFile("Paint/score.png");
	sf::Sprite scoreore[5];
	float fs[5];
	for (int i = 0; i < 5; i++) 
	{
		scoreore[i].setTexture(score);
		scoreore[i].setTextureRect(sf::IntRect(0, 0, 44, 55));
		scoreore[i].setPosition(50 * i, 5);
		fs[i] = 0;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (game) 
		{
			sf::Vector2f ca = car.getPosition();

			if (!_kbhit())
				car.setTextureRect(sf::IntRect(0, 0, 180, 140));

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
			{
				if (ca.y > 45)
					car.move(0, -0.3);

				car.setTextureRect(sf::IntRect(180, 0, 180, 140));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
			{
				if (ca.y < 390)
					car.move(0, 0.3);

				car.setTextureRect(sf::IntRect(360, 0, 180, 140));
			}

			sf::Vector2f st[3];
			if (q < 10) 
			{
				stone[0].move(-0.5, 0);
				st[0] = stone[0].getPosition();
				if (st[0].x < -100) 
				{
					se[0] = rand() % 4;
					stone[0].setPosition(1000, 50 + 100 * se[0]);
					q++;
				}
			}
			else if (q >= 10 && q < 20)
				for (int i = 0; i < 2; i++) 
				{
					stone[i].move(-0.5, 0);
					st[i] = stone[i].getPosition();
					if (st[i].x < -100) 
					{
						se[i] = rand() % 4;
						stone[i].setPosition(1000, 50 + 100 * se[i]);
						q++;
					}
				}
			else if (q >= 20)
				for (int i = 0; i < 3; i++) 
				{
					stone[i].move(-0.5, 0);
					st[i] = stone[i].getPosition();
					if (st[i].x < -100) 
					{
						se[i] = rand() % 4;
						stone[i].setPosition(1000, 50 + 100 * se[i]);
						q++;
					}
				}

			Frame += 0.005;
			if (Frame > 7)
				Frame -= 7;
			for (int i = 0; i < 3; i++)
				stone[i].setTextureRect(sf::IntRect(110 * int(Frame), 0, 110, 105));

			for (int i = 0; i < 3; i++)
				if (car.getGlobalBounds().intersects(stone[i].getGlobalBounds()))
					game = false;

			fs[4] += 0.005;
			if (fs[4] > 10) 
			{
				fs[4] -= 10;

				fs[3]++;
				if (fs[3] > 9) 
				{
					fs[3] -= 10;

					fs[2]++;
					if (fs[2] > 9) 
					{
						fs[2] -= 10;

						fs[1]++;
						if (fs[1] > 9) 
						{
							fs[1] -= 10;

							fs[0]++;
							if (fs[0] > 9)
								fs[0] -= 10;
							scoreore[0].setTextureRect(sf::IntRect(44 * int(fs[0]), 0, 44, 55));
						}
						scoreore[1].setTextureRect(sf::IntRect(44 * int(fs[1]), 0, 44, 55));
					}
					scoreore[2].setTextureRect(sf::IntRect(44 * int(fs[2]), 0, 44, 55));
				}
				scoreore[3].setTextureRect(sf::IntRect(44 * int(fs[3]), 0, 44, 55));
			}
			scoreore[4].setTextureRect(sf::IntRect(44 * int(fs[4]), 0, 44, 55));
		}

		else if (!game)
			over.setPosition(50, 150);

		window.clear(sf::Color::White);
		window.draw(track);
		window.draw(car);
		for (int i = 0; i < 3; i++)
			window.draw(stone[i]);
		window.draw(over);
		for (int i = 0; i < 5; i++)
			window.draw(scoreore[i]);
		window.display();
	}

	return 0;
}