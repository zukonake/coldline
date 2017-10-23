#include <data/DataMap.hpp>
#include "EntityType.hpp"

EntityType::EntityType( Dataset const &dataset, DataMap const &dataMap ) :
	mTile( dataset, dataMap )
{

}

EntityType::EntityType( Tile const &tile ) noexcept :
	mTile( tile )
{

}

void EntityType::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	mTile.render( target, states, color );
}
