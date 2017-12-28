#include "Map.h"

Map::Map(sf::Sprite & l, sf::View & v)
{
	view = &v;
	look = &l;
	Locks();
	Font();
}

Map::Map(sf::Sprite &l, sf::View & v, Enemy& p)
{
	view = &v;
	look = &l;
	f.push_back(p);
	Locks();
	Font();
}

Map::Map(sf::Sprite & l,  sf::View & v, Enemy& p, Enemy & p2)
{
	view = &v;
	look = &l;
	f.push_back(p);
	f.push_back(p2);
	Locks();
	Font();
}

Map::~Map()
{
}

void Map::Font()
{
	//Reading font
	if (!font_text.loadFromFile("font/arial.ttf"))
		throw("Font error");
}

void Map::set_Doors(Collision & a)
{
	doors.push_back(a);
}

void Map::set_Doors(Collision & a, Collision & b)
{
	doors.push_back(a);
	doors.push_back(b);
}

void Map::set_Doors(Collision & a, Collision & b, Collision & c)
{
	doors.push_back(a);
	doors.push_back(b);
	doors.push_back(c);
}

void Map::set_Others(Object & a)
{
	others.push_back(a);
	counter_other = 1;
}

void Map::set_Others(Object & a, Object & b)
{
	others.push_back(a);
	others.push_back(b);

	counter_other = 2;
}

void Map::Locks()
{
	upLock = Collision(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(0.0f, -(sizeBG.y) / 2.0f - 20.0f));
	leftLock = Collision(nullptr, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(-(sizeBG.x / 2.0f), 0.0f));
	rightLock = Collision(nullptr, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(sizeBG.x / 2.0f + 5.f, 0.0f));
	downLock = Collision(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(0.0f, sizeBG.y / 2.0f - 30.f));
}

void Map::Player_Lock(Player & p)
{
	//Locking room
	upLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
	rightLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
	leftLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
	downLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
}

void Map::Player_Others(Player & p)
{
	std::vector<Object>::iterator i;
	for (i = others.begin(); i != others.end(); ++i)
	{
		if (i->GetCollider().CheckCollision(p.GetCollider(), 1.0f))
		{

		}
	}
}

void Map::Player_Doors(Player& p)
{
	std::vector<Collision>::iterator i;
	for (i = doors.begin(); i != doors.end(); ++i)
	{
		if (i->GetCollider().CheckCollision(p.GetCollider(), 1.0f))
		{
			//bool
		}
	}
}

void Map::Player_Bots(Player & p, sf::RenderWindow* window)
{
	std::vector<Enemy>::iterator i;
	for (i = f.begin(); i != f.end(); ++i)
	{
		if (p.GetCollider().CheckCollision(i->GetCollider(), 0.0f))
		{
			Lose(window);
		}
	}

}
void Map::Figures_Direction()
{
	std::vector<Enemy>::iterator i;
	for (i = f.begin(); i != f.end(); ++i)
	{
		Figure_Direction(*i,upLock, downLock, i->getOne(), i->getTwo());
	}
}

void Map::Figure_Direction(Enemy& p, Collision& one, Collision& two, int i, int k)
{
	if (one.GetCollider().CheckCollision(p.GetCollider(), 1.0f))
	{
		p.setDirection(i);

	}
	else if (two.GetCollider().CheckCollision(p.GetCollider(), 1.0f))
	{
		p.setDirection(k);
	}
}

void Map::Lose(sf::RenderWindow* window)
{
	lose_text.setFont(font_text);
	lose_text.setFillColor(sf::Color::White);
	lose_text.setCharacterSize(100);
	lose_text.setPosition(0, 0);
	lose_text.setString("You lost!");

	window->clear();
	window->setView(*view);
	window->draw(lose_text);
	window->display();
	sf::Event evnt;
	while (evnt.KeyPressed != sf::Keyboard::Return)
	{
		if (evnt.KeyPressed == sf::Keyboard::Return)
			break;
	}

	window->close();
}

void Map::Draw(sf::RenderWindow* window)
{
	//Drawing on the screen
	window->clear();
	window->setView(*view);
	window->draw(*look);

	std::vector<Enemy>::iterator i;
	for (i = f.begin(); i != f.end(); ++i)
	{
		i->Draw(*window);
	}

	std::vector<Object>::iterator k;
	for (k = others.begin(); k != others.end(); ++k)
	{
		k->Draw(*window);
	}
}