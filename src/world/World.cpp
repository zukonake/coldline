#include <stdexcept>
#include <string>
//
#include <utility/Logger.hpp>
#include <world/Common.hpp>
#include <world/chunk/Chunk.hpp>
#include <world/entity/EntityType.hpp>
#include <world/entity/Entity.hpp>
#include <world/Generator.hpp>
#include "World.hpp"

World::World( Dataset const &dataset ) :
	mGenerator( dataset )
{

}



Block const &World::operator[]( world::Point const &point ) const
{
	if( !exists( point ))
	{
		return loadChunk( Chunk::getPosition( point ))[ point ];
	}
	return mChunks[ Chunk::getPosition( point )][ point ];
}

Block &World::operator[]( world::Point const &point )
{
	if( !exists( point ))
	{
		return loadChunk( Chunk::getPosition( point ))[ point ];
	}
	return mChunks[ Chunk::getPosition( point )][ point ];
}



bool World::sees( world::Point const &from, world::Point const &to ) const
{
	auto plot = world::Line( from, to ).getPlot();
	if( plot.empty())
	{
		return false;
	}
	for( auto iPoint = plot.begin(); iPoint < plot.end() - 1; ++iPoint )
	{
		if( !operator[]( *iPoint ).isPassable())
		{
			return false;
		}
		if( isEntityOn( *iPoint ))
		{
			if( getEntityOn( *iPoint ).isPassable() )
			{
				return false;
			}
		}
	}
	return true;
}

bool World::isEntityOn( world::Point const &point ) const
{
	Chunk const &chunk = getChunk( Chunk::getPosition( point ));
	return chunk.isEntityOn( point );
}


Entity &World::getEntityOn( world::Point const &point )
{
	Chunk &chunk = getChunk( Chunk::getPosition( point ));
	return chunk.getEntityOn( point );
}

Entity const &World::getEntityOn( world::Point const &point ) const
{
	Chunk const &chunk = getChunk( Chunk::getPosition( point ));
	return chunk.getEntityOn( point );
}

Entity &World::createEntity( world::Point const &position, EntityType const &subtype )
{
	if( !isEntityOn( position ))
	{
		mEntities.emplace_back( *this, position, subtype );
		Chunk &chunk = getChunk( Chunk::getPosition( position ));
		chunk.mEntities.insert({ position, mEntities.back()});
	}
	return mEntities.back();
}

Entity &World::createPlayer( EntityType const &subtype )
{
	return createEntity( { 0, 0, 0 }, subtype ); //TODO 0, 0, 0 ?
}



void World::moveEntity( world::Point const &from, world::Point const &to )
{
	auto fromChunkPoint = Chunk::getPosition( from );
	auto getPosition = Chunk::getPosition( to );
	Chunk &fromChunk = getChunk( fromChunkPoint );
	Chunk &toChunk = getChunk( getPosition );
	toChunk.getEntities().insert({ to, fromChunk.getEntityOn( from )});
	fromChunk.getEntities().erase( from );
}

void World::simulate()
{

}



bool World::exists( world::Point const &point ) const
{
	return mChunks.count( Chunk::getPosition( point )) > 0;
}

Chunk &World::loadChunk( chunk::Point const &point ) const
{
	utility::logger.log( utility::Logger::DEBUG,
		"Loaded chunk: " +
		std::to_string( point.x ) + ", " +
		std::to_string( point.y ) + ", " +
		std::to_string( point.z ));
	mChunks[ point ] = mGenerator.generate( point );
	return mChunks[ point ];
}

Chunk &World::getChunk( chunk::Point const &point )
{
	if( exists( point ))
	{
		return mChunks.at( point );
	}
	else
	{
		return loadChunk( point );
	}
}

Chunk const &World::getChunk( chunk::Point const &point ) const
{
	if( exists( point ))
	{
		return mChunks.at( point );
	}
	else
	{
		return loadChunk( point );
	}
}
