#include <render/Tile.hpp>
#include <world/World.hpp>
#include <world/block/BlockShape.hpp>
#include "WorldRenderer.hpp"

WorldRenderer::WorldRenderer( World const &world, Tile const &nothing, float const shadeLevel ) :
	mWorld( world ),
	mNothing( nothing ),
	mShadeLevel( shadeLevel )
{

}

void WorldRenderer::render( sf::RenderTarget &target, sf::RenderStates states,
	sf::Color color, world::Point const &source, world::Point position ) const
{
	if( mWorld.sees( source, position ))
	{
		world::Coordinate depth = 0;
		for( ; mWorld[ position + world::Point( 0, 0, -depth )].getShape() == BlockShape::EMPTY &&
				depth <= 1.f / mShadeLevel;
			depth++ );
		//we find how deep is the nearest non-empty tile
		//we are not going to render pitch black tiles so we stop at 1.f / mShadeLevel

		position.z -= depth;
		//the nearest non-empty tile is now the one we will render

		float shade = 255.f * (1.f - std::min( depth * mShadeLevel, 1.f ));
		//we calculate the shade, the deeper the tile is, the darker it is

		sf::Color shadedColor( shade, shade, shade, 255 );
		//the new tile's color

		mWorld[ position ].render( target, states, color * shadedColor );
		if( mWorld.isEntityOn( position ))
		{
			mWorld.getEntityOn( position ).render( target, states, color * shadedColor );
		}
	}
	else
	{
		mNothing.render( target, states, color );
		//this is rendered if the tile is not visible
	}
}

