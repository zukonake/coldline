/**
 * @file geometry/Space2D.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <geometry/Vector2D.hpp>
#include <geometry/Line2D.hpp>

namespace geometry
{

template< typename TCoordinate, typename TLength >
struct Space2D
{
	typedef Vector2D< TCoordinate > Point;
	typedef Vector2D< TLength > Size;
	typedef Vector2D< double > Origin;
	typedef Line2D< TLength > Diagonal;
	typedef TLength Area;

	constexpr Space2D() noexcept = default;
	constexpr Space2D< TCoordinate, TLength > operator=( Space2D< TCoordinate, TLength > const &that ) noexcept;
	constexpr Space2D( Point const &pos, Size const &size ) noexcept;
	//TODO converions?

	constexpr bool operator==( Space2D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator!=( Space2D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator<=( Space2D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator>=( Space2D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator<( Space2D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator>( Space2D< TCoordinate, TLength > const &that ) const noexcept;

	constexpr Diagonal getDiagonal() const noexcept;
	constexpr Area getArea() const noexcept;
	constexpr Origin getOrigin() const noexcept;
	constexpr Space2D< TCoordinate, TLength > getBorder() const noexcept;
	constexpr bool touches( Space2D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool intersects( Space2D< TCoordinate, TLength > const &that ) const noexcept;

	Point pos;
	Size size;

	TCoordinate &x = pos.x;
	TCoordinate &y = pos.y;
	TLength &w = size.x;
	TLength &h = size.y;
};



template< typename TCoordinate, typename TLength >
constexpr Space2D< TCoordinate, TLength >::Space2D( Point const &pos, Size const &size ) noexcept :
	pos( pos ),
	size( size )
{

}



template< typename TCoordinate, typename TLength >
constexpr Space2D< TCoordinate, TLength > Space2D< TCoordinate, TLength >::operator=( Space2D< TCoordinate, TLength > const &that ) noexcept
{
	pos = that.pos;
	size = that.size;
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::operator==( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	return pos == that.pos && size == that.size;
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::operator!=( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	return pos != that.pos || size != that.size;
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::operator<=( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	return getArea() <= that.getArea();
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::operator>=( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	return getArea() >= that.getArea();
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::operator<( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	return getArea() < that.getArea();
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::operator>( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	return getArea() > that.getArea();
}



template< typename TCoordinate, typename TLength >
constexpr Space2D< TCoordinate, TLength > Space2D< TCoordinate, TLength >::getBorder() const noexcept
{
	static_assert( std::is_integral< TCoordinate >::value &&
		std::is_integral< TLength >::value,
		"Space2D must have parameters of integral type" );
	return Space2D( pos - Point( 1, 1 ), size + Size( 2, 2 ));
}

template< typename TCoordinate, typename TLength >
constexpr typename Space2D< TCoordinate, TLength >::Area Space2D< TCoordinate, TLength >::getArea() const noexcept
{
	return w * h;
}

template< typename TCoordinate, typename TLength >
constexpr typename Space2D< TCoordinate, TLength >::Origin Space2D< TCoordinate, TLength >::getOrigin() const noexcept
{
	return { x + ( w / 2.0 ), y + ( h / 2.0 )};
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::touches( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	if( std::is_integral< TCoordinate >::value && std::is_integral< TLength >::value )
	{
		return getBorder().intersects( that );
	}
	else
	{
		return intersects( that );
	}
}

template< typename TCoordinate, typename TLength >
constexpr bool Space2D< TCoordinate, TLength >::intersects( Space2D< TCoordinate, TLength > const &that ) const noexcept
{
	return (
			x < that.x + that.w &&
			y < that.y + that.h &&
			x + w > that.x &&
			y + h > that.y);
}

}
