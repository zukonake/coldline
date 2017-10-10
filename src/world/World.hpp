#pragma once

#include <list>
#include <unordered_map>
//
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

	World &operator=( World const &that ) = delete;

	Block &operator[]( world::Point const &point );
	Block const &operator[]( world::Point const &point ) const;

	bool sees( world::Point const &from, world::Point const &to ) const;
	bool canMove( world::Point const &from, world::Point const &to ) const;
	bool isEntityOn( world::Point const &point ) const;

	std::vector< std::reference_wrapper< const Entity > > getEntitiesOn( world::Point const &point ) const;
	Entity &createEntity( world::Point const &position, EntityType const &subtype );
	Entity &createPlayer( EntityType const &subtype );

	void moveEntity( world::Point const &from, world::Point const &to );
	void simulate();
	private://TODO add isPathClear and Path typedef
	bool exists( world::Point const &point ) const;
	Chunk &loadChunk( chunk::Point const &point ) const;
	Chunk &getChunk( chunk::Point const &point );
	Chunk const &getChunk( chunk::Point const &point ) const;

	Generator mGenerator;

	std::list< Entity > mEntities;
	std::unordered_map< chunk::Point, Chunk > mutable mChunks;
};
