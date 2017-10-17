#include <utility/Logger.hpp>
//
#include "Client.hpp"

Client::Client() :
	mDataset(),
	mWorld( mDataset ),
	mPlayer( mDataset, mWorld )
{
	SFMLClient::openWindow({ 800, 600 }, "test" );
}

void Client::start()
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
			auto deltaMilliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( -delta );
			//we negate the duration, it is negative at this point,
			//so we bring it to a positive count
			utility::logger.log( utility::Logger::WARN,
				"Client clock overhead: " + std::to_string( deltaMilliseconds.count()) + "ms" );
		}
	}
}
