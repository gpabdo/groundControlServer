/*
 * state.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: Greg
 */

#include "drone.h"

/******************************************************************
*
******************************************************************/
drone::drone(int ID, linkedList * tx)
{
	drone_ID = ID;
	tx_queue = tx;

	state = (linkedList**)new linkedList[LIST_LENGTH];
	for( int i = 0; i < LIST_LENGTH; i++)
		state[i] = new linkedList();

	clients = (linkedList**)new linkedList[LIST_LENGTH];
	for( int i = 0; i < LIST_LENGTH; i++)
		clients[i] = new linkedList();

	runner = new thread(&drone::run, this);

}
/******************************************************************
*
******************************************************************/
drone::~drone()
{

}

/******************************************************************
*
******************************************************************/
void drone::run()
{
	while(true)
	{
		// If the queue is empty, busy loop.
		if(rx_queue->isEmpty())
			continue;

		message * next_message = (message*)rx_queue->popFront();\
		int command = next_message->getCommand();

		// Attach a client to get updates about a state.
		if( command == 5)
			attach(next_message);

		// Detach a client from a state change update.
		else if( command == 6)
			detachFrom(next_message, next_message->getValue());

		else if ( command > 10 && command < LIST_LENGTH )
			setState(next_message);

	}
}

/******************************************************************
*
******************************************************************/
int drone::getID()
{
	return drone_ID;
}

/******************************************************************
* Add a message to the drones receive queue to be read and
* handled.
******************************************************************/
void drone::submitMessage(message * obj)
{
	rx_queue->pushToBack(obj);
}

/******************************************************************
*
******************************************************************/
void drone::attach(message * obj)
{
	clients[obj->getValue()]->pushToBack(obj);
}

/******************************************************************
* Remove a client from all lists.
******************************************************************/
void drone::detachClient(message * obj)
{
	for(int i = 0; i < LIST_LENGTH; i++)
		detachFrom(obj, i);
}

/******************************************************************
*
******************************************************************/

void drone::detachFrom(message * obj, int detachFrom)
{
	for(int i = 0; i < clients[detachFrom]->getLength(); i++)
	{
		message * client = (message*)clients[detachFrom]->peekAt(i);
		if( client->getSource() == obj->getSource() )
			clients[detachFrom]->popAt(i);
	}
}

/******************************************************************
* Step through the clients list for the passed in field and add
* a copy of the message to the master queue to be transmitted.
******************************************************************/
void drone::sendUpdate(int command)
{
	// For everyone registered to receive status updates.
	for(int i = 0; i < clients[command]->getLength(); i++)
	{
		message *client = (message*)clients[command]->peekAt(i);
		// Create a message with drone_ID as source, i as the item to be updated
		//status->getStatus is the value and the client->getSource is where to send it.
		tx_queue->pushToBack(new message(drone_ID,i,
				getState(command), client->getSource() ));
	}

}

/******************************************************************
*
******************************************************************/
void drone::saveState(int value)
{
	if(state[value]->getLength() < FIELD_LENGTH * 2)
		return;

	//for( int i = state[value]->getLength() -1; i > FIELD_LENGTH; i--)
	//{
	//	delete state[value]->remove(i);
	//}
}

/******************************************************************
* Get the current state of the passed in peramiter.
******************************************************************/
int drone::getState(int command)
{
	message *status = (message*)state[command]->peekFront();
	return status->getValue();
}

/******************************************************************
* Add the new state to the front of the state list.
******************************************************************/
void drone::setState( message * obj)
{
	state[obj->getCommand()]->pushToFront(obj);
}

/******************************************************************
*
******************************************************************/
string drone::getString()
{
	return "";
}

