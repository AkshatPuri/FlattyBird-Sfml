#pragma once
#include<SFML/Graphics.hpp>

namespace Crabshat
{


	class Collisions
	{
	public :
		Collisions();

		bool CheckSpriteCollided(sf::Sprite sprite1, sf::Sprite sprite2);
		bool CheckSpriteCollided(sf::Sprite sprite1,float scale1 ,sf::Sprite sprite2, float scale2);


	};
}

