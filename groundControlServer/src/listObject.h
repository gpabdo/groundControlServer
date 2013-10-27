/*
 * listObject.h
 *
 *  Created on: Sep 14, 2013
 *      Author: Greg
 */

#ifndef LISTOBJECT_H_
#define LISTOBJECT_H_

#include <string>
using namespace std;

class listObject
{
public:
	virtual ~listObject();
	virtual string getString() = 0;
private:

};

#endif
