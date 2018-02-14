How To Run:
To run the simulation first compile by using the make command
Then to run from the command line type:
	./qSim #customers #tellers simulationTime averageServiceTime <seed>
seed is optional, and it is the random number seed if you wish to repeat trials with same random numbers to test/debug.

The output will be printed to the console, as this wasn't specified in the assignment, there is a folder called output that is filled with pictures of successful
runs to check out. The hardest part of this assigment was starting it, on first read we had no idea what to do. After reading it a few times and trying and failing
a few times we started to understand. Next time this assignment is used I believe it should be rewritten to include smaller details or include an example students can view
because at first it's very hard to understand what's supposed to happen.

Conclusion:
According to our data, which we hope and believe is correct, multiple teller lines is faster on average than a single teller line. The trials can be viewed in the output folder
also contained in the zip. When there are only a few customers to a bunch of tellers they both perform around the same, this makes sense as the improved availability of multiple
teller lines won't matter if no one is in the bank. When there are a lot of customers the multiple lines seems to be faster, not in a huge way, but it also reduces the maximum
time someone is in the bank. Overall it seems if there are more than a small amount of customers, multiple teller lines seems to pull ahead in almost every category, but at 
the same time the tellers are idle longer.

Loop Invariants:
In customer.cpp:
3x in the multiple lines function: for (int i = 0; i < tellers; i++) {//LOOP INVARIANT: i < tellers, means i will loop through every teller line, from 0 ... tellers.
while (teller_queue.front()->getTime() < this->time) {//LOOP INVARINT if a customer's event time is less than the current one run, continually do so until the line is depleted
In teller.cpp:
4x in multiple lines function: ^ same exact loop as above with same invariant
In LinkedList.cpp:
2x in the sort function: for(temp1 = first; temp!=NULL;temp1->next){//LOOP INVARIANT: temp!=NULL, means temp will loop through all elements in the list until it reaches
the last one, which is NULL. temp1 takes values from first....last
In sim.cpp:
2x in sim single line, 2x in multiple lines, 2x in findStDev:for (int i = 0; i < customers; i++) { // LOOP INVARIANT: i < customers, means i will loop through every value 
until customers, i = 0...customers-1, used to create all the customers
2x in sim single line, 3x in multiple lines:for(int i = 0; i < customers; i++){//LOOP INVARIANT: i < tellers, means i will loop through every value 
until tellers, i = 0...tellers-1, same thing as above except for tellers
2x in sim methods: while (!event_queue->eq.empty()) { //LOOP INVARIANT: while there are still things in the queue it runs, and removes every time, looping through the whole queue


Classes:
Event: An abstract class that is used to derive the classes Customer and Teller. This class represents an event which is either a customer getting in line, reaching the 
head of a line, and a teller who is either going to go idle because there are no customers in line or attend to a customer. The only field for an eveny is lineNumber, which
is the time at which this event will enter the global event queue. All the methods are virtual and defined in the header with null definitions, and then defined
in the derived classes.

Customer::Event: The customer class is used to represent a customer Event, which is either a customer entering the bank or a customer reaching the head of a line. Although
a customer object can also be used when the customer is second in line, and another teller has no one in line, they may call them over. The class has a field time,
which holds the total amount of time a customer was in the bank for. Customer methods are the implementations of the abstract methods from Event, they modify the customer's time
and add/remove them from a teller queue or the global event queue.

Teller::Event: The Teller class is used to represent an Event which is either a teller helping a customer or a teller doing idle work while waiting for customers. The Teller
implements the methods from Event, and works very similar to customer. However when a teller Event is encountered, they either help a customer, and get readded to the event
queue with increased time for transaction or they go idle as there are no customers to help in any line, and get readded to the event queue with increased time for idle
jobs. 

EventQueue: The EventQueue class is the main driving force of the simulation. The eventqueue is a queue that is either implemented by a LinkedList class(that we made) or 
a priority_queue for extra credit. The EventQueue holds all the events that will happen in the bank over the entire time. They all get added at the start,
and are in increasing order, so the smalles time comes first. The eventQueue then gets triggered as the time of the simulation increases and new events in the queue 
get activated. The only field in an EventQueue is either a priority_queue or a linkedList version, the LinkedList class description can be found below.

TellerQueue::EventQueue: The TellerQueue derived class is similar to the EventQueue in that it holds events, but the tellerqueue holds customers, that represents customers
waiting in line for a specific teller at a bank. The tellerqueue is used to update customers times for the global event queue. 

LinkedList: The linkedList class contains a struct element which is one block of the linkedlist chain. The LinkedList class contains a pointer to the first and last element
and is used to implement the priorty_queue. The add() function will sort the linkedList dynamically and it behaves similar to a prioirty_queue. Note that the sort() takes
some time as it is linear, traversing the linkedList was already hard enough, that trying to optimize it would be even harder.


