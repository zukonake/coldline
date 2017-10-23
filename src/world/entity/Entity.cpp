#include <world/Common.hpp>
#include <world/block/BlockShape.hpp>
#include <world/entity/EntityType.hpp>
#include <world/World.hpp>
#include "Entity.hpp"

Entity::Entity( World &world, world::Point const &position, EntityType const &type, bool const &chunkAnchor ) noexcept :
	Body( position ),
	mWorld( world ),
	mType( type ),
	mChunkAnchor( chunkAnchor )
{

}

void Entity::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	mType.render( target, states, color );
}

bool Entity::move( world::Vector const &by )
{
	world::Point position = Body::getPosition();
	if( canMove( position + by ))
	{
		if( Body::move( by ))
		{
			mWorld.moveEntity( position, Body::getPosition());
			return true;
		}
	}
	return false;
}

bool Entity::teleport( world::Point const &to )
{
	world::Point position = Body::getPosition();
	if( Body::move( to ))
	{
		mWorld.moveEntity( position, Body::getPosition());
		return true;
	}
	return false;
}

bool Entity::isChunkAnchor() const noexcept
{
	return mChunkAnchor;
}

void Entity::simulate()
{
	while( mWorld[ Body::getPosition()].getShape() == BlockShape::EMPTY )
	{
		move({ 0, 0, -1 });
	}
}

bool Entity::canMove( world::Point const &to ) const
{
	return mWorld.sees( Body::getPosition(), to );
}
