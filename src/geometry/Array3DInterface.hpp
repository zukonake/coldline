/*
 * @file geometry/Array3DInterface.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <geometry/Vector3D.hpp>

namespace geometry
{

template< typename T >
class Array3DInterface
{
	public:
	virtual ~Array3DInterface() = default;

	virtual T &operator[]( Vector3Dull const &index ) = 0;
	virtual T const &operator[]( Vector3Dull const &index ) const = 0;
};

}
