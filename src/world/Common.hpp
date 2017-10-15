#pragma once

#include <geometry/Vector3D.hpp>
#include <geometry/Line3D.hpp>
#include <geometry/Space3D.hpp>
#include <geometry/Array3D.hpp>

class Block;

namespace world
{

typedef long long Coordinate;
typedef unsigned long long Length;
typedef ::geometry::Vector3D< Coordinate > Point;
typedef ::geometry::Vector3D< Coordinate > Vector;
typedef ::geometry::Line3D< Coordinate > Line;
typedef ::geometry::Space3D< Coordinate, Length > SpaceScope;
template< Length width, Length height, Length depth >
using Space = ::geometry::Array3D< ::Block, width, height, depth >;

}
