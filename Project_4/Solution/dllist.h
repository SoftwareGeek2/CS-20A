#ifndef S23_CS20A_LlST_H
#define S23_CS20A_LlST_H

#include<iostream>
#include<assert.h>
// Linked DLList object that maintains both front and rear pointers
// and the size of the list.  Note that you have to keep the front,
// rear and size consistent with the intended state of the DLList 
// otherwise very bad things happen. 
template<typename Type>
class DLList {
public:

	DLList();

	DLList(const DLList<Type>& other);

	DLList<Type>& operator=(const DLList<Type>& other);

	~DLList();

	void	print() const;
	bool	empty() const;

	void	insert_front(const Type &value);
	void	insert_rear(const Type &value);
	void	insert(int idx, const Type &value);

	// Note that the user must front ensure the list is not empty
	// prior to calling these functions. 
	Type	peek_front() const;
	Type	peek_rear() const;
	Type	peek(int idx) const;

	int		count() const;
	int		count_value(const Type &value) const;

	int		find(const Type &value) const;

	bool	remove_front();
	bool	remove_rear();
	bool	remove_index(int idx);
	int		remove_value(const Type &value);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our DLList.
	// Will be implemented along with list
	// member functions
	class DLNode;

	// We'll have both front and rear points for 
	// Fast insertion/deletion from both ends.
	DLNode*	front;
	DLNode*	rear;

	// Keep track of number of nodes in the list
	int		size;
};


/* DLList Implementation
//
//  Since DLList is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* DLNode definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Type>
class DLList<Type>::DLNode {
public:
	DLNode() :nxt(nullptr), prv(nullptr) {}
	DLNode(Type v, DLNode* p, DLNode* n) : val(v), nxt(n), prv(p) {}

	DLNode * next() const { return nxt; }
	void next(DLNode *n) { nxt = n; }

	DLNode * prev() const { return prv; }
	void prev(DLNode *p) { prv = p; }

	Type value() const { return val; }
	void value(const Type &v) { val = v; }

private:
	Type  val;
	DLNode * nxt;
	DLNode * prv;
};



/* DLList default constructor
//		Set front and rear pointer to point to nothing, size is zero
//		Already implemented, nothing to do.
*/
template<typename Type>
DLList<Type>::DLList() :front(nullptr), rear(nullptr), size(0) {
	/*    COMPLETE    */
}


/* Copy constructor
*/
template<typename Type>
DLList<Type>::DLList(const DLList<Type>& other) : front(nullptr), rear(nullptr), size(0) {
    DLNode* current = other.front;
    while (current) {//Loop until nullptr (if(nullptr) return false)
        insert_rear(current->value());
        current = current->next();//Insert values and loop
    }
}

/* Overloaded assignment operator
*/
template<typename Type>
DLList<Type>& DLList<Type>::operator=(const DLList<Type>& other) {
    if (this == &other) {
        return *this;
    }//Self-Assingment check

    // Clean up the current list
    while (size > 0) {
        remove_front();
    }

    // Copy other list
    DLNode* current = other.front;
    while (current) {
        insert_rear(current->value());
        current = current->next();
    }

    return *this;
}



/* DLList destructor
*/
template<typename Type>
DLList<Type>::~DLList() {
    while (size > 0) {
        remove_front();//Remove_front is a member function, remove_front() is called on this
    }
}

/* DLList print
*/
template<typename Type>
void DLList<Type>::print() const {
    DLNode* current = front;
    while (current) {
        std::cout << current->value();
        if (current->next()) {//Since if(nullptr) returns false
            std::cout << " ";//Add space, no newline
        }
        current = current->next();
    }
}


/* DLList empty
*/
template<typename Type>
bool DLList<Type>::empty() const {
    return size == 0;//this.size
}

/* DLList insert_front
*/
template<typename Type>
void DLList<Type>::insert_front(const Type &value) {
    DLNode* newNode = new DLNode(value, nullptr, front);//Initialize with prev = nullptr, nxt = front
    if (empty()) {
        front = rear = newNode;//Single element DLL
    } else {
        front->prev(newNode);//newNode is assigned to prev of the front
        front = newNode;
    }
    size++;
}

