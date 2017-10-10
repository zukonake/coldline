#pragma once

#include <world/Common.hpp>
#include <world/chunk/Common.hpp>
#include <world/block/Block.hpp>

class Entity;

class Chunk
{
	friend class World;
	public:
	Chunk() noexcept;

	std::vector< std::reference_wrapper< Entity > > getEntitiesOn( chunk::InternalPoint const &point );
	std::vector< std::reference_wrapper< Entity > > getEntities();
	std::vector< std::reference_wrapper< const Entity > > getEntitiesOn( chunk::InternalPoint const &point ) const;
	std::vector< std::reference_wrapper< const Entity > > getEntities() const;

	Block &operator[]( chunk::InternalPoint const &point ) noexcept;
	Block const &operator[]( chunk::InternalPoint const &point ) const noexcept;

	static chunk::Point toChunkPoint( world::Point const &point ) noexcept;
	static chunk::InternalPoint toChunkInternalPoint( world::Point const &point ) noexcept;
	static chunk::Size constexpr size = { 24, 24, 1 };
	private:
	std::vector< std::reference_wrapper< Entity > > mEntities;
	world::Space< size.x, size.y, size.z > mValue;
};
