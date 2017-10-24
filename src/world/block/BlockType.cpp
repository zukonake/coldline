#include <data/DataMap.hpp>
#include "BlockType.hpp"

BlockType::BlockType( Dataset const &dataset, DataMap const &dataMap ) :
	mTile( dataset, dataMap )
{

}

BlockType::BlockType( Tile const &tile ) noexcept :
	mTile( tile )
{

}

void BlockType::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	mTile.render( target, states, color );
}
