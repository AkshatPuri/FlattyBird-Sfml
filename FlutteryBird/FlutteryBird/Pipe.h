#pragma once
#include<SFML/Graphics.hpp>
#include "Game.h"
#include<vector>
#include "DEFINATIONS.h"
#include<random>


namespace Crabshat
{

	class Pipe
	{

	public:
		Pipe(GameDataRef data);

		void DrawPipes();
		void SpawnUpPipes();
		void SpawnBottomPipes();
		void SpawnInvisibleScorePipe();
	
		void RandomisePipeOffset();
		void MovePipes(float dt);
		const std::vector<sf::Sprite> &GetSprites() const;
		 std::vector<sf::Sprite> &GetInvisibleScoreSprites();
	private:
		GameDataRef _data;
		std::vector<sf::Sprite> pipeSprites;
		std::vector<sf::Sprite> invisibleScorePipeSprites;
		int _landHeight;
		int _pipeSpawnYOffset;
	};

}