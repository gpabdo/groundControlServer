/*
 * drone.h
 *
 *  Created on: Sep 12, 2013
 *      Author: Greg
 */

#ifndef DRONE_H_
#define DRONE_H_

#include "message.h"
#include "linkedList.h"
#include "listObject.h"
#include <string>
#include <iostream>
#include <thread>
using namespace std;

#define LIST_LENGTH					200
#define FIELD_LENGTH				100

#define ACK							0
//#define DRONE_IP_ADDRESS			1
//#define DRONE_PORT				2
//#define CONNECTED					3
//#define DRONE_ID					4
#define ATTACH						5	// Attach user to a field
#define DETACH						6
#define DESIRED_THROTTLE			10
#define ACTUAL_THROTTLE				11
#define DESIRED_PITCH				12
#define ACTUAL_PITCH				13
#define DESIRED_ROLL				14
#define ACTUAL_ROLL					15
#define DESIRED_YAW					16
#define ACTUAL_YAW					17
#define DESIRED_AIRSPEED			18
#define ACTUAL_AIRSPEED				19
#define DESIRED_LANDSPEED			20
#define ACTUAL_LANDSPEED			21
#define DESIRED_BAROMETRIC_ALTITUDE	22
#define ACTUAL_BAROMETRIC_ALTITUDE	23

class drone : public listObject
{
public:
	// ID, tx_queue;
	drone(int, linkedList * );
	~drone();

	void run();
	int getID();
	void submitMessage(message *);
	string getString();

private:
	int getState(int);
	void setState( message *);
	void saveState(int);
	void attach(message*);
	void detachClient(message*);
	void detachFrom(message*, int);
	void sendUpdate(int);

	int drone_ID;

	thread * runner;

	linkedList ** state;		// Array that keeps the current state.
	linkedList ** clients;	// Arry of clients for each state.
	linkedList * rx_queue;
	linkedList * tx_queue;
};

#endif DRONE_H_
