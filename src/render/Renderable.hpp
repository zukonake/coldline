#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>

class Renderable
{
	public:
	virtual ~Renderable() = default;
	virtual void render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const = 0;
};
