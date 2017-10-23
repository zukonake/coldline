#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>
//
#include <world/Common.hpp>

class World;
class Tile;

class WorldRenderer
{
	public:
	WorldRenderer( World const &world, Tile const &nothing, float const shadeLevel );

	void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color,
		world::Point const &source, world::Point position ) const;
	private:
	World const &mWorld;
	Tile const &mNothing;
	float mShadeLevel;
};
