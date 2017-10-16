#include <world/entity/Entity.hpp>
#include <world/chunk/Exception.hpp>
#include "Chunk.hpp"

chunk::Size constexpr Chunk::size;

Chunk::Chunk() noexcept
{
	static_assert( size.x > 0, "Chunk size cannot be 0" );
	static_assert( size.y > 0, "Chunk size cannot be 0" );
	static_assert( size.z > 0, "Chunk size cannot be 0" );
}

Block &Chunk::operator[]( world::Point const &point ) noexcept
{
	return mValue[ getInternalPoint( point )];
}

Block const &Chunk::operator[]( world::Point const &point ) const noexcept
{
	return mValue[ getInternalPoint( point )];
}

bool Chunk::isAnchored() const
{
	for( auto const &iEntity : mEntities )
	{
		if( iEntity.second.get().isChunkAnchor())
		{
			return true;
		}
	}
	return false;
}

bool Chunk::isEntityOn( world::Point const &point ) const
{
	return mEntities.count( point ) > 0;
}

Entity &Chunk::getEntityOn( world::Point const &point )
{
	try
	{
		return mEntities.at( point );
	}
	catch( std::out_of_range const &e )
	{
		throw chunk::InvalidEntityError( "TODO" );
	}
}

Entity const &Chunk::getEntityOn( world::Point const &point ) const
{
	try
	{
		return mEntities.at( point );
	}
	catch( std::out_of_range const &e )
	{
		throw chunk::InvalidEntityError( "TODO" );
	}
}

typename Chunk::Entities &Chunk::getEntities()
{
	return mEntities;
}

typename Chunk::Entities const &Chunk::getEntities() const
{
	return mEntities;
}

chunk::Point Chunk::getPosition( world::Point const &point ) noexcept
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

chunk::InternalPoint Chunk::getInternalPoint( world::Point const &point ) noexcept
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
