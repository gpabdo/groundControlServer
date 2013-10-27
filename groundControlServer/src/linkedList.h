/*
 * linkedList.h
 *
 *  Created on: Sep 12, 2013
 *      Author: Greg
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "listObject.h"
#include <string>
#include <iostream>
using namespace std;

class linkedList
{
public:
	linkedList();
	~linkedList();
	void pushToFront(listObject*);	// Adds to the front.
	void pushToBack(listObject*);	// Adds to the end.
	void pushAt(int, listObject*);	// Adds to passed in location.
	listObject* popFront();			// Removes front and returns it.
	listObject* popBack();			// Removes back and returns it.
	listObject* popAt(int);			// Removes from location and returns it.
	listObject* peekFront();		// Returns pointer to front
	listObject* peekBack();			// Returns pointer to back.
	listObject* peekAt(int);	  	// Return object at passed in value of list.
	int getLength();				// Number of nodes.
	bool isEmpty();					// Returns true if empty.
	void clear();					// Clear all nodes.
	void print();					// Print out the entire list.

private:
    int length;

    struct queueNode                // Node object for the queue.
	{
		listObject* data;  			// Pointer to the StructureItem object.
		queueNode * next;           // Next node in the queue.

		queueNode(listObject* obj)
		{
			data = obj;
			next = NULL;
		}

		~queueNode()
		{}
	};

    queueNode* front;              	// Root of the queue.
    queueNode* back;				// End of the queue/

    void place(int, queueNode*);	// Place somewhere in the queue.
    queueNode* find(int);			// Find a node in the queue.
    listObject * remove(int);		// Remove the node at passed in location.
};

#endif
