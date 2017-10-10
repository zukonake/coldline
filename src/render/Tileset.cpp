#include <render/Common.hpp>
#include <data/DataMap.hpp>
#include "Tileset.hpp"

Tileset::Tileset( DataMap const &dataMap ) :
	mTileSize( dataMap.toVector2D< render::Length >())
{
	mTexture.loadFromFile( dataMap.getString( "path" ));
}

Tileset::Tileset( std::string const &path, render::Size const &tileSize ) :
	mTileSize( tileSize )
{
	mTexture.loadFromFile( path );
}

render::Size const &Tileset::getTileSize() const noexcept
{
	return mTileSize;
}

sf::Texture const &Tileset::getTexture() const noexcept
{
	return mTexture;
}
