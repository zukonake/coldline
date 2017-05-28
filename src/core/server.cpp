#include <stdexcept>
//
#include <core/client.hpp>
#include <data/inputData.hpp>
#include <world/generator/randomWallsGenerator.hpp>
#include "server.hpp"

Server::Server() :
	mWorld( RandomWallsGenerator( mDataset, 0.15f ))
{

}

Server::~Server()
{
	for( auto iPair = mClients.cbegin(); iPair != mClients.cend(); )
	{
		iPair->second.second->disconnect();
	}
}

void Server::loop()
{
	while( !mClients.empty())
	{
		mWorld.simulate();
		for( auto iPair = mClients.begin(); iPair != mClients.end(); )
		{
			Client *client = iPair->second.second;
			iPair->second.first.receiveInputData( iPair->second.second->requestInputData() );
			iPair->second.second->receiveOutputData( iPair->second.first.requestOutputData() );
			if( !client->isConnected())
			{
				break; //TODO works only with one client...
			}
		}
	}
}

void Server::connect( Client* client )
{
	mClients.emplace( client->getName(),
		std::pair< Player, Client * >( Player( mDataset, mWorld ), client ));
}

void Server::disconnect( Client* client )
{
	mClients.erase( client->getName());
}

void Server::cleanClients()
{
	for( auto iPair = mClients.cbegin(); iPair != mClients.cend(); )
	{
		if( !iPair->second.second->isConnected())
		{
			iPair = mClients.erase( iPair );
		}
		else
		{
			++iPair;
		}
	}
}
