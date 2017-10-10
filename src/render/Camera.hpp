#pragma once

#include <render/Common.hpp>
#include <render/Renderable.hpp>
#include <world/Body.hpp>

class Tile;
class World;
class Entity;

class Camera : public virtual Renderable, public Body
{
	public:
	Camera(
		render::Size const &screenSize,
		render::Size const &spriteSize,
		World const &world,
		Tile const &nothing,
		Entity const &entity );

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const override;
	private:
	virtual bool canMove( world::Point const &to ) const override;

	bool mLocked;

	render::Size mScreenSize;
	render::Size mSpriteSize; //TODO replace with some config?
	World const &mWorld;
	Tile const &mNothing;
	Entity const &mEntity;
};
