/*
 * communication.cpp
 *
 *  Created on: Oct 20, 2013
 *      Author: greg
 */

#include "communication.h"

/******************************************************************
*
******************************************************************/
communication::communication(linkedList * tx, linkedList * rx, linkedList * log, linkedList * clients)
{
	client_list = clients;
	tx_queue = tx;
	rx_queue = rx;
	log_list = log;
	clientListiner = new thread(&communication::listen, this);
	packetTx = new thread(&communication::send, this);
}

/******************************************************************
*
******************************************************************/
communication::~communication()
{

}

/******************************************************************
*
******************************************************************/
void communication::listen()
{
	int sd, newSd;
	sd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in server;
	bzero( (char *)&server, sizeof( server ) );
	server.sin_family =AF_INET;
	server.sin_addr.s_addr = htonl( INADDR_ANY );
	server.sin_port = htons( 12345 );

	bind( sd, (sockaddr *)&server, sizeof( server ) );

	sockaddr_in clientSoc;
	socklen_t len=sizeof(clientSoc);

	while( true )
	{
		newSd = accept(sd, (sockaddr *)&clientSoc, &len);
		client_list->pushToBack( new client(newSd, rx_queue) );
		close(sd);
		//read( newSd, buf2, sizeof( buf2 ) );
	 }

}

/******************************************************************
*
******************************************************************/
void communication::send()
{
	while(true)
	{
		if(!tx_queue->isEmpty())
			txPacket( (message*)tx_queue->popFront());
	}
}

/******************************************************************
*
******************************************************************/
void communication::txPacket(message * send_message)
{
	char packetSize = 4;

	int fd = send_message->getDest();
	char * packet = new char[packetSize];

	packet[0] = packetSize;							// Number of bytes.
	packet[1] = send_message->getSource();			// Packet Source.
	packet[2] = (char)send_message->getCommand();	// The command.
	packet[3] = (char)send_message->getValue();		// The value.

	write(fd, packet, packet[0]);
}

/******************************************************************
*
******************************************************************/
client * communication::findClient(int id)
{
	for(int i = 0; i < client_list->getLength(); i++)
	{
		client * theClient = (client*)client_list->peekAt(i);
		if( theClient->getID() == id )
			return theClient;
	}
	return NULL;
}

