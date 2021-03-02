#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collisions.h"
#include "Flash.h"
#include "HUD.h"
namespace Crabshat
{
	class FPS
	{
	public:
		/// @brief Constructor with initialization.
		///
		FPS() : mFrame(0), mFps(0) {}

	

	private:
		unsigned int mFrame;
		unsigned int mFps;
		sf::Clock mClock;
		sf::Text fpsText;
		GameDataRef _data;

	public:

		void Init(GameDataRef data) 
		{

			_data = data;
			
			fpsText.setFont(_data->assets.GetFont("Font"));
			fpsText.setFillColor(sf::Color(37, 35, 74, 230));
			fpsText.setOrigin(fpsText.getGlobalBounds().width / 2, fpsText.getGlobalBounds().height / 2);
			
			fpsText.setCharacterSize(20);

		}
		void update()
		{
			if (mClock.getElapsedTime().asSeconds() >= 1.f)
			{
				mFps = mFrame;
				mFrame = 0;
				mClock.restart();
				fpsText.setString(std::to_string(mFps));
			}

			++mFrame;
		}

		void DrawFps()
		{

			
			_data->window.draw(fpsText);

			
		}
	};

	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		Pipe *pipe;
		Land *land;
		Bird *bird;
		Flash *flash;
		FPS *fps;
		HUD *hud;
		Collisions collision;

		sf::Clock clock;
		int _gameState;
		int score;
		

		sf::SoundBuffer hitSoundBuffer;
		sf::SoundBuffer pointSoundBuffer;
		sf::SoundBuffer flySoundBuffer;

		sf::Sound _hitSound;
		sf::Sound _pointSound;
		sf::Sound _flySound;
		int isTextAnimating=0;
		sf::Text pressSpaceText;
		
	};
}

