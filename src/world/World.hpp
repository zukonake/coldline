#pragma once

#include <thread>
#include <ratio>
#include <list>
#include <unordered_map>
//
#include <utility/Clock.hpp>
#include <world/Common.hpp>
#include <world/entity/Entity.hpp>
#include <world/chunk/Common.hpp>
#include <world/chunk/Chunk.hpp>
#include <world/Generator.hpp>

class Tile;
class EntityType;

class World
{
	public:
	World( Dataset const &Dataset );
	World( World const &that ) = delete;

	~World();

	World &operator=( World const &that ) = delete;

	Block &operator[]( world::Point const &point );
	Block const &operator[]( world::Point const &point ) const;

	bool sees( world::Point const &from, world::Point const &to ) const;
	bool canMove( world::Point const &from, world::Point const &to ) const;
	bool isEntityOn( world::Point const &point ) const;

	Entity &getEntityOn( world::Point const &point );
	Entity const &getEntityOn( world::Point const &point ) const;
	template< typename... Targs >
	Entity &createEntity( world::Point const &position, Targs const &...args );
	Entity &createPlayer( EntityType const &type );

	void moveEntity( world::Point const &from, world::Point const &to );
	void simulate();
	private://TODO add isPathClear and Path typedef
	static constexpr chunk::Size anchorRange = { 2, 2, 0 };

	bool exists( chunk::Point const &point ) const;

	Chunk &loadChunk( chunk::Point const &point ) const;
	Chunk &getChunk( chunk::Point const &point );
	Chunk const &getChunk( chunk::Point const &point ) const;

	void startUnloader();
	void stopUnloader();
	void unloaderLoop();
	void unloadChunks() const;

	bool mUnloading;

	Generator mGenerator;

	std::list< Entity > mEntities;
	std::unordered_map< chunk::Point, Chunk > mutable mChunks;
	std::thread mUnloaderThread;
	utility::Clock< double, std::ratio< 1, 1 > > mUnloaderClock;
};

template< typename... Targs >
Entity &World::createEntity( world::Point const &position, Targs const &...args )
{
	if( !isEntityOn( position ))
	{
		mEntities.emplace_back( *this, position, args... );
		Chunk &chunk = getChunk( Chunk::getPosition( position ));
		chunk.mEntities.insert({ position, mEntities.back()});
	}
	return mEntities.back();
}


