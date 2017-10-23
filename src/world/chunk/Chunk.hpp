#pragma once

#include <functional>
#include <unordered_map>
//
#include <world/Common.hpp>
#include <world/chunk/Common.hpp>
#include <world/block/Block.hpp>

class Entity;

class Chunk
{
	friend class World;
	public:
	typedef std::unordered_map< world::Point, std::reference_wrapper< Entity > > Entities;
	Chunk() noexcept;

	Block &operator[]( world::Point const &point ) noexcept;
	Block const &operator[]( world::Point const &point ) const noexcept;

	bool isAnchored() const;
	bool isEntityOn( world::Point const &point ) const;

	Entity &getEntityOn( world::Point const &point );
	Entity const &getEntityOn( world::Point const &point ) const;
	Entities &getEntities();
	Entities const &getEntities() const;

	static chunk::Point getPosition( world::Point const &point ) noexcept;
	static chunk::Size constexpr size = { 24, 24, 24 };
	private:
	static chunk::InternalPoint getInternalPoint( world::Point const &point ) noexcept;

	Entities mEntities;
	world::Space< size.x, size.y, size.z > mValue;
};
