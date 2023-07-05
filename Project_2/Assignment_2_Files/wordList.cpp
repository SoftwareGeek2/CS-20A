/* Wordlist source file
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias words in any way that would result
*	in undefined behavior. 
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++
#define _CRT_SECURE_NO_DEPRECATE
#else  // not Microsoft Visual C++, so assume UNIX interface
#endif
#define WORDLIST_H


// Do not include any other libraries
#include"wordlist.h"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

// Function: Wordlist Constructor
Wordlist::Wordlist(const int max):stored(0),capacity(max) {

	if(max<1)
	{
		words = nullptr;
	}

	words = new char*[capacity];

	for(int lv = 0; lv<capacity; lv++)
	{
		words[lv] = nullptr;
	}

}

// Function: Wordlist Copy Constructor
Wordlist::Wordlist(const Wordlist &src) {

	stored = src.stored;
	capacity = src.capacity;
	words = new char*[capacity];

	for(int lv = 0; lv<capacity;lv++)
	{
		words[lv] = src.words[lv];
	}

}

// Function: Wordlist Destructor.
Wordlist::~Wordlist() {

	for(int lv = 0;lv<capacity;lv++)
	{
		delete words[lv];
	}

	stored = 0;
	capacity = 0;

}

// Function: display
int	Wordlist::display() const {

	for(int lv=0; lv<capacity;lv++)
	{
		std::cout << words[lv];
		if(lv != (capacity-1))
			std::cout << " ";
	}

	std::cout << "\n";

	return this->capacity;
}

//  Function: word
const char* Wordlist::word(const int index) const {

	if(index<0||index>=stored)
	{
		return nullptr;
	}
	
	return words[index];
}

//  Function: size
int	Wordlist::size() const {

	return this->stored;
}

//  Function: insert
int	Wordlist::insert(const int index, const char word[]) {
	
	if(stored==capacity)//Need to resize
	{
		Wordlist resizedWords(capacity+1);

		//For now simply copy the words over from this->words[]

		for(int lv=0;lv<capacity-1;lv++)
		{
			strcpy(resizedWords.words[lv],this->words[lv]);
		}

		delete []this->words;//Free up the memory

		char tempCStr_prev[] = "";
		strcpy(tempCStr_prev,word);

		char tempCStr_fow[] = "";

		for(int lv = index;lv<index;lv++)
		{
			if(index<0)
				lv=0;

			strcpy(tempCStr_fow,resizedWords.words[lv]);
			strcpy(resizedWords.words[lv],tempCStr_prev);
			strcpy(tempCStr_prev,tempCStr_fow);
			
		}

		delete []tempCStr_fow;
		delete []tempCStr_prev;

		this = &resizedWords;


	}


	int dummyreturnval = -9000;
	return dummyreturnval;
}

//	Funtion: remove
int	Wordlist::remove(const char word[]) {

	//  TODO: 
	int dummyreturnval = -9000;
	return dummyreturnval;
}

//  Funtion: prepend
int	Wordlist::prepend(const Wordlist &other) {

	//  TODO: 
	int dummyreturnval = -9000;
	return dummyreturnval;
}

// Function: search
int Wordlist::search(const char word[]) const {

	//  TODO: 
	int dummyreturnval = -9000;
	return dummyreturnval;
}

//	Funtion: sort
int	Wordlist::sort(const bool asc) {

	//  TODO: 
	int dummyreturnval = -9000;
	return dummyreturnval;
}

//  Funtion: Assignment Operator
Wordlist& Wordlist::operator=(const Wordlist &other) {

	//  TODO: 
	return *this;
}

// Function: missyElliot
int		Wordlist::missyElliot() {

	//  TODO: 
	int dummyreturnval = -9000;
	return dummyreturnval;
}
























