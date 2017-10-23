#include <stdexcept>
#include <set>
#include <string>
//
#include <utility/Logger.hpp>
#include <world/Common.hpp>
#include <world/block/BlockShape.hpp>
#include <world/chunk/Chunk.hpp>
#include <world/entity/EntityType.hpp>
#include <world/entity/Entity.hpp>
#include <world/Generator.hpp>
#include "World.hpp"

World::World( Dataset const &dataset ) :
	mGenerator( dataset )
{
	startUnloader();
}



World::~World()
{
	if( mUnloading )
	{
		stopUnloader();
	}
}



Block const &World::operator[]( world::Point const &point ) const
{
	return getChunk( Chunk::getPosition( point ))[ point ];
}

Block &World::operator[]( world::Point const &point )
{
	return getChunk( Chunk::getPosition( point ))[ point ];
}



bool World::sees( world::Point const &from, world::Point const &to ) const
{
	auto plot = world::Line( from, to ).getPlot();
	if( plot.empty())
	{
		return false;
	}
	for( auto iPoint = plot.begin() + 1; iPoint < plot.end() - 1; ++iPoint )
	{
		if( operator[]( *iPoint ).getShape() == BlockShape::WALL )
		{
			return false;
		}
		if( isEntityOn( *iPoint ))
		{
			return false;
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

Entity &World::createPlayer( EntityType const &type )
{
	return createEntity({ 0, 0, 0 }, type, true ); //TODO 0, 0, 0 ?
}



void World::moveEntity( world::Point const &from, world::Point const &to )
{
	Chunk &fromChunk = getChunk( Chunk::getPosition( from ));
	Chunk &toChunk = getChunk( Chunk::getPosition( to ));
	toChunk.getEntities().insert({ to, fromChunk.getEntityOn( from )});
	fromChunk.getEntities().erase( from );
}

void World::simulate()
{
	for( auto &iEntity : mEntities )
	{
		iEntity.simulate();
	}
}



bool World::exists( chunk::Point const &point ) const
{
	return mChunks.count( point ) > 0;
}

Chunk &World::loadChunk( chunk::Point const &point ) const
{
	utility::logger.log( utility::Logger::DEBUG,
		"Loaded chunk: " +
		std::to_string( point.x ) + ", " +
		std::to_string( point.y ) + ", " +
		std::to_string( point.z ));
	mChunks.insert({ point, mGenerator.generate( point )});
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

void World::startUnloader()
{
	mUnloading = true;
	mUnloaderThread = std::thread( &World::unloaderLoop, this );
}

void World::stopUnloader()
{
	//TODO mutex?
	mUnloading = false;
	mUnloaderThread.join();
}

void World::unloaderLoop()
{
	while( mUnloading )
	{
		mUnloaderClock.start();
		unloadChunks();
		mUnloaderClock.stop();
		mUnloaderClock.synchronize();
	}
}

void World::unloadChunks() const
{
	std::set< chunk::Point > anchored;
	for( auto const &iPair : mChunks )
	{
		if( iPair.second.isAnchored())
		{
			chunk::Point iPoint;
			chunk::Point const &center = iPair.first;
			for( iPoint.z = center.z - anchorRange.z; iPoint.z <= center.z + anchorRange.z; ++iPoint.z )
			{
				for( iPoint.y = center.y - anchorRange.y; iPoint.y <= center.y + anchorRange.y; ++iPoint.y )
				{
					for( iPoint.x = center.x - anchorRange.x; iPoint.x <= center.x + anchorRange.x; ++iPoint.x )
					{
						anchored.insert( iPoint );
					}
				}
			}
		}
	}
	for( auto iPair = mChunks.begin(); iPair != mChunks.end(); )
	{
		if( anchored.count( iPair->first ) == 0 )
		{
			utility::logger.log( utility::Logger::DEBUG,
				"Unloaded chunk: " +
				std::to_string( iPair->first.x ) + ", " +
				std::to_string( iPair->first.y ) + ", " +
				std::to_string( iPair->first.z ));
			iPair = mChunks.erase( iPair );
		}
		else
		{
			++iPair;
		}
	}
}
