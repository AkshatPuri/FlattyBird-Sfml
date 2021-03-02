#pragma once
#include<SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINATIONS.h"
#include<vector>
namespace Crabshat
{
	enum BirdState
	{
		Still=1,
		Flying,

		Falling,
		Died
	};
	class Bird
	{
	public:
		Bird(GameDataRef data);
		BirdState birdState;


		void DrawBird();
		void Animate(float dt);
		void Update(float dt);

		void Tap();
		const sf::Sprite& GetSprite() const;

	private:
		GameDataRef _data;
		sf::Sprite _birdSprite;
		std::vector<sf::Texture> _animationFrames;
		unsigned int animationIterator = 0;

		sf::Clock _clock;
		sf::Clock _movementClock;
		float _rotation;
		int _Statebird;
	};
}
