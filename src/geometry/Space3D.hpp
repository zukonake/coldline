/**
 * @file geometry/Space3D.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3D
 */

#pragma once

#include <geometry/Vector3D.hpp>
#include <geometry/Line3D.hpp>

namespace geometry
{

template< typename TCoordinate, typename TLength >
struct Space3D
{
	typedef Vector3D< TCoordinate > Point;
	typedef Vector3D< TLength > Size;
	typedef Vector3Dd Origin;
	typedef Line3D< TLength > Diagonal;
	typedef TLength Volume;

	constexpr Space3D() noexcept = default;
	constexpr Space3D( Space3D< TCoordinate, TLength > const &that ) noexcept = default;
	constexpr Space3D( Point const &pos, Size const &size ) noexcept;
	template< typename TTCoordinate, typename TTLength >
	constexpr Space3D( Space3D< TTCoordinate, TTLength > const &that ) noexcept;

	template< typename TTCoordinate, typename TTLength >
	constexpr operator Space3D< TTCoordinate, TTLength >() noexcept;

	constexpr Space3D< TCoordinate, TLength > operator=( Space3D< TCoordinate, TLength > const &that ) noexcept;

	constexpr bool operator==( Space3D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator!=( Space3D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator<=( Space3D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator>=( Space3D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator<( Space3D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool operator>( Space3D< TCoordinate, TLength > const &that ) const noexcept;

	constexpr Diagonal getDiagonal() const noexcept;
	constexpr Volume getVolume() const noexcept;
	constexpr Origin getOrigin() const noexcept;
	constexpr Space3D< TCoordinate, TLength > getBorder() const noexcept;
	constexpr bool touches( Space3D< TCoordinate, TLength > const &that ) const noexcept;
	constexpr bool intersects( Space3D< TCoordinate, TLength > const &that ) const noexcept;

	Point pos;
	Size size;

	TCoordinate &x = pos.x;
	TCoordinate &y = pos.y;
	TCoordinate &z = pos.z;
	TLength &w = size.x;
	TLength &h = size.y;
	TLength &d = size.z;
};



template< typename TCoordinate, typename TLength >
constexpr Space3D< TCoordinate, TLength > Space3D< TCoordinate, TLength >::operator=( Space3D< TCoordinate, TLength > const &that ) noexcept
{
	pos = that.pos;
	size = that.size;
}

template< typename TCoordinate, typename TLength >
template< typename TTCoordinate, typename TTLength >
constexpr Space3D< TCoordinate, TLength >::Space3D( Space3D< TTCoordinate, TTLength > const &that ) noexcept :
	pos( static_cast< Point >( that.pos )),
	size( static_cast< Size >( that.size ))
{

}

template< typename TCoordinate, typename TLength >
template< typename TTCoordinate, typename TTLength >
constexpr Space3D< TCoordinate, TLength >::operator Space3D< TTCoordinate, TTLength >() noexcept
{
	return Space3D< TTCoordinate, TTLength >( pos, size );
}

template< typename TCoordinate, typename TLength >
constexpr bool Space3D< TCoordinate, TLength >::operator==( Space3D< TCoordinate, TLength > const &that ) const noexcept
{
	return pos == that.pos && size == that.size;
}

template< typename TCoordinate, typename TLength >
constexpr bool Space3D< TCoordinate, TLength >::operator!=( Space3D< TCoordinate, TLength > const &that ) const noexcept
{
	return pos != that.pos || size != that.size;
}

template< typename TCoordinate, typename TLength >
constexpr bool Space3D< TCoordinate, TLength >::operator<=( Space3D< TCoordinate, TLength > const &that ) const noexcept
{
	return getVolume() <= that.getVolume();
}

template< typename TCoordinate, typename TLength >
constexpr bool Space3D< TCoordinate, TLength >::operator>=( Space3D< TCoordinate, TLength > const &that ) const noexcept
{
	return getVolume() >= that.getVolume();
}

template< typename TCoordinate, typename TLength >
constexpr bool Space3D< TCoordinate, TLength >::operator<( Space3D< TCoordinate, TLength > const &that ) const noexcept
{
	return getVolume() < that.getVolume();
}

template< typename TCoordinate, typename TLength >
constexpr bool Space3D< TCoordinate, TLength >::operator>( Space3D< TCoordinate, TLength > const &that ) const noexcept
{
	return getVolume() > that.getVolume();
}



template< typename TCoordinate, typename TLength >
constexpr Space3D< TCoordinate, TLength > Space3D< TCoordinate, TLength >::getBorder() const noexcept
{
	static_assert( std::is_integral< TCoordinate >::value &&
		std::is_integral< TLength >::value,
		"Space3D must have parameters of integral type" );
	return Space3D( pos - Point( 1, 1, 1 ), size + Size( 2, 2, 2 ));
}

template< typename TCoordinate, typename TLength >
constexpr typename Space3D< TCoordinate, TLength >::Volume Space3D< TCoordinate, TLength >::getVolume() const noexcept
{
	return w * h * d;
}

template< typename TCoordinate, typename TLength >
constexpr typename Space3D< TCoordinate, TLength >::Origin Space3D< TCoordinate, TLength >::getOrigin() const noexcept
{
	return { x + ( w / 2.0 ), y + ( h / 2.0 ), z + ( d / 2.0 )};
}

template< typename TCoordinate, typename TLength >
constexpr bool Space3D< TCoordinate, TLength >::touches( Space3D< TCoordinate, TLength > const &that ) const noexcept
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
constexpr bool Space3D< TCoordinate, TLength >::intersects( Space3D< TCoordinate, TLength > const &that ) const noexcept
{
	return (
			x < that.x + that.w &&
			y < that.y + that.h &&
			z < that.z + that.d &&
			x + w > that.x &&
			y + h > that.y &&
			z + d > that.z );
}

}
