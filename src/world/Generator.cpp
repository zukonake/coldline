#include <fastNoise/FastNoise.h>
//
#include <utility/Random.hpp>
#include <data/Dataset.hpp>
#include <world/block/BlockType.hpp>
#include <world/chunk/Chunk.hpp>
#include "Generator.hpp"

Generator::Generator( Dataset const &dataset ) :
	mFloor( dataset.at< BlockType >( "grass" )),
	mWall( dataset.at< BlockType >( "dirt" )),
	mAir( dataset.at< BlockType >( "air" ))
{
	mNoise.SetSeed( utility::numberGenerator());
	mNoise.SetNoiseType( FastNoise::Perlin );
}

Chunk Generator::generate( chunk::Point const &position ) const
{
	Chunk chunk;
	chunk::InternalPoint iterator;
	for( iterator.z = 0; iterator.z < Chunk::size.z; iterator.z++ )
	{
		for( iterator.y = 0; iterator.y < Chunk::size.y; iterator.y++ )
		{
			for( iterator.x = 0; iterator.x < Chunk::size.x; iterator.x++ )
			{
				world::Point worldPosition = (position * Chunk::size) + iterator;
				float height = std::fabs( mNoise.GetNoise( worldPosition.x, worldPosition.y )) * -16;
				if( worldPosition.z < height )
				{
					chunk[ iterator ] = mWall;
				}
				else if( worldPosition.z - 1 < height )
				{
					chunk[ iterator ] = mFloor;
				}
				else
				{
					chunk[ iterator ] = mAir;
				}
			}
		}
	}
	return chunk;
}
