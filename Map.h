#include <SFML\Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Collision.h"
#include "Character.h"
#include "Enemy.h"
#include "Object.h"
#include "Player.h"

class Map
{
public:
	Map(sf::Sprite& l, sf::View& v);
	Map(sf::Sprite & l, sf::View & v, Enemy& p);
	Map(sf::Sprite & l, sf::View & v, Enemy& p, Enemy& p2);
	
	~Map();
	
	void Font();
	void set_Doors(Collision& a);
	void set_Doors(Collision& a, Collision& b);
	void set_Doors(Collision& a, Collision& b, Collision& c);
	
	void set_Others(Object& a);
	void set_Others(Object& a, Object& b);

	void Locks_Settup(Collision& a, Collision& b, Collision& c, Collision& d);

	void Bots_Update(float d);

	void Player_Lock(Player& p, int &m);
	void Player_Others(Player& p);
	bool Player_Doors(Player& p);
	void Player_Bots(Player& p, sf::RenderWindow* window);
	void Figures_Direction();
	void Figure_Direction(Enemy & p, Collision& one, Collision& two, int i, int k);

	void Lose(sf::RenderWindow* window);

	void Draw(sf::RenderWindow* window);
private:
	std::vector<Enemy>f;
	std::vector<Object> others;
	std::vector<Collision> doors;

	Collision upLock;
	Collision downLock;
	Collision rightLock;
	Collision leftLock;
	sf::Event evnt;
	sf::Vector2f sizeBG;

	sf::View *view;

	sf::Sprite *look;

	sf::Font font_text;
	sf::Text lose_text;

	int counter_other = 0;
};
