/*
 * @file geometry/Array2DInterface.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <geometry/Vector2D.hpp>

namespace geometry
{

template< typename T >
class Array2DInterface
{
	public:
	virtual T &operator[]( Vector2Dull const &index ) = 0;
	virtual T const &operator[]( Vector2Dull const &index ) const = 0;
};

}
