// teller.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef TELLER_H_
#define TELLER_H_

#include "event.h"
#include "eventqueue.h"

/**
 * \class Teller
 *
 * \brief Teller is the derived class of Event that carries additional info such as idle_time for each specific teller
 */
class Teller: public Event {
public:
	int idle_time;
	int time;
	Teller() {//empty constructor never used
	}
	Teller(int idle_t) {//used to initialize with specific idle time
		time = 0;
		idle_time = idle_t;
	}

	Event* add();
	int getTime();
	int getIdle();
	void action_single_line();
	void action_multiple_lines();
	void add_time(int transaction_time);
	void process_transaction(int line_number);
	virtual ~Teller() {
	}
private:
};

/**
 * \class TellerQueue
 *
 * \brief TellerQueue is a derived class from EventQueue that does nothing extra, it only holds Customer objects though
 */
class TellerQueue: public EventQueue {
public:
	TellerQueue() {
	}
private:
};

#endif /* TELLER_H_ */
