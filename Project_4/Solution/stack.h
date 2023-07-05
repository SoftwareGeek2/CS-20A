#ifndef STACK_H_
#define STACK_H_

#include"dllist.h"

// Stack ADT using linked list as primary data structure.
template<typename Type>
class Stack {
public:

    Stack();

    // Basic stack operations
    void	push(Type item);
    void	pop();
    Type	peek() const; 

    // Check to see if there is anything on the stack
    bool	empty() const;

    // Use to see what is in the stack for debugging
    void	print() const;

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif

    DLList<Type> list;
};

// Stack Implementation

template<typename Type>
Stack<Type>::Stack():list() {}

template<typename Type>
void Stack<Type>::push(Type item) {
    list.insert_front(item); // Insert item at the front of the list.
}

template<typename Type>
void Stack<Type>::pop() {
    if (!list.empty()) {
        list.remove_front(); // Remove item from the front of the list.
    }
}

template<typename Type>
bool Stack<Type>::empty() const {
    return list.empty(); // Return true if the list is empty, false otherwise.
}

template<typename Type>
Type Stack<Type>::peek() const {
    assert(!list.empty()); // Ensure the list is not empty before peeking.
    return list.peek_front(); // Return the value at the front of the list.
}

template<typename Type>
void Stack<Type>::print() const {
    list.print(); // Print the list.
}

#endif//STACK_H__X_XMMXX
