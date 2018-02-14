// teller.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "sim.h"
#include "teller.h"
#include "event.h"
#include "eventqueue.h"

using namespace std;

extern float simulation_time;
extern float avg_service_time;
extern int total_time, total_idle_time, times_idle, total_transaction_time,
		tellers;
extern int* customers_in_line;
extern list<int> time_in_bank;
extern TellerQueue teller_queue;
extern TellerQueue* teller_queues;
extern EventQueue *event_queue;

/**
 * add() creates a new teller object
 * add() creates a new teller object with a random idle time between the min and max, which are 0 to 5 minutes
 * @return a pointer to the new teller object
 */
Event* Teller::add() {
	int idle_time = min_idle_time + rand() % max_idle_time;
	Event* new_event = new Teller(idle_time);
	return new_event;
}

/**
 * getTime() returns the time of a teller object
 * @return the time of a teller object
 */
int Teller::getTime() {
	return time;
}

/**
 * getIdle() returns the idle time of a teller object
 * @return the idle time of a teller object
 */
int Teller::getIdle() {
	return idle_time;
}

/**
 * action_single_line() adds this teller event to a teller_queue using the add function of the event queue class
 */
void Teller::action_single_line() {
	teller_queue.eq.push(this); // Add to end of teller queue
}

/**
 * action_multiple_lines() either  helps a customers or goes idle
 * adds a teller event to the event queue with idle time, or processes a transaction for a customer in the tellers line,
 * if not the teller looks to other lines to see if anyone needs help and if no one does goes idle.
 */
void Teller::action_multiple_lines() {
	if (customers_in_line[line] > 0) {
		process_transaction(line);
	} else { // No customers in the teller's line
		bool customers_in_other_lines = false;
		for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every value
			//until tellers, i = 0...tellers-1, same thing as above except for tellers
			if (customers_in_line[i] != 0) {//check if other lines have customers
				customers_in_other_lines = true;
			}
		}

		if (customers_in_other_lines == true) { // There are customers in other lines to serve
			int longest_line = 0;
			int num_of_longest_lines = 0;

			// Determine which line has maximum number of customers to take the next customer from
			for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every value
				//until tellers, i = 0...tellers-1, same thing as above except for tellers
				if (customers_in_line[longest_line] < customers_in_line[i]) {
					longest_line = i;
				}
			}

			for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every value
				//until tellers, i = 0...tellers-1, same thing as above except for tellers
				if (customers_in_line[longest_line] == customers_in_line[i]) {
					num_of_longest_lines++;
				}
			}

			int random_line = rand() % num_of_longest_lines; // Choose a random line for the customer to go to

			for (int i = 0; i < tellers; i++) { // LOOP INVARIANT: i < customers, means i will loop through every value
				//until customers, i = 0...customers-1, used to create all the customers
				if (customers_in_line[longest_line] == customers_in_line[i]) {//if the line has same number as smallest line
					if (random_line != 0) {
						random_line--;
					} else {//other lines arent as long
						process_transaction(i); // Process transaction at that line
						break;
					}
				}
			}
		} else { // No customers in other lines to serve
			float idle_time_back_in_queue = min_idle_time_back_in_queue + rand() % max_idle_time_back_in_queue;
			this->add_time(idle_time_back_in_queue); // Teller goes idle
			total_idle_time += idle_time_back_in_queue; // Increment idle time counter by time idle
			time_in_bank.push_back(idle_time_back_in_queue);
			times_idle++; // Increment idle counter

			if (this->getTime() <= simulation_time) { // Don't add to event_queue if it would happen past sim time
				event_queue->add(this);
			}
		}
	}

}

/**
 * add_time() adds the transaction_time to the time of the teller
 * @param transaction_time the time to be added to the teller's total time
 */
void Teller::add_time(int transaction_time) { // Add transaction time to total time of teller
	this->time += transaction_time;
}

/**
 * process_transaction() processes a transaction for a specific line passed by input
 * process_transaction removes the first event from a teller queue, and generates a random service time, adds it
 * to the customers time and updates globals and readds the teller to the event queue. The customer is not readded
 * as he is done in the bank.
 *
 */
void Teller::process_transaction(int line_number) {
	Event* temp_event = teller_queues[line_number].front(); // Get next event as a temp event before removing it
	teller_queues[line_number].remove(); // Remove event from queue
	customers_in_line[line_number]--; // Decrease number of customers in line by 1

	float service_time = 2 * avg_service_time * rand() / float(RAND_MAX); // Random service times
	add_time(service_time);

	total_time += getTime() - temp_event->getTime();
	total_transaction_time += service_time;

	event_queue->add(this);
}
