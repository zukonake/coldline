#pragma once

#include <world/Common.hpp>

class Body
{
	public:
	Body() = default;
	Body( world::Point const &position );

	virtual ~Body() = default;

	virtual bool move( world::Vector const &by );
	virtual bool teleport( world::Point const &to );

	virtual world::Point const &getPosition() const noexcept;
	private:
	virtual bool canMove( world::Point const &to ) const = 0;

	world::Point mPosition;
};
