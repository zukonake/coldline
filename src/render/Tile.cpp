#include <SFML/Graphics/PrimitiveType.hpp>
//
#include <render/Common.hpp>
#include <data/DataMap.hpp>
#include <data/Dataset.hpp>
#include <render/Tileset.hpp>
#include "Tile.hpp"

Tile::Tile( Dataset const &dataset, DataMap const &dataMap ) :
	mTileset( dataset.at< Tileset >( dataMap.getString( "tileset" )))
{
	render::Size const &tileSize = mTileset.getTileSize();
	render::Point const &tilesetPosition =
		dataMap.getDataMap( "position" )->toVector2D< render::Coordinate >() * tileSize;

	mVertices[ 0 ].texCoords = { tilesetPosition.x, tilesetPosition.y };
	mVertices[ 1 ].texCoords = { tilesetPosition.x + tileSize.x, tilesetPosition.y };
	mVertices[ 2 ].texCoords = { tilesetPosition.x + tileSize.x, tilesetPosition.y + tileSize.y };
	mVertices[ 3 ].texCoords = { tilesetPosition.x, tilesetPosition.y + tileSize.y };

	mVertices[ 0 ].position = { 0, 0 };
	mVertices[ 1 ].position = { 1, 0 };
	mVertices[ 2 ].position = { 1, 1 };
	mVertices[ 3 ].position = { 0, 1 };
}

Tile::Tile( Tileset const &tileset, render::Point const &position ) noexcept:
	mTileset( tileset )
{
	render::Size const &tileSize = mTileset.getTileSize();
	render::Point tilesetPosition = position * tileSize;

	mVertices[ 0 ].texCoords = { tilesetPosition.x, tilesetPosition.y };
	mVertices[ 1 ].texCoords = { tilesetPosition.x + tileSize.x, tilesetPosition.y };
	mVertices[ 2 ].texCoords = { tilesetPosition.x + tileSize.x, tilesetPosition.y + tileSize.y };
	mVertices[ 3 ].texCoords = { tilesetPosition.x, tilesetPosition.y + tileSize.y };

	mVertices[ 0 ].position = { 0, 0 };
	mVertices[ 1 ].position = { 1, 0 };
	mVertices[ 2 ].position = { 1, 1 };
	mVertices[ 3 ].position = { 0, 1 };
}

void Tile::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color) const
{
	std::array< sf::Vertex, 4 > vertices = mVertices;

	vertices[ 0 ].color = color;
	vertices[ 1 ].color = color;
	vertices[ 2 ].color = color;
	vertices[ 3 ].color = color;

	states.texture = &mTileset.getTexture();

	target.draw( vertices.data(), 4, sf::Quads, states );
}
