#include "Game.hpp"
#include <iostream>

Game::Game() :
	mDataset(),
	mWorld( mDataset ),
	mPlayer( mDataset, mWorld )
{
	SFMLClient::openWindow({ 800, 600 }, "test" );
}

void Game::start()
{
	while( SFMLClient::isRunning() && !mPlayer.isDead())
	{
		mClock.start();
		SFMLClient::render( mPlayer );
		SFMLClient::update();
		mPlayer.handleEvents( SFMLClient::getEvents());
		if( mPlayer.hasDoneAction())
		{
			mPlayer.resetAction();
			mWorld.simulate();
		}
		mClock.stop();
		mClock.synchronize();
	}
}
