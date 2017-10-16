#include <world/Common.hpp>
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
	if( Body::move( by ))
	{
		mWorld.moveEntity( position, Body::getPosition());
		return true;
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

bool Entity::isPassable() const noexcept
{
	return !mType.mSolid;
}

bool Entity::isChunkAnchor() const noexcept
{
	return mChunkAnchor;
}

bool Entity::canMove( world::Point const &to ) const
{
	auto plot = world::Line( getPosition(), to ).getPlot();
	if( plot.empty())
	{
		return false;
	}
	for( auto iPoint = plot.begin() + 1; iPoint < plot.end(); ++iPoint )
	{
		if( !mWorld[ *iPoint ].isPassable())
		{
			return false;
		}
		if( mWorld.isEntityOn( *iPoint ))
		{
			if( mWorld.getEntityOn( *iPoint ).isPassable())
			{
				return false;
			}
		}
	}
	return true;
}
