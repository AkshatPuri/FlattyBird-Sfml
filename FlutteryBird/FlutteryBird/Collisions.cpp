#include "Collisions.h"




namespace Crabshat{

	Collisions::Collisions()
	{

	}


		bool Collisions:: CheckSpriteCollided(sf::Sprite sprite1, sf::Sprite sprite2)
        {
			sf::Rect<float> rect1 = sprite1.getGlobalBounds();
			sf::Rect<float> rect2 = sprite2.getGlobalBounds();
			if (rect2.intersects(rect1))
			{
				return true;
			}
			else
			{
				return false;
			}
        }
		bool Collisions::CheckSpriteCollided(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2)
		{
			sprite2.setScale(scale1, scale2);
			
			sf::Rect<float> rect1 = sprite1.getGlobalBounds();
			sf::Rect<float> rect2 = sprite2.getGlobalBounds();
			if (rect2.intersects(rect1))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
}