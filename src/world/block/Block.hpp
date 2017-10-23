#pragma once

#include <render/Renderable.hpp>
#include <world/block/BlockShape.hpp>

class Tile;
class BlockType;

class Block : public Renderable
{
	public:
	Block() = default;
	Block( Block const &that ) noexcept;
	Block( BlockType const &type ) noexcept;

	Block &operator=( Block const &that ) noexcept;
	Block &operator=( BlockType const &that ) noexcept;

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const override;

	BlockShape const &getShape() const;
	private:
	BlockType const *mType;
};
