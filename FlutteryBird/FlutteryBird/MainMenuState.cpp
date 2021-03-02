#include "MainMenuState.h"
#include "GameState.h"
#include<sstream>
#include "DEFINATIONS.h"
#include<iostream>

namespace Crabshat
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		_data->assets.LoadTextures("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));


		_data->assets.LoadTextures("Main Menu Title", MAIN_MENU_TITLE_FILEPATH);
		_title.setTexture(this->_data->assets.GetTexture("Main Menu Title"));

		_title.setPosition(SCREEN_WIDTH / 2 - _title.getGlobalBounds().width / 2,
			((SCREEN_HEIGHT / 5.5) - _title.getGlobalBounds().height/2 ) );


		_data->assets.LoadTextures("Main Menu PlayButton", PLAY_BUTTON_FILEPATH);
		_playButton.setTexture(this->_data->assets.GetTexture("Main Menu PlayButton"));
	
		_playButton.setPosition(SCREEN_WIDTH / 2- _playButton.getGlobalBounds().width / 2, ((SCREEN_HEIGHT / 2)- _playButton.getGlobalBounds().height / 2)+100);
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}

			if (_data->input.isSpriteClicked(_playButton, sf::Mouse::Left, _data->window)) 
			{
				_data->machine.AddState(StateRef(new GameState(_data)),true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
	
	}

	void MainMenuState::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_playButton);
		_data->window.draw(_title);
		_data->window.display();

	}
}