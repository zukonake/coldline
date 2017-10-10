#pragma once

#include <string>
//
#include <SFML/Graphics/Texture.hpp>
//
#include <render/Common.hpp>
#include <data/Loadable.hpp>

class DataMap;

class Tileset : public Loadable
{
	public:
	Tileset( DataMap const &dataMap );
	Tileset( std::string const &path, render::Size const &tileSize );

	render::Size const &getTileSize() const noexcept;
	sf::Texture const &getTexture() const noexcept;
	private:
	render::Size mTileSize;

	sf::Texture mTexture;
};
