#pragma once

#include <geometry/Vector2D.hpp>
#include <geometry/Line2D.hpp>
#include <geometry/Space2D.hpp>

namespace render
{

typedef float Coordinate;
typedef float Length;
typedef ::geometry::Vector2D< int > FieldOfView;
typedef ::geometry::Vector2D< Coordinate > Point;
typedef ::geometry::Vector2D< Coordinate > Scale;
typedef ::geometry::Vector2D< Coordinate > Size;
typedef ::geometry::Vector2D< Coordinate > Vector;
typedef ::geometry::Line2D< Coordinate > Line;
typedef ::geometry::Space2D< Coordinate, Length > Surface;

}

