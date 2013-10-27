/*
 * message.h
 *
 *  Created on: Oct 15, 2013
 *      Author: greg
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "listObject.h"
#include <string>
using namespace std;

class message : public listObject
{
public:
	// source, command, value, dest
	message(int, int, int, int);
	message(int, int, int, int, string);
	~message();

	int getSource();
	int getDest();
	int getCommand();
	int getValue();
	char * getData();
	int getDataLength();

	void setData(string);

	string getString();

private:
	int source;
	int dest;
	int command;
	int value;
	char * data;
	int data_length;
};


#endif /* MESSAGE_H_ */
