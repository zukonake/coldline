#pragma once

#include <render/Renderable.hpp>
#include <world/Common.hpp>
#include <world/Body.hpp>

class Tile;
class EntityType;
class World;

class Entity : public virtual Renderable, public Body
{
	public:
	Entity( World &mWorld, world::Point const &position, EntityType const &type, bool const &chunkAnchor ) noexcept;

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const override;

	virtual bool move( world::Vector const &by ) override;
	virtual bool teleport( world::Point const &to ) override;

	bool isChunkAnchor() const noexcept;

	void simulate();
	private:
	virtual bool canMove( world::Point const &to ) const override;

	World &mWorld;
	EntityType const &mType;
	bool mChunkAnchor;
};
