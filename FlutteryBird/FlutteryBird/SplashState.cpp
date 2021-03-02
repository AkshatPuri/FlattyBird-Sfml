#include "SplashState.h"
#include<sstream>
#include "DEFINATIONS.h"
#include<iostream>
#include "MainMenuState.h"
namespace Crabshat
{
	SplashState::SplashState(GameDataRef data): _data(data)
	{

	}

	void SplashState::Init()
	{
		_data->assets.LoadTextures("Splash State Background", SPLASH_SCREEN_BACKGROUND_FILEPATH);
		_data->assets.GetTexture("Splash State Background").setSmooth(true);
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
		_background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);
		_background.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	}

	void SplashState::HandleInput()
	{
		sf::Event event;
		
			while (_data->window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					_data->window.close();
				}
			}
	}

	void SplashState::Update(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
		else
		{
			sf::Vector2f scale;
			scale = sf::Vector2f(_background.getScale().x + 0.3*dt, _background.getScale().y + 0.3*dt);
			
			_background.setScale(scale);
			
			
		}
	}

	void SplashState::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.display();
		
	}
}