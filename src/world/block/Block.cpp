#include <world/block/BlockType.hpp>
#include "Block.hpp"

Block::Block( Block const &that ) noexcept :
	mType( that.mType )
{

}

Block::Block( BlockType const &type ) noexcept :
	mType( &type )
{

}

Block &Block::operator=( Block const &that ) noexcept
{
	mType = that.mType;
	return *this;
}

Block &Block::operator=( BlockType const &that ) noexcept
{
	mType = &that;
	return *this;
}

void Block::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	mType->render( target, states, color );
}

bool Block::isPassable() const noexcept
{
	return !mType->mSolid;
}
