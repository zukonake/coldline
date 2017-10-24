#include <world/block/BlockType.hpp>
#include "Block.hpp"

Block::Block( Block const &that ) noexcept :
	mType( that.mType ),
	mShape( that.mShape )
{

}

Block::Block( BlockType const &type, BlockShape const &shape ) noexcept :
	mType( &type ),
	mShape( shape )
{

}

Block &Block::operator=( Block const &that ) noexcept
{
	mType = that.mType;
	mShape = that.mShape;
	return *this;
}

void Block::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	mType->render( target, states, color );
}

BlockShape const &Block::getShape() const
{
	return mShape;
}
