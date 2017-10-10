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
		return loadChunk( Chunk::toChunkPoint( point ))[ Chunk::toChunkInternalPoint( point )];
	}
	return mChunks[ Chunk::toChunkPoint( point )][ Chunk::toChunkInternalPoint( point )];
}

Block &World::operator[]( world::Point const &point )
{
	if( !exists( point ))
	{
		return loadChunk( Chunk::toChunkPoint( point ))[ Chunk::toChunkInternalPoint( point )];
	}
	return mChunks[ Chunk::toChunkPoint( point )][ Chunk::toChunkInternalPoint( point )];
}



bool World::sees( world::Point const &from, world::Point const &to ) const
{
	auto plot = world::Line( from, to ).getPlot();
	if( plot.empty())
	{
		return false;
	}
	for( unsigned i = 1; i < plot.size() - 1; i++ )
	{
		if( !operator[]( plot[ i ]).passable())
		{
			return false;
		}
		for( auto const &entity : getEntitiesOn( plot[ i ]))
		{
			if( !entity.get().isPassable())
			{
				return false;
			}
		}
	}
	return true;
}

bool World::isEntityOn( world::Point const &point ) const
{
	Chunk const &chunk = getChunk( Chunk::toChunkPoint( point ));
	return !chunk.getEntitiesOn( Chunk::toChunkInternalPoint( point )).empty();
}



std::vector< std::reference_wrapper< const Entity > > World::getEntitiesOn( world::Point const &point ) const
{
	Chunk const &chunk = getChunk( Chunk::toChunkPoint( point ));
	return chunk.getEntitiesOn( Chunk::toChunkInternalPoint( point ));
}

Entity &World::createEntity( world::Point const &position, EntityType const &subtype )
{
	if( !isEntityOn( position ))
	{
		mEntities.emplace_back( *this, position, subtype );
		Chunk &chunk = getChunk( Chunk::toChunkPoint( position ));
		chunk.mEntities.push_back( mEntities.back());
	}
	return mEntities.back();
}

Entity &World::createPlayer( EntityType const &subtype )
{
	return createEntity( { 0, 0, 0 }, subtype ); //TODO 0, 0, 0 ?
}



void World::moveEntity( world::Point const &from, world::Point const &to )
{
	if( Chunk::toChunkPoint( from ) != Chunk::toChunkPoint( to ))
	{
		Chunk &fromChunk = getChunk( Chunk::toChunkPoint( from ));
		Chunk &toChunk = getChunk( Chunk::toChunkPoint( to ));
		for( unsigned i = 0; i < fromChunk.mEntities.size(); i++ )
		{
			if( fromChunk.mEntities[ i ].get().getPosition() == from )
			{
				toChunk.mEntities.push_back( fromChunk.mEntities[ i ]);
				fromChunk.mEntities.erase( fromChunk.mEntities.begin() + i );
				return;
			}
		}
	}
}

void World::simulate()
{

}



bool World::exists( world::Point const &point ) const
{
	return mChunks.count( Chunk::toChunkPoint( point )) > 0;
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
