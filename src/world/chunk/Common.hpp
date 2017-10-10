#pragma once

#include <geometry/Vector3D.hpp>

namespace chunk
{

typedef long long Coordinate;
typedef unsigned InternalCoordinate;
typedef unsigned Length;
typedef ::geometry::Vector3D< Coordinate > Point;
typedef ::geometry::Vector3D< InternalCoordinate > InternalPoint;
typedef ::geometry::Vector3D< Length > Size;

}
