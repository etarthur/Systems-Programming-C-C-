// eventqueue.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include "event.h"

//struct necessary to compare elements since they are created objects
struct CompareEvents {
	bool operator()(Event *a, Event *b) {
		return (a->getTime() > b->getTime());//return true if a is greater than b
	}
};

/**
 * \class EventQueue
 *
 * \brief EventQueue is a priorty_queue of events, is the global overhead for the entire project
 */
class EventQueue {
public:
	//priority queue implementation
	std::priority_queue<Event *, std::vector<Event *>, CompareEvents> eq;
	EventQueue() {
	}
	void getNext();
	void getNextMultipleLines();
	Event* front();
	void remove();
	void add(Event *a);
};

#endif /* EVENTQUEUE_H_ */
