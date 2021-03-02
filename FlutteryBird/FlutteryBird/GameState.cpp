#include "GameState.h"
#include<sstream>
#include "DEFINATIONS.h"
#include<iostream>
#include "GameOverState.h"

namespace Crabshat
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
	}

	void GameState::Init()
	{
		fps = new FPS();
		
		std::cout << "Game State" << std::endl;
		_data->assets.LoadTextures("Game Over State Background", GAME_OVER_BACKGROUND_FILEPATH);
		_data->assets.LoadTextures("Obstacle Up", OBSTACLE_UP_FILEPATH);
		_data->assets.LoadTextures("Obstacle Bottom", OBSTACLE_BOTTOM_FILEPATH);
		_data->assets.GetTexture("Obstacle Bottom").setSmooth(true);
		_data->assets.GetTexture("Obstacle Up").setSmooth(true);
		_data->assets.LoadTextures("Land", LAND_FILEPATH);
		_data->assets.LoadTextures("Bird Frame 1", BIRD_FRAME1_FILEPATH);
		_data->assets.LoadTextures("Bird Frame 2", BIRD_FRAME2_FILEPATH);
		_data->assets.LoadTextures("Bird Frame 3", BIRD_FRAME3_FILEPATH);
		_data->assets.LoadTextures("Bird Frame 4", BIRD_FRAME4_FILEPATH);
		_data->assets.LoadTextures("Score Pipe", SCORE_PIPE_FILEPATH);
		_data->assets.LoadFont("Font", FONT);
		pressSpaceText.setFont(_data->assets.GetFont("Font"));
		fps->Init(_data);
		if (!hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH)) 
		{
			std::cout << "ERROR LOADING HIT SOUND"<<std::endl;
		}

		if (!pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
		{
			std::cout << "ERROR LOADING POINT SOUND" << std::endl;
		}

		if (!flySoundBuffer.loadFromFile(FLY_SOUND_FILEPATH))
		{
			std::cout << "ERROR LOADING FLY SOUND" << std::endl;
		}

		_hitSound.setBuffer(hitSoundBuffer);
		_flySound.setBuffer(flySoundBuffer);
		_pointSound.setBuffer(pointSoundBuffer);
	/*	_flySound.setVolume(.8f);
		_pointSound.setVolume(2.0f);
		_hitSound.setVolume(2.0f);*/
		pipe = new Pipe(_data);
		land = new Land(_data);
		bird = new Bird(_data);
		flash = new Flash(_data);

		hud = new HUD(_data);


		pressSpaceText.setFillColor(sf::Color(37, 35, 74, 230));
		pressSpaceText.setString("Press Space To Start!");
		pressSpaceText.setOrigin(pressSpaceText.getGlobalBounds().width / 2, pressSpaceText.getGlobalBounds().height / 2);
		pressSpaceText.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 70);


		_background.setTexture(this->_data->assets.GetTexture("Game Over State Background"));
		_gameState = GameStates::eReady;
		score = 0;
		hud->UpdateScore(score);
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			if ((_data->input.isSpriteClicked(_background, sf::Mouse::Left, _data->window))||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (_gameState != GameStates::eGameOver)
				{
					_gameState = GameStates::ePlaying;
					_flySound.play();
					bird->Tap();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		fps->update();
		if (_gameState != GameStates::eGameOver)
		{
			bird->Animate(dt);
			
			
		}
		

		if (_gameState == GameStates::ePlaying)
		{
			land->MoveLand(dt);
			pipe->MovePipes(dt);
			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				
				pipe->RandomisePipeOffset();
				pipe->SpawnInvisibleScorePipe();
				pipe->SpawnBottomPipes();

				pipe->SpawnUpPipes();
				
				clock.restart();
			}

			bird->Update(dt);

			std::vector<sf::Sprite> landSprites = land->GetSprites();
			for (int i = 0; i < landSprites.size(); i++)
			{
				if (collision.CheckSpriteCollided(landSprites.at(i), 0.800f, bird->GetSprite(), 0.300f))
				{
					_hitSound.play();
					_gameState = GameStates::eGameOver;
					clock.restart();
				}
			}
			std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
			for (int i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.CheckSpriteCollided(pipeSprites.at(i),0.650f, bird->GetSprite(),0.300f))
				{
					_hitSound.play();
					_gameState = GameStates::eGameOver;
					clock.restart();
				}
			}

			if (_gameState == GameStates::ePlaying)
			{


				std::vector<sf::Sprite> &ScorePipeSprites = pipe->GetInvisibleScoreSprites();
				for (int i = 0; i < ScorePipeSprites.size(); i++)
				{
					if (collision.CheckSpriteCollided(ScorePipeSprites.at(i), 0.650f, bird->GetSprite(), 0.300f))
					{
						_pointSound.play();
						score++;
						isTextAnimating = 1;
						hud->UpdateScore(score);
						std::cout << score << std::endl;
						ScorePipeSprites.erase(ScorePipeSprites.begin() + i);
					}
				}

				if (isTextAnimating==1)
				{


					
					hud->Animate(dt, isTextAnimating);
				}
				
			}
			
		}

		if (_gameState == GameStates::eGameOver)
		{
			flash->Show(dt);
			if (clock.getElapsedTime().asSeconds() >= TIME_BEFORE_GAME_OVER)
			{
				_data->machine.AddState(StateRef(new GameOverState(_data,score)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		
		_data->window.clear();


		
		_data->window.draw(_background);
		pipe->DrawPipes();
		land->DrawLand();
		bird->DrawBird();
		fps->DrawFps();
		if (_gameState == GameStates::eReady)
		{
			_data->window.draw(pressSpaceText);
		}
		flash->Draw();
		hud->Draw();
		_data->window.display();

	}
}