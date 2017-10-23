#pragma once

#include <data/Loadable.hpp>
#include <render/Renderable.hpp>
#include <world/block/BlockShape.hpp>
#include <render/Tile.hpp>

class Dataset;
class DataMap;

class BlockType : public Renderable, public Loadable
{
	public:
	BlockType( Dataset const &dataset, DataMap const &dataMap );
	BlockType( Tile const &tile, BlockShape const &shape ) noexcept;

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const override;

	Tile mTile;
	BlockShape mShape;
};
