#include <render/Tileset.hpp>
#include <render/Tile.hpp>
#include <world/block/BlockType.hpp>
#include <world/block/BlockShape.hpp>
#include <world/entity/EntityType.hpp>
#include "Dataset.hpp"

Tileset blockTiles =
{
	"tilesets/blocks.png",
	{ 16, 16 }
};

Tileset creatureTiles =
{
	"tilesets/creatures.png",
	{ 16, 16 }
};

Tile nothing =
{
	blockTiles,
	{ 0, 0 }
};

BlockType air =
{
	{
		blockTiles,
		{ 1, 0 }
	},
	BlockShape::EMPTY
};

BlockType stoneBrickWall =
{
	{
		blockTiles,
		{ 2, 0 }
	},
	BlockShape::WALL
};

BlockType grass =
{
	{
		blockTiles,
		{ 3, 0 }
	},
	BlockShape::FLOOR
};

BlockType dirt =
{
	{
		blockTiles,
		{ 2, 1 }
	},
	BlockShape::WALL
};

BlockType stoneWall =
{
	{
		blockTiles,
		{ 0, 1 }
	},
	BlockShape::WALL
};

EntityType human =
{
	{
		creatureTiles,
		{ 0, 0 }
	}
};

Dataset::Dataset() noexcept
{
	mObjects[ "nothing" ] = &nothing;
	mObjects[ "blockTiles" ] = &blockTiles;
	mObjects[ "air" ] = &air;
	mObjects[ "stoneBrickWall" ] = &stoneBrickWall;
	mObjects[ "grass" ] = &grass;
	mObjects[ "dirt" ] = &dirt;
	mObjects[ "stoneWall" ] = &stoneBrickWall;
	mObjects[ "human" ] = &human;
}
