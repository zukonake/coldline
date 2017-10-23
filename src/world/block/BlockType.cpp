#include <data/DataMap.hpp>
#include "BlockType.hpp"

BlockType::BlockType( Dataset const &dataset, DataMap const &dataMap ) :
	mTile( dataset, dataMap )
	//mShape( dataMap ) TODO
{

}

BlockType::BlockType( Tile const &tile, BlockShape const &shape ) noexcept :
	mTile( tile ),
	mShape( shape )
{

}

void BlockType::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const {
	mTile.render( target, states, color );
}
