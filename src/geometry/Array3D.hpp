/*
 * @file geometry/Array3D.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <stdexcept>
#include <array>
//
#include <geometry/Common.hpp>
#include <geometry/Vector3D.hpp>
#include <geometry/Array3DInterface.hpp>

namespace geometry
{

template< typename T, Dimension width, Dimension height, Dimension depth >
class Array3D : public Array3DInterface< T >
{
public:
	typedef typename std::array< T, width * height * depth >::iterator iterator;
	typedef typename std::array< T, width * height * depth >::iterator const_iterator;

	Array3D() = default;
	Array3D( Array3D< T, width, height, depth > const &that ) = default;
	Array3D( Array3D< T, width, height, depth > &&that ) = default;
	Array3D( T const &fill );

	Array3D &operator=( Array3D< T, width, height, depth > const &that ) = default;
	Array3D &operator=( Array3D< T, width, height, depth > &&that ) = default;

	virtual T &operator[]( Vector3Dull const &index ) override;
	virtual T const &operator[]( Vector3Dull const &index ) const override;

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;
private:
	std::array< T, width * height * depth > mValue;
};

template< typename T, Dimension width, Dimension height, Dimension depth >
Array3D< T, width, height, depth >::Array3D( T const &fill )
{
	std::fill( this->begin(), this->end(), fill );
}

template< typename T, Dimension width, Dimension height, Dimension depth >
T &Array3D< T, width, height, depth >::operator[]( Vector3Dull const &index )
{
	return mValue.at( index.x + ( index.y * width ) + ( index.z * width * height ));
}

template< typename T, Dimension width, Dimension height, Dimension depth >
T const &Array3D< T, width, height, depth >::operator[]( Vector3Dull const &index ) const
{
	return mValue.at( index.x + ( index.y * width ) + ( index.z * width * height ));
}

template< typename T, Dimension width, Dimension height, Dimension depth >
typename Array3D< T, width, height, depth >::iterator Array3D< T, width, height, depth >::begin() noexcept
{
	return mValue.begin();
}

template< typename T, Dimension width, Dimension height, Dimension depth >
typename Array3D< T, width, height, depth >::const_iterator Array3D< T, width, height, depth >::begin() const noexcept
{
	return mValue.begin();
}

template< typename T, Dimension width, Dimension height, Dimension depth >
typename Array3D< T, width, height, depth >::const_iterator Array3D< T, width, height, depth >::cbegin() const noexcept
{
	return mValue.cbegin();
}

template< typename T, Dimension width, Dimension height, Dimension depth >
typename Array3D< T, width, height, depth >::iterator Array3D< T, width, height, depth >::end() noexcept
{
	return mValue.end();
}

template< typename T, Dimension width, Dimension height, Dimension depth >
typename Array3D< T, width, height, depth >::const_iterator Array3D< T, width, height, depth >::end() const noexcept
{
	return mValue.end();
}

template< typename T, Dimension width, Dimension height, Dimension depth >
typename Array3D< T, width, height, depth >::const_iterator Array3D< T, width, height, depth >::cend() const noexcept
{
	return mValue.cend();
}

}
