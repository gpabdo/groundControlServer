/*
 * groundControlServer.cpp
 *
 *  Created on: Sep 13, 2013
 *      Author: greg
 */

#include "groundControlServer.h"

/******************************************************************
*
******************************************************************/
groundControlServer::groundControlServer()
{
	cout << "Server initializing" << endl;
	sleep_time = 0;
	log_list = new linkedList();
	tx_queue = new linkedList();
	rx_queue = new linkedList();
	drone_list = new linkedList();
	client_list = new linkedList();
	netCom = new communication(tx_queue, rx_queue, log_list, client_list);
	runner  = new thread(&groundControlServer::interface, this);
	start();
}

/******************************************************************
*
******************************************************************/
groundControlServer::~groundControlServer()
{

}

/******************************************************************
*
******************************************************************/
void groundControlServer::start()
{
	cout << "Server started" << endl;
	int sleep_time = 0;
	while( true )
	{
		handleMessages();
	}
}

/******************************************************************
*
******************************************************************/
void groundControlServer::interface()
{
	cout << "Welcome to Ground Control Server" << endl;

	while( true )
	{
		cout << "Build a packet" << endl;
		cout << "Input destination: ";
		int dest;
		cin >> dest;

		cout << "Input command: ";
		int command;
		cin >> command;

		cout << "Input value: ";
		int value;
		cin >> value;

		rx_queue->pushToBack(new message(0, command, value, dest));
	}
}

/******************************************************************
* Pulls the message from the queue to be further processed by
* the filter.
******************************************************************/
void groundControlServer::handleMessages()
{
	// Pop out of master queue and route packets to destinations.
	if(rx_queue->isEmpty())
		sleep_time++;
	else
	{
		message * data = (message*)rx_queue->popFront();	// Get a message from the queue.
		messageFilter( data );
		sleep_time = 0;
	}

	if(sleep_time > 10)
	{
		usleep(100000);
		sleep_time = 10;
	}
}

/******************************************************************
* Will someday check the message.
******************************************************************/
void groundControlServer::messageFilter(message * data)
{
	if(data->getDest() == 0)
	{
		int command = data->getCommand();
		if( command == 0)
			returnDroneList( data );

		if(command == 1)
			addDrone( data );

		return;
	}

	messageRouter(data);
}

/******************************************************************
* Send the message to the appropriate destination.
******************************************************************/
void groundControlServer::messageRouter(message * data)
{
	for( int i = 0; i < drone_list->getLength(); i++)
	{
		drone *test = (drone*)drone_list->peekAt(i);
		if(data->getDest() == test->getID())
		{
			test->submitMessage( data );
			return;
		}
	}
}

/******************************************************************
*
******************************************************************/
void groundControlServer::returnDroneList(message * data)
{
	// If there are no drones, return a 0,0 packet.
	if( drone_list->isEmpty())
	{
		tx_queue->pushToBack(new message(0,0,0,data->getSource()));
		return;
	}

	// For each drone, send a packet with the id and name.
	for( int i = 0; i < drone_list->getLength(); i++)
	{
		drone *temp_drone = (drone*)drone_list->peekAt(i);
		tx_queue->pushToBack(new message(temp_drone->getID(),0,0,
				data->getSource(),temp_drone->getString()));
	}
}

/******************************************************************
*
******************************************************************/
void groundControlServer::addDrone(message * newDrone)
{
	drone_list->pushToFront(new drone(0, tx_queue));
}
