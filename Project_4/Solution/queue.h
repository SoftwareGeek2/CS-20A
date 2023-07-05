#ifndef QUEUE_H_
#define QUEUE_H_

#include "dllist.h"

// Queue ADT using linked list as primary data structure.
template<typename Type>
class Queue {
public:

	Queue();

	// Basic queue operations
	void enqueue(Type item);
	void dequeue();
	Type peek() const;

	// Check to see if there is anything on the queue
	bool empty() const;

	// Use to see what is in the queue for debugging
	void print() const;

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	DLList<Type> list;
};


// Queue Implementation

// Queue() Default constructor:
// Call the default constructor for its List.
// Already implemented.
template<typename Type>
Queue<Type>::Queue() :list() {}


template<typename Type>
void Queue<Type>::enqueue(Type item) {
    list.insert_rear(item); // insert item at the end of the list
}


template<typename Type>
void Queue<Type>::dequeue() {
    if (!empty()) {
        list.remove_front(); // remove item from the front of the list
    }
}


template<typename Type>
bool Queue<Type>::empty() const {
    return list.empty(); // return true if the list is empty, otherwise false
}


template<typename Type>
Type Queue<Type>::peek() const {
	assert(!list.empty()); // Ensure the list is not empty before peeking.
    return list.peek_front(); // return the item at the front of the list

}


template<typename Type>
void Queue<Type>::print() const {
    list.print(); // print the list
}

#endif //QUEUE_H_X_XMMXX 
