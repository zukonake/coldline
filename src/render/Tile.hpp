#pragma once

#include <array>
//
#include <SFML/Graphics/Vertex.hpp>
//
#include <data/Loadable.hpp>
#include <render/Common.hpp>
#include <render/Renderable.hpp>

class Dataset;
class DataMap;
class Tileset;

class Tile : public Renderable, public Loadable
{
	public:
	Tile( Dataset const &dataset, DataMap const &dataMap );
	Tile( Tileset const &tileset, render::Point const &position ) noexcept;

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const override;
	private:
	Tileset const &mTileset;
	std::array< sf::Vertex, 4 > mVertices;
};
