#pragma once

#include <global.hpp>
#include <world/tile/tileSubtype.hpp>

TileSubtype const stoneFloor
{ 
	{ 0 * global::textureSpriteSize.x, 0 * global::textureSpriteSize.y },
	false
};

TileSubtype const stoneWall
{ 
	{ 1 * global::textureSpriteSize.x, 0 * global::textureSpriteSize.y },
	true
};
