#include "GameOverState.h"
#include<sstream>
#include "DEFINATIONS.h"
#include<iostream>
#include "GameState.h"
#include<fstream>
namespace Crabshat
{
	GameOverState::GameOverState(GameDataRef data,int score) : _data(data), _score(score)
	{
	}

	void GameOverState::Init()
	{
		std::ifstream readFile;
		readFile.open("Resources/HighScore.txt");

		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> _highScore;
			}
		}
		readFile.close();

		std::ofstream writeFile("Resources/HighScore.txt");
		if (writeFile.is_open())
		{
			if (_score > _highScore)
			{
				_highScore = _score;
			}

			writeFile << _highScore;
		}

		writeFile.close();


		std::cout << "Game Over State" << std::endl;
		_data->assets.LoadTextures("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
		_data->assets.LoadTextures("Game Over Body", GAME_OVER_BODY_FILEPATH);
		_data->assets.LoadTextures("Retry Button",RETRY_BUTTON_FILEPATH);
		_data->assets.LoadTextures("Game Over Title",GAME_OVER_TITLE_FILEPATH);

		_data->assets.GetTexture("Retry Button").setSmooth(true);
		_data->assets.GetTexture("Game Over Body").setSmooth(true);
		_data->assets.GetTexture("Game Over Title").setSmooth(true);

		_background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
		_gameOverBody.setTexture(this->_data->assets.GetTexture("Game Over Body"));
		_RetryButton.setTexture(this->_data->assets.GetTexture("Retry Button"));
		_gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title"));


		_gameOverTitle.setPosition((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2),
			(_data->window.getSize().y / 5) - (_gameOverTitle.getGlobalBounds().height ));

		_gameOverBody.setPosition((_data->window.getSize().x / 2) - (_gameOverBody.getGlobalBounds().width / 2),
			(_data->window.getSize().y / 2) - (_gameOverBody.getGlobalBounds().height / 2));
		

		_RetryButton.setPosition((_data->window.getSize().x / 2) - (_RetryButton.getGlobalBounds().width / 2),
			(_gameOverBody.getPosition().y) + (_gameOverBody.getGlobalBounds().height
				+ (_RetryButton.getGlobalBounds().height*0.2)));


		_scoreText.setFont(_data->assets.GetFont("Font"));
		_scoreText.setString(std::to_string(_score));
		_scoreText.setCharacterSize(40);
		_scoreText.setFillColor(sf::Color(37, 35, 74, 255));
		_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
		_scoreText.setPosition(_data->window.getSize().x /2, _data->window.getSize().y / 2.23);

		_highScoreText.setFont(_data->assets.GetFont("Font"));
		_highScoreText.setString(std::to_string(_highScore));
		_highScoreText.setCharacterSize(40);
		_highScoreText.setFillColor(sf::Color(37, 35, 74, 255));
		_highScoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
		_highScoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y / 1.79);

	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			if (_data->input.isSpriteClicked(_RetryButton, sf::Mouse::Left, _data->window))
			{
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_gameOverTitle);
		_data->window.draw(_gameOverBody);
		_data->window.draw(_RetryButton);
		_data->window.draw(_scoreText);
		_data->window.draw(_highScoreText);
		_data->window.display();
		

	}
}