#include <world/World.hpp>
#include "Camera.hpp"

Camera::Camera(
	render::Size const &screenSize,
	render::Size const &spriteSize,
	World const &world,
	Tile const &nothing,
	Entity const &entity ) :
	mScreenSize( screenSize ),
	mSpriteSize( spriteSize ),
	mWorld( world ),
	mNothing( nothing ),
	mEntity( entity )
{

}

void Camera::render( sf::RenderTarget &target, sf::RenderStates states, sf::Color color ) const
{
	world::Point const &position = Body::getPosition();
	//we get the camera's position in the world

	states.transform.scale( mSpriteSize.x, mSpriteSize.y );
	//we scale the screen so that coordinate of 1 is equal to 1 tile
	//(as opposed to 1 pixel)

	render::Size gridHalf = ( mScreenSize / mSpriteSize ) / render::Scale( 2, 2 );
	//gridHalf is half of the screen's sprite grid

	render::FieldOfView fov = gridHalf + render::Size( 1.5, 1.5 );
	//fov is the range in which player can look in all directions (the x and y are separated here)
	//we need to divide the screen in half, add 1 to it and then add 0.5 to round it from float
	//we add 1 because this is the row and column where the player is rendered

	render::Point gridCenter = gridHalf - render::Size( 0.5, 0.5 );
	//screenCenter is position of the center tile
	//we subtract 0.5 because we need the top left corner of the tile (its position)

	render::Point topLeft = gridCenter - fov;
	//topLeft defines point from which the rendering starts (usually off the screen)

	states.transform.translate( topLeft.x, topLeft.y );

	world::Point iterator = position;
	for( iterator.y = position.y - fov.y; iterator.y <= position.y + fov.y; iterator.y++ )
	{
		for( iterator.x = position.x - fov.x; iterator.x <= position.x + fov.x; iterator.x++ )
		{
			if( iterator != position )
			{
				mWorld[ iterator ].render( target, states, color );
			}
			states.transform.translate( 1, 0 );
			//we move the transform one to the right (one tile)
		}
		states.transform.translate(( fov.x * -2 ) - 1, 0 );
		//we need to translate the transform back to the starting x

		states.transform.translate( 0, 1 );
		//we move the transform one to the down (one tile)
	}
}

bool Camera::canMove( world::Point const &to ) const
{
	( void )to;
	return true;
}
