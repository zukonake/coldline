#include <utility/Random.hpp>
#include <data/Dataset.hpp>
#include <world/block/BlockType.hpp>
#include <world/chunk/Chunk.hpp>
#include "Generator.hpp"

Generator::Generator( Dataset const &dataset ) :
	mFloor( dataset.at< BlockType >( "stoneFloor" )),
	mWall( dataset.at< BlockType >( "stoneWall" ))
{

}

Chunk Generator::generate( chunk::Point const &position ) const
{
	( void )position;
	Chunk chunk;
	for( unsigned iZ = 0; iZ < Chunk::size.z; iZ++ )
	{
		for( unsigned iY = 0; iY < Chunk::size.y; iY++ )
		{
			for( unsigned iX = 0; iX < Chunk::size.x; iX++ )
			{
				if(( utility::numberGenerator() % 50) == 0 )
				{
					chunk[{ iX, iY, iZ }] = mWall;
				}
				else
				{
					chunk[{ iX, iY, iZ }] = mFloor;
				}
			}
		}
	}
	return chunk;
}
