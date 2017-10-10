#include <render/Tileset.hpp>
#include <render/Tile.hpp>
#include <world/block/BlockType.hpp>
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

BlockType stoneFloor =
{
	{
		blockTiles,
		{ 1, 0 }
	},
	false
};

BlockType stoneBrickWall =
{
	{
		blockTiles,
		{ 2, 0 }
	},
	true
};

BlockType grass =
{
	{
		blockTiles,
		{ 3, 0 }
	},
	false
};

BlockType stoneWall =
{
	{
		blockTiles,
		{ 0, 1 }
	},
	true
};

EntityType human =
{
	{
		creatureTiles,
		{ 0, 0 }
	},
	true
};

Dataset::Dataset() noexcept
{
	mObjects[ "nothing" ] = &nothing;
	mObjects[ "blockTiles" ] = &blockTiles; //TODO is it really needed?
	mObjects[ "stoneFloor" ] = &stoneFloor;
	mObjects[ "stoneBrickWall" ] = &stoneBrickWall;
	mObjects[ "grass" ] = &grass;
	mObjects[ "stoneWall" ] = &stoneBrickWall;
	mObjects[ "human" ] = &human;
}
