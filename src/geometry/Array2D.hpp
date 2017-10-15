/*
 * @file geometry/Array2D.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>
#include <array>
//
#include <geometry/Vector2D.hpp>
#include <geometry/Array2DInterface.hpp>

namespace geometry
{

template< typename T, unsigned long long width, unsigned long long height >
class Array2D : public Array2DInterface< T >
{
public:
	typedef std::array< T, width * height >::iterator iterator;
	typedef std::array< T, width * height >::iterator const_iterator;

	Array2D() = default;
	Array2D( Array2D< T, width, height > const &that ) = default;
	Array2D( Array2D< T, width, height > &&that ) = default;
	Array2D( T const &fill );

	Array2D &operator=( Array2D< T, width, height > const &that ) = default;
	Array2D &operator=( Array2D< T, width, height > &&that ) = default;

	virtual T &operator[]( Vector2Dull const &index ) override;
	virtual T const &operator[]( Vector2Dull const &index ) const override;

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;
private:
	std::array< T, width * height > mValue;
};

template< typename T, unsigned long long width, unsigned long long height >
Array2D< T, width, height >::Array2D( T const &fill )
{
	std::fill( this->begin(), this->end(), fill );
}

template< typename T, unsigned long long width, unsigned long long height >
T &Array2D< T, width, height >::operator[]( Vector2Dull const &index )
{
	return mValue.at( index.x + ( index.y * width ));
}

template< typename T, unsigned long long width, unsigned long long height >
T const &Array2D< T, width, height >::operator[]( Vector2Dull const &index ) const
{
	return mValue.at( index.x + ( index.y * width ));
}

template< typename T, unsigned long long width, unsigned long long height >
typename Array2D< T, widht, height >::iterator begin() noexcept
{
	return mValue.begin();
}

template< typename T, unsigned long long width, unsigned long long height >
typename Array2D< T, widht, height >::const_iterator begin() const noexcept
{
	return mValue.begin();
}

template< typename T, unsigned long long width, unsigned long long height >
typename Array2D< T, widht, height >::const_iterator cbegin() const noexcept
{
	return mValue.cbegin();
}

template< typename T, unsigned long long width, unsigned long long height >
typename Array2D< T, widht, height >::iterator end() noexcept
{
	return mValue.end();
}

template< typename T, unsigned long long width, unsigned long long height >
typename Array2D< T, widht, height >::const_iterator end() const noexcept
{
	return mValue.end();
}

template< typename T, unsigned long long width, unsigned long long height >
typename Array2D< T, widht, height >::const_iterator cend() const noexcept
{
	return mValue.cend();
}

}
