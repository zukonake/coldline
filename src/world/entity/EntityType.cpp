#include <data/DataMap.hpp>
#include "EntityType.hpp"

EntityType::EntityType( Dataset const &dataset, DataMap const &dataMap ) :
	mTile( dataset, dataMap ),
	mSolid( dataMap.getBool( "solid" ))
{

}

EntityType::EntityType( Tile const &tile, bool const &solid ) noexcept :
	mTile( tile ),
	mSolid( solid )
{

}

void EntityType::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	mTile.render( target, states, color );
}
