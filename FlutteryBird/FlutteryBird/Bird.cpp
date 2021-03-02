#include "Bird.h"



namespace Crabshat
{


	Bird::Bird(GameDataRef data) :_data(data)
	{
		animationIterator = 0;

		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 1"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 2"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 3"));
		_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 4"));

		for (int i = 0; i < _animationFrames.size(); i++)
		{
			_animationFrames.at(i).setSmooth(true);
		}

		_birdSprite.setTexture(_animationFrames.at(animationIterator));
		_birdSprite.setPosition((_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2),
			(_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2));

		birdState = BirdState::Still;
		sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width / 2, _birdSprite.getGlobalBounds().height / 2);
		_birdSprite.setOrigin(origin);
		_rotation = 0;

	}

	void Bird::DrawBird()
	{
		_data->window.draw(_birdSprite);
	}

	void Bird::Animate(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size())
		{
			if (animationIterator < _animationFrames.size() - 1)
			{
				animationIterator++;
			}
			else
			{
				animationIterator = 0;
			}
			_birdSprite.setTexture(_animationFrames.at(animationIterator));
			_clock.restart();
		}
	}

	void Bird::Update(float dt)
	{
		if (birdState == BirdState::Falling)
		{
			

				_birdSprite.move(0, GRAVITY*dt);
			
			_rotation += ROTATION_SPEED * dt;
			if (_rotation > 25.0f)
			{
				_rotation = 25.0f;
			}
			_birdSprite.setRotation(_rotation);
		}
		if (birdState == BirdState::Flying)
		{
			if (_birdSprite.getPosition().y >25)
			{


				_birdSprite.move(0, -FlYING_SEED * dt);
			}
			
			_rotation -= ROTATION_SPEED * dt;
			if (_rotation < -25.0f)
			{
				_rotation = -25.0f;
			}
			_birdSprite.setRotation(_rotation);
		}
		if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
		{
			birdState = BirdState::Falling;
			_movementClock.restart();
		}

	}

	void Bird::Tap()
	{

		birdState = BirdState::Flying;
		_movementClock.restart();
	}

	const sf::Sprite & Bird::GetSprite() const
	{
		return _birdSprite;
	}
}