#include <utility/Logger.hpp>
#include <data/Dataset.hpp>
#include <world/entity/EntityType.hpp>
#include <world/entity/Entity.hpp>
#include <world/World.hpp>
#include "Player.hpp"

Player::Player( Dataset const &dataset, World &world ) :
	mDataset( dataset ),
	mWorld( world ),
	mEntity( mWorld.createPlayer( mDataset.at< EntityType >( "human" ))),
	mCamera(
		{ 800, 600 },
		{ 32, 32 },
		{ mWorld, mDataset.at< Tile >( "nothing" ), 0.1f },
		mEntity ),
	mDead( false ),
	mDoneAction( false )
{

}

void Player::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color) const
{
	mCamera.render( target, states, color );
}

bool Player::isDead() const
{
	return mDead;
}

bool Player::hasDoneAction() const
{
	return mDoneAction;
}

void Player::resetAction()
{
	mDoneAction = false;
}

void Player::handleEvents( std::vector< sf::Event > const &events )
{
	for( auto const &iEvent : events )
	{
		handleEvent( iEvent );
	}
}

void Player::handleEvent( sf::Event const &event )
{
	if( event.type == sf::Event::Closed )
	{
		mDead = true;
	}
	if( event.type == sf::Event::KeyPressed )
	{
		switch( event.key.code )
		{
		case sf::Keyboard::W:
			move({ 0, -1, 0 });
			break;

		case sf::Keyboard::A:
			move({ -1, 0, 0 });
			break;

		case sf::Keyboard::S:
			move({ 0, 1, 0 });
			break;

		case sf::Keyboard::D:
			move({ 1, 0, 0 });
			break;

		case sf::Keyboard::R:
			mCamera.changeScale({ 1, 1 });
			break;

		case sf::Keyboard::F:
			mCamera.changeScale({ -0.1, -0.1 });
			break;

		case sf::Keyboard::Q:
			mCamera.unlock();
			break;

		case sf::Keyboard::E:
			mCamera.lock();
			break;

		default:
			break;
		}
	}
}

void Player::move( world::Vector const &by )
{
	if( !mDoneAction )
	{
		if( mCamera.isLocked())
		{
			if( mEntity.move( by ))
			{
				//mCamera.move( by );
				mDoneAction = true;
			}
		}
		else
		{
			mCamera.move( by );
		}
	}
	utility::logger.log( utility::Logger::TRACE,
		"Moved to: " +
		std::to_string( mEntity.getPosition().x ) + ", " +
		std::to_string( mEntity.getPosition().y ) + ", " +
		std::to_string( mEntity.getPosition().z ));
}