/* DLList insert_rear
*/
template<typename Type>
void DLList<Type>::insert_rear(const Type &value) {
    DLNode* newNode = new DLNode(value, rear, nullptr);//Initialization : prev = rear, nxt = nullptr
    if (empty()) {
        front = rear = newNode;
    } else {
        rear->next(newNode);//Assign current rear's next
        rear = newNode;//Reassign rear
    }
    size++;
}


/* DLList insert */
template<typename Type>
void DLList<Type>::insert(int idx, const Type &value) {
    if (idx <= 0) {
        insert_front(value);
    } else if (idx >= size) {//Adapted from spec, and notes for single LL
        insert_rear(value);
    } else {
        DLNode* iterateNode = front;
        for (int i = 0; i < idx - 1; i++) {
            iterateNode = iterateNode->next();//Reach point of insertion
        }
        DLNode* newNode = new DLNode(value, iterateNode, iterateNode->next());
        iterateNode->next()->prev(newNode);//Adjust prev of next node
        iterateNode->next(newNode);//Adjust next of current node
        size++;
    }
}

/*  DLList peek_front */
template<typename Type>
Type DLList<Type>::peek_front() const {
    assert(front != nullptr);//Force check safe value
    return front->value();
}

/* DLList peek_rear */
template<typename Type>
Type DLList<Type>::peek_rear() const {
    assert(rear != nullptr);//Force check safe value
    return rear->value();
}


/* DLList peek */
template<typename Type>
Type DLList<Type>::peek(int idx) const {
    assert(idx >= 0 && idx < size);//Force check safe value
    DLNode* iterateNode = front;
    for (int i = 0; i < idx; i++) {
        iterateNode = iterateNode->next();
    }
    return iterateNode->value();
}

/* DLList count */
template<typename Type>
int DLList<Type>::count() const {
    return size;//Return private variable
}

/* DLList count_value */
template<typename Type>
int DLList<Type>::count_value(const Type &value) const {
    int count = 0;
    DLNode* iterateNode = front;
    while (iterateNode != nullptr) {
        if (iterateNode->value() == value) {
            count++;
        }//Iterate through list, use counter variable
        iterateNode = iterateNode->next();
    }
    return count;
}
/* DLList find*/
template<typename Type>
int DLList<Type>::find(const Type &value) const {
    int index = 0;
    DLNode* iterateNode = front;
    while (iterateNode != nullptr) {
        if (iterateNode->value() == value) {
            return index;
        }//Iterate through and obtain index
        iterateNode = iterateNode->next();
        index++;
    }
    return -1;
}

/* DLList remove_front */
template<typename Type>
bool DLList<Type>::remove_front() {
    if (empty()) {
        return false;
    }
    DLNode* temp = front;//Make use of temporary variable to avoid losing access to member variables
    if (front == rear) {
        front = rear = nullptr;
    } else {
        front = front->next();
        front->prev(nullptr);//Reset front's pointer member variables
    }
    delete temp;//Now we can delete temp
    size--;
    return true;
}

/* DLList remove_rear */
template<typename Type>
bool DLList<Type>::remove_rear() {
    if (empty()) {
        return false;
    }
    DLNode* temp = rear;
    if (front == rear) {
        front = rear = nullptr;
    } else {
        rear = rear->prev();
        rear->next(nullptr);//Reset rear
    }
    delete temp;//Delete temp
    size--;
    return true;
}


/* DLList remove_index */
template<typename Type>
bool DLList<Type>::remove_index(int idx) {
    if (idx < 0 || idx >= size) {
        return false;
    }
    if (idx == 0) {
        return remove_front();
    }
    if (idx == size - 1) {
        return remove_rear();
    }//Reuse
    
    DLNode* iterateNode = front;
    for (int i = 0; i < idx; i++) {
        iterateNode = iterateNode->next();
    }//Iterate to reach point of removal
    
    iterateNode->prev()->next(iterateNode->next());
    iterateNode->next()->prev(iterateNode->prev());//Reset pointers
    delete iterateNode;
    size--;
    return true;
}

/* DLList remove_value */
template<typename Type>
int DLList<Type>::remove_value(const Type &value) {
    int index = find(value);
    if (index == -1) {
        return -1;
    }
    remove_index(index);//Obtain location and remove
    return index;
}


#endif