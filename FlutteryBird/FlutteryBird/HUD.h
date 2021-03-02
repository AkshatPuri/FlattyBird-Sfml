#pragma once

#include<SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINATIONS.h"

namespace Crabshat
{


	class HUD
	{
	public:
		HUD(GameDataRef data);

		void Draw();
		void UpdateScore(int score);
		void Animate(float dt,int &isTextAnimating);
		sf::Clock _animationClock;

	private:
		GameDataRef _data;
		sf::Text _scoreText;
		sf::Vector2f scoreStartScale;
		
	};

}