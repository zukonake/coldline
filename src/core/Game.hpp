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
	typedef utility::Clock< double, std::ratio< 1, 60 > > Clock;
	Clock mClock;

	Dataset mDataset;
	World mWorld;
	Player mPlayer;
};
