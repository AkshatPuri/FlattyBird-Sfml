#include "HUD.h"
#include<string>
#include<iostream>
namespace Crabshat
{
	HUD::HUD(GameDataRef data) : _data(data)
	{
		_scoreText.setFont(_data->assets.GetFont("Font"));
		_scoreText.setString("0");
		_scoreText.setCharacterSize(80);
		_scoreText.setFillColor(sf::Color(37,35,74,230));
		_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
		_scoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y / 5);
		scoreStartScale = _scoreText.getScale();
	}

	void HUD::Draw()
	{
		
		_data->window.draw(_scoreText);
		

	}

	void HUD::UpdateScore(int score)
	{
		_scoreText.setString(std::to_string(score));
		_animationClock.restart();
	}

	void HUD::Animate(float dt,int &isTextAnimating)
	{
		if (isTextAnimating==1)
		{
			

			if (_animationClock.getElapsedTime().asSeconds() < SCORE_TEXT_ANIMATION_TIME)
			{
				sf::Vector2f scale;
				if (_animationClock.getElapsedTime().asSeconds() > SCORE_TEXT_ANIMATION_TIME / 1.3f)
				{
					if ((scale.x >= scoreStartScale.x)&& (scale.y >= scoreStartScale.y))
					{


						scale = sf::Vector2f(_scoreText.getScale().x - 1.5*dt, _scoreText.getScale().y - 1.5*dt);
					}
				}
				else
				{
					scale = sf::Vector2f(_scoreText.getScale().x + 1*dt, _scoreText.getScale().y + 1*dt);
				}
				_scoreText.setScale(scale);
			}
			else
			{
				_scoreText.setScale(scoreStartScale);
				isTextAnimating = 0;

			}
		}
		
	}

}