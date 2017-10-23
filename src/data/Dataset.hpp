#pragma once

#include <type_traits>
#include <unordered_map>
#include <string>
//
#include <data/Exception.hpp>
#include <data/Loadable.hpp>

class Dataset
{
	public:
	Dataset() noexcept;

	template< typename T >
	T const &at( std::string const &key ) const;
	private:
	std::unordered_map< std::string, const Loadable * > mObjects;
};

template< typename T >
T const &Dataset::at( std::string const &key ) const
{
	static_assert( std::is_base_of< Loadable, T >::value, "Dataset only holds objects of base Loadable" );
	try
	{
		T const &returnValue = dynamic_cast< T const & >( *mObjects.at( key ));
		return returnValue;
	}
	catch( std::out_of_range &e )
	{
		throw data::InvalidDatasetKeyError( "No such key: " + key );
	}
}
