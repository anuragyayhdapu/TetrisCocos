#include "NetworkHandler.h"

void NetworkHandler::initialize()
{
	// enet network library code goes here
}

// TODO: should run on a seperate thread
void NetworkHandler::listenForDataOnNetwork()
{
	// on a separate thread, continuously listen for incoming packets
	// if any data recieved, unpack it, and notify Scene


}

// TODO: should be asynchronous function
void NetworkHandler::pushDataToNetwork(const Board& board)
{
	// recieve data

	// pack 

	// send
}
