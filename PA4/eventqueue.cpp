// eventqueue.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "eventqueue.h"
#include "event.h"

/**
 * getNext() removes the first event in the queue and runs the action for it
 * getNext() takes off the first event and runs the corresponding event, either customer or teller,
 * this function is used for a one line simulation
 */
void EventQueue::getNext() { // Remove event and execute action even which is appropriate for that event
	Event* temp_event = eq.top();
	eq.pop();
	temp_event->action_single_line();
}

/**
 * getNextMultipleLines() takes the first event off the queue and runs the action for it, for multiple lines
 * does the same as getNext() function, but used for multiple line simulation instead
 */
void EventQueue::getNextMultipleLines() { // Remove event and execute action even which is appropriate for that event
	Event* temp_event = eq.top();
	eq.pop();
	temp_event->action_multiple_lines();
}

/**
 * front() returns a pointer to the first element in the queue
 * @return a pointer to the first Event in the queue
 */
Event* EventQueue::front() {
	return eq.top(); // get first element
}

/**
 * remove() removes the first element from the queue
 */
void EventQueue::remove() {
	eq.pop(); // remove first element
}

/**
 * add() takes a pointer to an event and adds it to the queue
 */
void EventQueue::add(Event *event) {
	eq.push(event); // add element to end of queue
}

