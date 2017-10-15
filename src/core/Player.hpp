#pragma once

#include <vector>
//
#include <SFML/Window/Event.hpp>
//
#include <render/Renderable.hpp>
#include <render/Camera.hpp>

class Dataset;
class World;

class Player : public Renderable
{
	public:
	Player( Dataset const &dataset, World &world );

	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color) const override;

	bool isDead() const;
	bool hasDoneAction() const;

	void resetAction();

	void handleEvents( std::vector< sf::Event > const &events );
	private:
	void handleEvent( sf::Event const &event );
	void move( world::Vector const &by );
	Dataset const &mDataset;
	World &mWorld;
	Entity &mEntity;
	Camera mCamera;

	bool mDead;
	bool mDoneAction;
};
