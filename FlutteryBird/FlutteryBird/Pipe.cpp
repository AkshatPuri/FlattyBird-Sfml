#include "Pipe.h"
#include<iostream>

namespace Crabshat
{

	Pipe::Pipe(GameDataRef data) :_data(data)
	{
		_data->assets.GetTexture("Land").setSmooth(true);
		_landHeight = _data->assets.GetTexture("Land").getSize().y;
		_pipeSpawnYOffset = 0;
	}

	

	void Pipe::SpawnUpPipes()
	{
		_data->assets.GetTexture("Obstacle Up").setSmooth(true);
		sf::Sprite sprite(_data->assets.GetTexture("Obstacle Up"));

		sprite.setPosition(_data->window.getSize().x, -_pipeSpawnYOffset);
		

		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnBottomPipes()
	{
		_data->assets.GetTexture("Obstacle Bottom").setSmooth(true);
		sf::Sprite sprite(_data->assets.GetTexture("Obstacle Bottom"));

		sprite.setPosition(_data->window.getSize().x,
			_data->window.getSize().y - sprite.getGlobalBounds().height- _pipeSpawnYOffset);
		pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnInvisibleScorePipe()
	{
		_data->assets.GetTexture("Score Pipe").setSmooth(true);
		sf::Sprite sprite(_data->assets.GetTexture("Score Pipe"));
		sprite.setColor(sf::Color(0, 0, 0, 0));
		sprite.setPosition(_data->window.getSize().x,
			0);
		invisibleScorePipeSprites.push_back(sprite);
	}

	

	void Pipe::RandomisePipeOffset()
	{
		_pipeSpawnYOffset = rand() % (_landHeight + 1);

	}

	void Pipe::MovePipes(float dt)
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			if (pipeSprites.at(i).getPosition().x < 0 - pipeSprites.at(i).getGlobalBounds().width)
			{
				pipeSprites.erase(pipeSprites.begin() + i);
			}

			else
			{


				float movement = PIPE_MOVEMENT_SPEED * dt;
				pipeSprites.at(i).move(-movement, 0);
			}
			
		}
		for (unsigned short int i = 0; i < invisibleScorePipeSprites.size(); i++)
		{
			if (invisibleScorePipeSprites.at(i).getPosition().x < 0 - invisibleScorePipeSprites.at(i).getGlobalBounds().width)
			{
				invisibleScorePipeSprites.erase(pipeSprites.begin() + i);
			}

			else
			{


				float movement = PIPE_MOVEMENT_SPEED * dt;
				invisibleScorePipeSprites.at(i).move(-movement, 0);
			}
			
		}
	}

	const std::vector<sf::Sprite> &Pipe::GetSprites() const
	{
		return pipeSprites;
	}

	 std::vector<sf::Sprite> &Pipe::GetInvisibleScoreSprites() 
	{
		return invisibleScorePipeSprites;
	}


	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < pipeSprites.size(); i++)
		{
			_data->window.draw(pipeSprites.at(i));
		}
		for (unsigned short int i = 0; i < invisibleScorePipeSprites.size(); i++)
		{
			_data->window.draw(invisibleScorePipeSprites.at(i));
		}
	}
}