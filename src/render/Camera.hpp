#pragma once

#include <render/Common.hpp>
#include <render/Renderable.hpp>
#include <render/WorldRenderer.hpp>
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
		WorldRenderer const &renderer,
		Entity const &entity );

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const override;

	void lock();
	void unlock();
	void changeScale( render::Scale const &change );
	bool isLocked() const noexcept;

	virtual world::Point const &getPosition() const noexcept override;
	private:
	virtual bool canMove( world::Point const &to ) const override;

	Entity const &mEntity;

	WorldRenderer mRenderer;

	render::Size mScreenSize;
	render::Size mSpriteSize; //TODO replace with some config?

	bool mLocked;
};
