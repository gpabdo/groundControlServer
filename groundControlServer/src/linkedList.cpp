/*
 * linkedList.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: Greg
 */

#include "linkedList.h"

/******************************************************************
* Construtor initializes a new list.
******************************************************************/
linkedList::linkedList()
{
    front = NULL;   // Set front to NULL.
    back = NULL;	// Set back to NULL.
    length = 0;		// Set length to 0.
}

/******************************* distructor **********************************
* Clears the entire list, deleteing all nodes. Data is not deleted from the
* nodes.
*****************************************************************************/
linkedList::~linkedList()
{
    clear();        // Clear the entire queue.
}

/******************************************************************
* Search the list for the desired node and if found, return a
* pointer to that node. If value is larger then the list, return
* the last node.
******************************************************************/
linkedList::queueNode * linkedList::find(int value)
{
	if( value > getLength() )
		return NULL;

	queueNode* temp = front;
	for( int i = 0; i < value; i++)
		temp = temp->next;

	return temp;
}

/******************************************************************
* Place a node in the list at a desired location as long as the
* passed in value is less then the length of the list. If larger,
* node will be placed at the end.
******************************************************************/
void linkedList::place(int value, queueNode * node)
{
	if( value > getLength())
		return;

    if( isEmpty() )
    {
        front = node;        // Set front to the new node.
        back = node;
    }
    else
    {
    	queueNode * temp = find(value -1);
    	node->next = temp->next;
    	temp->next = node;
    }

	if(value == getLength())
		back = node;

    length++;
}


/******************************************************************
* Remove a node from the list and return its data.
******************************************************************/
listObject * linkedList::remove(int value)
{
	if(isEmpty())
		return NULL;

	queueNode * temp;
	listObject * data;

	if(value == 0)
	{
		temp = front;
		front = front->next;
	}
	else
	{
		queueNode * prev = find(value - 1);
		temp = prev->next;
		prev->next = temp->next;
	}

	if( value == getLength() -1)
		back = temp;

	data = temp->data;		// Save a pointer to the data.
	delete temp;			// Delete the node.
	length--;				// Remove 1 from the length.
	return data;			// Return the data.
}


/******************************************************************
* Add a node to the front of the list.
******************************************************************/
void linkedList::pushToFront( listObject* item )
{
    // Were we passed an invalid object somehow?
    if( item == NULL )  // Check for NULL
        return;         // If so, return.

    place(0, new queueNode(item));
}

/******************************************************************
* Add a node to the back of the list.
******************************************************************/
void linkedList::pushToBack( listObject* item )
{
    // Were we passed an invalid object somehow?
    if( item == NULL )  // Check for NULL
        return;         // If so, return.

    place(getLength() -1, new queueNode(item));
}

/******************************************************************
* Push a node to a location.
******************************************************************/
void linkedList::pushAt(int value, listObject * data)
{
	place(value, new queueNode(data));
}

/******************************************************************
* Pop a node from the front of the list.
******************************************************************/
listObject * linkedList::popFront()
{
    // Is the list already empty?
    if( isEmpty() )     // Check for an empty list.
        return NULL;			// List is empty, don't need to do anything.

    return remove(0);               // return the stuctureItem.
}

/******************************************************************
* Pop a node from the back of the list.
******************************************************************/
listObject * linkedList::popBack()
{
    // Is the list already empty?
    if( isEmpty() )     // Check for an empty list.
        return NULL;    // List is empty, don't need to do anything.

    return remove(getLength() -1);     // return the stuctureItem.
}

/******************************************************************
* Look at the node in the front of the list.
******************************************************************/
listObject * linkedList::peekFront()
{
    if( front != NULL )
        return find(0)->data;

    return NULL;
}

/******************************************************************
* Look at the node in the back of the list.
******************************************************************/
listObject * linkedList::peekBack()
{
    if( front == NULL )
        return find(getLength() -1)->data;

    return NULL;
}

/******************************************************************
*
******************************************************************/
listObject * linkedList::peekAt(int value)
{
	return find(value)->data;
}

/******************************************************************
*
******************************************************************/
listObject * linkedList::popAt(int value)
{
	return remove(value);
}

/******************************************************************
*
******************************************************************/
int linkedList::getLength()
{
	return length;
}

/******************************************************************
*
******************************************************************/
bool linkedList::isEmpty()
{
	// Is the queue empty?
	if( front == NULL ) // Check the front pointer.
		return true;    // Queue is empty, return true.

	return false;       // There is at least one item, not empty.
}

/******************************************************************
*
******************************************************************/
void linkedList::clear()
{
    // Is the list already empty?
    if( isEmpty() )     // Check for an empty list.
        return;         // List is empty, don't need to do anything.

    queueNode * current = front;    // Create node to help step through list.
    queueNode * placeHold = front;  // Create node to keep place of delete.

    // As long as were not at the end, keep stepping to the next node.elete front;
    while( current != NULL)
    {
        placeHold = current->next;  // Hold where we have to go.
        delete current;             // Delete the node.
        current = placeHold;        // Set current to the next node.
    }

    front = NULL;   // Reset the front to NULL;
    back = NULL;
    length = 0;
}

/******************************************************************
*
******************************************************************/
void linkedList::print()
{
	for( int i = 0; i < getLength(); i++ )
		cout << find(i)->data->getString() << endl;
}
