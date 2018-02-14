// customer.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <list>
#include "sim.h"
#include "customer.h"
#include "teller.h"
#include "event.h"
#include "eventqueue.h"

using namespace std;

extern float simulation_time, avg_service_time;
extern int total_time, total_idle_time, times_idle, total_transaction_time,
		tellers;
extern double max_time_until_service;
extern int* customers_in_line;
extern list<int> time_in_bank;
extern TellerQueue teller_queue;
extern TellerQueue* teller_queues;

/** add() creates a new Customer event with a random arrival time and returns a pointer to it
 * add() generates a random arrival time using the max simulation time from the command line input to create
 * a random time.
 * @return A pointer to the new customer event created
 *
 */
Event* Customer::add() {
	float arrival_time = simulation_time * rand() / float(RAND_MAX); // Generate random arrival time
	Event* new_event = new Customer(arrival_time);
	return new_event;
}

/**getTime() returns the arrival time of a customer object
 *
 *@return The arrival time of a customer
 */
int Customer::getTime() {
	return time;
}

/** action_single_line() performs the action for a customer in a single line simulation according to the guidelines
 *  action_single_line() does as specified in the handout instructions, the first customer in line is taken out
 *  and his time is incremented with the idle time of waiting in line. Then the global variables for data being tracked are
 *  updated accordingly, such as total_idle_time and times_idle. The customer is then readded to the queue with
 *  the updated time. Then a random transaction time is generated for the customer and it is added to his time, and
 *  again other global variables are updated, total_time and total_transaction_time get updated.
 *
 */
void Customer::action_single_line() {
	float service_time = 2 * avg_service_time * rand() / float(RAND_MAX);
	while (teller_queue.front()->getTime() < this->time) {//LOOP INVARINT if a customer's event time is less than the current
		//one run, continually do so until the line is depleted
		Event* temp_customer = new Event();
		temp_customer = (teller_queue.front()); // Set next customer as temp event and remove him from queue
		teller_queue.remove();
		temp_customer->add_time(temp_customer->getIdle()); // Add idle time to the customers time
		teller_queue.add(temp_customer); // Push it back to the priority queue

		total_idle_time += temp_customer->getIdle(); // Add idle time to total idle time
		time_in_bank.push_back(temp_customer->getIdle());
		times_idle++; // Increment number of times idle
	}
	Event* temp_event = new Event();
	temp_event = teller_queue.front();
	teller_queue.remove();

	double wait_time = temp_event->getTime() - this->time;//how long has customer been waiting
	temp_event->add_time(service_time);

	if (wait_time > max_time_until_service) {//if wait time is greater than max, update max time to this value
			max_time_until_service = wait_time;
		}
	total_time += (temp_event->getTime() - this->time);
	total_transaction_time += service_time;

	teller_queue.add(temp_event);
}

/** action_multiple_lines() runs the action for a customer when there are multiple teller queues.
 * this function effectively figures out which line is shortest and adds a customer to that corresponding line
 * if multiple lines have the same length the customer is added to a random line.
 */
void Customer::action_multiple_lines() {
	int shortest_line = 0; // Index of the shortest line
	int shortest_line_count = 0; // Number of shortest lines

	// Find the index of the smallest line
	for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every teller line
		if (customers_in_line[shortest_line] > customers_in_line[i]) { //Check to see if the current line is shorter than stored one
			shortest_line = i;
		}
	}

	// Find how many lines that are shortest
	for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: same as above
		if (customers_in_line[shortest_line] == customers_in_line[i]) {//if multiple lines have the same length of customers
			shortest_line_count++;//increment number of same length minimum lines
		}
	}

	int random_shortest_line = rand() % shortest_line_count;//randomly select what line to add a customer to

	for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: same as above
		if (customers_in_line[shortest_line] == customers_in_line[i]) {//if this line is equally as short as minimum line
			if (random_shortest_line != 0) {//if the random line isnt the first one decrement it
				random_shortest_line--;
			} else {//otherwise add a customer to that line
				customers_in_line[i]++;
				teller_queues[i].add(this);
				break;
			}
		}
	}
}
