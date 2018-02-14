// sim.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <cmath>
#include "sim.h"
#include "event.h"
#include "customer.h"
#include "teller.h"
#include "eventqueue.h"

using namespace std;

const int sec_in_min = 60; // Conversion factor
const int min_idle_time = 1; // Units in seconds
const int max_idle_time = 600; // Units in seconds
const int min_idle_time_back_in_queue = 1; // Units in seconds
const int max_idle_time_back_in_queue = 150; // Units in seconds

int customers, tellers;//user input global for customers and tellers
int total_time, total_idle_time, times_idle, total_transaction_time;//global variables to track for the data
double standard_deviation, max_time_until_service;;//another global
int* customers_in_line;//number of customers in line
list<int> time_in_bank;//a  list of integer used to find average time in bank
float simulation_time, avg_service_time;//user input passed from command line
unsigned int seed;//the seed if passed in otherwise defaulted to random value

Teller t;//intialize example teller t
Customer c;//initalize example teller c
Event* generic_teller = &t;//^
Event* generic_customer = &c;//^
Event** all_tellers;//pointer to pointers of all the tellers
Event** all_customers;//pointer to pointer of all the customers
TellerQueue teller_queue;//The tellerQueue
TellerQueue* teller_queues;//pointer to multiple teller queues
EventQueue *event_queue;//pointer to the main event queue

//main runs the whole thing
int main(int argc, char *argv[]) {
	customers = atoi(argv[1]);//set from user input
	tellers = atoi(argv[2]);//set from user input
	simulation_time = sec_in_min * atoi(argv[3]); // Input units in min
	avg_service_time = sec_in_min * atoi(argv[4]);//set from user input
	if (argc == 6) { // If seed is provided
		seed = atof(argv[5]);
	} else { // If no seed is provided
		seed = time(NULL);
	}
	srand(seed);//set seed

	printf("Simulation started with following parameters:\n");
	printf("Simulation time: %d minutes\n", int(simulation_time) / sec_in_min);
	printf("Average service time: %.2f minutes\n",
			avg_service_time / sec_in_min);
	printf("Idle time between %d - %d seconds\n", min_idle_time, max_idle_time);
	printf("Number of Customers: %d\n", customers);
	printf("Number of Tellers: %d\n", tellers);
	cout << endl << endl;

	cout << "Simulation for one line" << endl;
	cout << "-----------------------" << endl;

	sim_single_line();//run single line simulation
	print(); // Print results for single line sim

	// Reset parameters which are being tracked
	total_time = total_idle_time = times_idle = total_transaction_time =
			standard_deviation = 0;

	cout << endl << endl;
	cout << "Simulation for multiple lines" << endl;
	cout << "-----------------------------" << endl;

	sim_multiple_lines();//run multiple line simulation
	print(); // Print results for multiple lines sim

	return 0;
} // int main(int argc, char *argv[]);

/**
 * sim_single_line runs the simulation for a single teller line
 * The simulation is ran by generating all the customers, tellers and the eventqueue and then
 * running everything according to the actions each object have.
 */
void sim_single_line() {
	event_queue = new EventQueue();

	all_customers = new Event*[customers];
	all_tellers = new Event*[tellers];

	for (int i = 0; i < customers; i++) { // LOOP INVARIANT: i < customers, means i will loop through every value
		//until customers, i = 0...customers-1, used to create all the customers
		all_customers[i] = generic_customer->add();
		event_queue->add(all_customers[i]); // Insert element at the end of queue
	}

	for (int i = 0; i < tellers; i++) { // Generate and initiate tellers
		all_tellers[i] = generic_teller->add();
		event_queue->add(all_tellers[i]);
	}

	while (!event_queue->eq.empty()) { // Process the event queue until it is empty
		event_queue->getNext();
	}

	// Free memory
	for (int i = 0; i < customers; i++) {// LOOP INVARIANT: i < customers, means i will loop through every value
		//until customers, i = 0...customers-1, used to create all the customers
		delete (all_customers[i]);
	}
	delete (all_customers);
	for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every value
		//until tellers, i = 0...tellers-1, same thing as above except for tellers
		delete (all_tellers[i]);
	}
	delete (all_tellers);

	delete (event_queue);
} // void sim_single_line();

/**
 * sim_multiple_lines is similar to sim_single_line except it generates all the customers and teller events
 * and behaves as if there were multiple teller lines, one for each teller. The respective actions called are the ones
 * for multiple lines
 */
void sim_multiple_lines() {
	teller_queues = new TellerQueue[tellers];
	event_queue = new EventQueue();

	all_customers = new Event*[customers];
	all_tellers = new Event*[tellers];

	for (int i = 0; i < customers; i++) { // LOOP INVARIANT: i < customers, means i will loop through every value
		//until customers, i = 0...customers-1, used to create all the customers
		all_customers[i] = generic_customer->add();
		event_queue->add(all_customers[i]); // Insert element at the end of queue
	}

	for (int i = 0; i < tellers; i++) {  //LOOP INVARIANT: i < tellers, means i will loop through every value
		//until tellers, i = 0...tellers-1, same thing as above except for tellers
		all_tellers[i] = generic_teller->add();
		all_tellers[i]->line = i;
		event_queue->add(all_tellers[i]); // Insert element at the end of queue
	}

	customers_in_line = new int[tellers];
	for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every value
		//until tellers, i = 0...tellers-1, same thing as above except for tellers
		customers_in_line[i] = 0;
	}

	while (!event_queue->eq.empty()) { //LOOP INVARIANT: while there are still things in the queue it runs, and removes
		//the first element every time
		event_queue->getNextMultipleLines();
	}

	// Free memory
	for (int i = 0; i < customers; i++) {// LOOP INVARIANT: i < customers, means i will loop through every value
		//until customers, i = 0...customers-1, used to create all the customers
		delete (all_customers[i]);
	}
	delete (all_customers);

	for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every value
		//until tellers, i = 0...tellers-1, same thing as above except for tellers
		delete (all_tellers[i]);
	}

	delete (all_tellers);
} // void sim_multiple_lines();

/**
 * findStDev() calculates the standard deviation of the customers wait time, by using a list of all their wait times
 * and looping through while calculation. It updates the global deviation variable.
 */
void findStDev() {
	double avg_time = total_time / customers;
	double total_deviation = 0;

	while (!time_in_bank.empty()) { // Loop from back of time_in_bank to front, until empty
		total_deviation += abs(time_in_bank.back() - avg_time); // Add the individual deviation of last element of time_in_bank to total_deviation
		time_in_bank.pop_back(); // Remove last element
	}
	// time_in_bank should be empty after this, so that it can be used properly for next sim

	standard_deviation = total_deviation / customers;
} // void findStDev();

/**
 * print() prints out all the data being tracked over the course of the simulation
 */
void print() {
	findStDev();
	double avg_transaction_time = double(total_transaction_time)
			/ double(customers);
	printf("Average transaction time: %.2f minutes\n",
			avg_transaction_time / double(sec_in_min));
	printf("Total time: %d minutes\n", total_time / sec_in_min);
	printf("Total idle time: %d minutes\n", total_idle_time / sec_in_min);
	printf("Times idle: %d\n", times_idle);
	printf("Maximum time taken to get serviced: %.2f minutes\n",
			max_time_until_service / sec_in_min);
	printf("Average time spent in bank: %.2f minutes\n",
			(double(total_time) / double(customers)) / double(sec_in_min));
	printf(
			"Standard deviation of time spent at bank: %d seconds (%.2f minutes)\n",
			int(standard_deviation), standard_deviation / double(sec_in_min));
} // void print();
