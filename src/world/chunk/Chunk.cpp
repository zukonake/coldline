#include <world/entity/Entity.hpp>
#include "Chunk.hpp"

chunk::Size constexpr Chunk::size;

Chunk::Chunk() noexcept
{
	static_assert( size.x > 0, "Chunk size cannot be 0" );
	static_assert( size.y > 0, "Chunk size cannot be 0" );
	static_assert( size.z > 0, "Chunk size cannot be 0" );
}

Block &Chunk::operator[]( chunk::InternalPoint const &point ) noexcept
{
	return mValue[ point ];
}

Block const &Chunk::operator[]( chunk::InternalPoint const &point ) const noexcept
{
	return mValue[ point ];
}

std::vector< std::reference_wrapper< Entity > > Chunk::getEntitiesOn( chunk::InternalPoint const &point )
{
	std::vector< std::reference_wrapper< Entity > > entities;
	for( auto &iEntity : mEntities )
	{
		if( toChunkInternalPoint( iEntity.get().getPosition()) == point )
		{
			entities.push_back( iEntity );
		}
	}
	return entities;
}

std::vector< std::reference_wrapper< Entity > > Chunk::getEntities()
{
	return mEntities;
}

std::vector< std::reference_wrapper< const Entity > > Chunk::getEntitiesOn( chunk::InternalPoint const &point ) const
{
	std::vector< std::reference_wrapper< const Entity > > entities;
	for( auto const &iEntity : mEntities )
	{
		if( toChunkInternalPoint( iEntity.get().getPosition()) == point )
		{
			entities.emplace_back( iEntity.get());
		}
	}
	return entities;
}

std::vector< std::reference_wrapper< const Entity > > Chunk::getEntities() const
{
	std::vector< std::reference_wrapper< const Entity > > entities;
	for( auto const &iEntity : mEntities )
	{
		entities.emplace_back( iEntity.get());
	}
	return entities;
}

chunk::Point Chunk::toChunkPoint( world::Point const &point ) noexcept
{
	chunk::Point output = point;
	if( output.x < 0 )
	{
		output.x -= size.x - 1;
	}
	if( output.y < 0 )
	{
		output.y -= size.y - 1;
	}
	if( output.z < 0 )
	{
		output.z -= size.z - 1;
	}
	return output / size;
}

chunk::InternalPoint Chunk::toChunkInternalPoint( world::Point const &point ) noexcept
{
	world::Point output = point;
	output.x %= size.x;
	output.y %= size.y;
	output.z %= size.z;
	if( output.x < 0 )
	{
		output.x += size.x;
	}
	if( output.y < 0 )
	{
		output.y += size.y;
	}
	if( output.z < 0 )
	{
		output.z += size.z;
	}
	return output;
}
