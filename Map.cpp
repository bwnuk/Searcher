#include "Map.h"

Map::Map(sf::Sprite & l, sf::View & v)
{
	view = &v;
	look = &l;
	Font();
}

Map::Map(sf::Sprite &l, sf::View & v, Enemy& p)
{
	view = &v;
	look = &l;
	f.push_back(p);
	Font();
}

Map::Map(sf::Sprite & l,  sf::View & v, Enemy& p, Enemy & p2)
{
	view = &v;
	look = &l;
	f.push_back(p);
	f.push_back(p2);
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

void Map::Locks_Settup(Collision & a, Collision & b, Collision & c, Collision & d)
{
	upLock = a;
	downLock = b;
	leftLock = c;
	rightLock = d;
}

void Map::Bots_Update(float d)
{
	std::vector<Enemy>::iterator i;
	for (i = f.begin(); i != f.end(); ++i)
	{
		i->Update(d);
	}
}

int Map::Get_Others_Size()
{
	return others.size();
}

int Map::Get_Others_Type(int n)
{
	return others[n].Get_Type();
}

void Map::Player_Lock(Player& p, int& m)
{
	//Locking room
	upLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
	rightLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
	leftLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
	downLock.GetCollider().CheckCollision(p.GetCollider(), 1.0f);
}

int Map::Player_Others(Player & p)
{
	int i;
	for (i = 0; i < others.size();i++)
	{
		if (others[i].GetCollider().CheckCollision(p.GetCollider(), 1.0f))
		{
			return i;
		}
	}
	return -1;
}

bool Map::Player_Doors(Player& p)
{
	std::vector<Collision>::iterator i;
	for (i = doors.begin(); i != doors.end(); ++i)
	{
		if (i->GetCollider().CheckCollision(p.GetCollider(), 1.0f))
		{
			return true;
		}
	}
	return false;
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

void Map::Set_Drawable(bool d, int n)
{
	others[n].Set_Drawable(d);
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
	lose_text.setPosition(-200, 0);
	lose_text.setString("You lost!");

	window->clear();
	window->setView(*view);
	window->draw(lose_text);
	window->display();

	//sf::Event evnt;

	while (1)
	{
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			switch (evnt.key.code)
			{
			case sf::Keyboard::Escape:
				window->close();
				break;
			case sf::Keyboard::Return:
				window->close();
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

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
		if(k->Get_Drawable())
			k->Draw(*window);
	}
}