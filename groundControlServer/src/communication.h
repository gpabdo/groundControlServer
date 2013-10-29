/*
 * communication.h
 *
 *  Created on: Oct 20, 2013
 *      Author: greg
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Socket.h"
#include "client.h"
#include "linkedList.h"
#include "listObject.h"
#include "message.h"
#include <iostream>
#include <thread>
using namespace std;

class communication
{
public:
	// tx_queue, rx_queue, log_list, client_list
	communication(linkedList*,linkedList*,linkedList*,linkedList *);
	~communication();
	client *findClient(int);

private:
	void listener();
	void send();
	void txPacket(message*);

	thread * clientListiner;	// Thread for receving new clients.
	thread * packetTx;			// Thread for routing packets to clients.

	linkedList * client_list;	// List of clients.
	linkedList * tx_queue;		// Passed in list of packets to send
	linkedList * rx_queue;		// Passed in list to place pacets in.
	linkedList * log_list;		// Passed in list for the log file.
};

#endif /* COMMUNICATION_H_ */
