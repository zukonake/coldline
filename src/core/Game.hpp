#pragma once

#include <ratio>
//
#include <utility/Clock.hpp>
#include <render/SFMLClient.hpp>
#include <data/Dataset.hpp>
#include <world/World.hpp>
#include <core/Player.hpp>

class Game : SFMLClient
{
	public:
	Game();

	void start();
	private:
	utility::Clock< double, std::ratio< 1, 60 > > mClock;

	Dataset mDataset;
	World mWorld;
	Player mPlayer;
};
