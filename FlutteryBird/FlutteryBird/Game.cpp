#include "Game.h"
#include "SplashState.h"

#include <stdlib.h>
#include<time.h>
#include<iostream>
#include "DEFINATIONS.h"
namespace Crabshat
{
	




	Game::Game(int width, int height, std::string title)
	{
		

		srand(time(NULL));
		_data->window.create(sf::VideoMode(width, height),
			title, sf::Style::Close | sf::Style::Titlebar);
		sf::Image icon;
		icon.loadFromFile("Resources/Icon.png");// File/Image/Pixel
		_data->window.setIcon(128,128, icon.getPixelsPtr());
		_data->machine.AddState(StateRef(new SplashState(this->_data)));
		this->Run();
	}

	void Game::Run()
	{
	
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_data->window.isOpen())
		{

			this->_data->machine.ProcessStateChange();
			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}
			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);
				accumulator -= dt;
			}
			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}