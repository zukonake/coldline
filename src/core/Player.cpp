#include <SFML/Graphics/RenderTarget.hpp>
//
#include <render/Tile.hpp>
#include <data/Dataset.hpp>
#include <world/entity/EntityType.hpp>
#include <world/World.hpp> //TODO
#include "Player.hpp"

Player::Player( Dataset const &dataset, World &world ) :
	mDataset( dataset ),
	mWorld( world ),
	mCamera(
		{ 800, 600 },
		{ 32, 32 },
		mWorld,
		mDataset.at< Tile >( "nothing" ),
		mWorld.createPlayer( mDataset.at< EntityType >( "human" ))),
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
			mCamera.move({ 0, -1, 0 });
			break;

		case sf::Keyboard::A:
			mCamera.move({ -1, 0, 0 });
			break;

		case sf::Keyboard::S:
			mCamera.move({ 0, 1, 0 });
			break;

		case sf::Keyboard::D:
			mCamera.move({ 1, 0, 0 });
			break;

		default:
			break;
		}
	}
}
