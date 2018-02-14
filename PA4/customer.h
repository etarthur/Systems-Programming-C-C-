// customer.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "event.h"

/**
 * \class Customer
 *
 * \brief Customer is a derived Event class that contains information on how long a customer was in the bank for
 */
class Customer: public Event {
public:
	int time;
	Customer() {//empty Constructor is never used
	}
	Customer(int t) {//Constructor that is used to initialize time
		time = t;
	}
	Event* add();
	int getTime();
	void action_single_line();
	void action_multiple_lines();
	virtual ~Customer() {
	}
private:
};

#endif /* CUSTOMER_H_ */
