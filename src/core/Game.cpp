#include <utility/Logger.hpp>
//
#include "Game.hpp"

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
		Clock::Duration delta = mClock.synchronize();
		if( delta < Clock::Duration::zero())
		{
			utility::logger.log( utility::Logger::WARN,
				"Game clock overhead: " + std::to_string( delta.count()));
		}
	}
}
