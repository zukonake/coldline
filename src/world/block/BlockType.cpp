#include <data/DataMap.hpp>
#include "BlockType.hpp"

BlockType::BlockType( Dataset const &dataset, DataMap const &dataMap ) :
	mTile( dataset, dataMap ),
	mSolid( dataMap.getBool( "solid" ))
{

}

BlockType::BlockType( Tile const &tile, bool const &solid ) noexcept :
	mTile( tile ),
	mSolid( solid )
{

}

void BlockType::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	mTile.render( target, states, color );
}
