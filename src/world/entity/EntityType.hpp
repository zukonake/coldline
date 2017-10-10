#pragma once

#include <data/Loadable.hpp>
#include <render/Renderable.hpp>
#include <render/Tile.hpp>

class Dataset;
class DataMap;

class EntityType : public Renderable, public Loadable
{
	public:
	EntityType( Dataset const &dataset, DataMap const &dataMap );
	EntityType( Tile const &tile, bool const &solid ) noexcept;

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const override;

	Tile mTile;
	bool mSolid;
};
