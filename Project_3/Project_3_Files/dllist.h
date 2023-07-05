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
DLList<Type>::DLList(const DLList<Type>& other) {

	/*    TODO    */

}
/* Overloaded assignment operator
*/
template<typename Type>
DLList<Type>& DLList<Type>::operator=(const DLList<Type>& other) {

	/*    TODO    */

	return *this;
}


/* DLList destructor
*/
template<typename Type>
DLList<Type>::~DLList() {

	/*    TODO    */

}

/* DLList print
*/
template<typename Type>
void DLList<Type>::print() const {

	/*    TODO    */

}

/* DLList empty
*/
template<typename Type>
bool DLList<Type>::empty() const {

	/*    TODO    */

	bool retval = false;
	return retval;
	
}


/* DLList insert_front
*/
template<typename Type>
void DLList<Type>::insert_front(const Type &value) {

	/*    TODO    */

}

/* DLList insert_rear
*/
template<typename Type>
void DLList<Type>::insert_rear(const Type &value) {

	/*    TODO    */

}

/* DLList insert
*/
template<typename Type>
void DLList<Type>::insert(int idx, const Type &value) {

	/*    TODO    */

}

/*  DLList peek_front
*/
template<typename Type>
Type DLList<Type>::peek_front() const {
	// Force check that the front is pointing to a DLNode
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(front != nullptr);

	/*    TODO    */

	Type retval{};
	return retval;

}

/* DLList peek_rear
*/
template<typename Type>
Type DLList<Type>::peek_rear() const {

	// Force check that the rear is pointing to a DLNode
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(rear != nullptr);

	/*    TODO    */

	Type retval{};
	return retval;

}

/* DLList peek
*/
template<typename Type>
Type DLList<Type>::peek(int idx) const {

	// Force index to be correct before getting the Type
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(idx >= 0 && idx < size);

	/*    TODO    */

	Type retval{};
	return retval;;
}

/* DLList count
*/
template<typename Type>
int DLList<Type>::count() const {

	/*    TODO    */

	int retval = 9000000;
	return retval;

}

/* DLList count_value
*/
template<typename Type>
int DLList<Type>::count_value(const Type &value) const {
	/*    TODO    */

	int retval = 9000000;
	return retval;

}
/* DLList find
*/
template<typename Type>
int DLList<Type>::find(const Type &value) const {

	/*    TODO    */

	int retval = 8675309;
	return retval;

}

/* DLList remove_front
*/
template<typename Type>
bool DLList<Type>::remove_front() {

	/*    TODO    */

	bool retval = false;
	return retval;

}
/* DLList remove_rear
*/
template<typename Type>
bool DLList<Type>::remove_rear() {

	/*    TODO    */

	bool retval = false;
	return retval;
}

/* DLList remove_index
*/
template<typename Type>
bool DLList<Type>::remove_index(int idx) {

	/*    TODO    */

	bool retval = false;
	return retval;

}

/* DLList remove_index on value
*/
template<typename Type>
int DLList<Type>::remove_value(const Type &value) {

	/*    TODO    */

	int retval = 42;
	return retval;

}

#endif







































































































// _X_XMXMXI