/*
 * groundControlServer.h
 *
 *  Created on: Sep 12, 2013
 *      Author: Greg
 */

#ifndef GROUNDCONTROLSERVER_H_
#define GROUNDCONTROLSERVER_H_

#include "message.h"
#include "linkedList.h"
#include "drone.h"
#include "communication.h"
#include <iostream>
#include <thread>
using namespace std;

#define MAX_OBJECTS	50

class groundControlServer
{
public:
	groundControlServer();
	~groundControlServer();

private:
	void start();
	void interface();
	void handleMessages();
	void messageFilter(message *);
	void messageRouter(message *);

	void returnDroneList(message *);
	void addDrone(message *);

	thread * runner;

	unsigned int sleep_time;

	linkedList * rx_queue;
	linkedList * tx_queue;
	linkedList * log_list;
	linkedList * client_list;
	linkedList * drone_list;

	communication * netCom;
};

#endif
