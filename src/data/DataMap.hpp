#pragma once

#include <cstddef>
#include <string>
//
#include <geometry/Vector2D.hpp>
#include <geometry/Vector3D.hpp>

class DataMap
{
	public:
	virtual ~DataMap() = default;

	virtual bool getBool( std::string const &key ) const = 0;
	virtual bool getBool( std::size_t const &index ) const = 0;
	virtual int getInt( std::string const &key ) const = 0;
	virtual int getInt( std::size_t const &index ) const = 0;
	virtual double getDouble( std::string const &key ) const = 0;
	virtual double getDouble( std::size_t const &index ) const = 0;
	virtual std::string getString( std::string const &key ) const = 0;
	virtual std::string getString( std::size_t const &index ) const = 0;
	virtual DataMap const *getDataMap( std::string const &key ) const = 0;
	virtual DataMap const *getDataMap( std::size_t const &index ) const = 0;

	template< typename T >
	geometry::Vector2D< T > toVector2D() const;
	template< typename T >
	geometry::Vector3D< T > toVector() const;
};

template< typename T >
geometry::Vector2D< T > DataMap::toVector2D() const
{ //TODO other types?
	return geometry::Vector2D< T >( getDouble( 0 ), getDouble( 1 ));
}

template< typename T >
geometry::Vector3D< T > DataMap::toVector() const
{
	return geometry::Vector3D< T >( getDouble( 0 ), getDouble( 1 ), getDouble( 2 ));
}
