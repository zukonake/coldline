#include "Body.hpp"

Body::Body( world::Point const &position ) :
	mPosition( position )
{

}

bool Body::move( world::Vector const &by )
{
	world::Point newPosition = mPosition + by;
	if( canMove( newPosition ))
	{
		mPosition = newPosition; //TODO check with pathfind
		return true;
	}
	else
	{
		return false;
	}
}

bool Body::teleport( world::Point const &to )
{
	if( canMove( to ))
	{
		mPosition = to;
		return true;
	}
	else
	{
		return false;
	}
}

world::Point const &Body::getPosition() const noexcept
{
	return mPosition;
}

