#pragma once

#include <fastNoise/FastNoise.h>

class BlockType;
class Dataset;

class Generator
{
	public:
	Generator( Dataset const &dataset );

	Chunk generate( chunk::Point const &position ) const;
	private:
	BlockType const &mFloor;
	BlockType const &mWall;
	BlockType const &mAir;
	FastNoise mNoise;
};
