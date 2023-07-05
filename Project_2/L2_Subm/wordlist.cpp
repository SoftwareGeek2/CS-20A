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
Wordlist::Wordlist(const int max) {
    if (max < 1) {//Initialization case
        words = nullptr;
        capacity = 0;
        stored = 0;
    } else {//Base case
        capacity = max;
        stored = 0;
        words = new char*[capacity];
        for (int i = 0; i < capacity; ++i) {
            words[i] = nullptr;
        }
    }
}


// Function: Wordlist Copy Constructor
Wordlist::Wordlist(const Wordlist &src) {
	//Deep copy as appropriate
    capacity = src.capacity;
    stored = src.stored;
    words = new char*[capacity];
    for (int i = 0; i < capacity; ++i) {
        if (src.words[i]) {
            words[i] = new char[MAX_WORD_SIZE];
            strcpy(words[i], src.words[i]);
        } else {
            words[i] = nullptr;
        }
    }
}


// Function: Wordlist Destructor.
Wordlist::~Wordlist() {
    if (words != nullptr) {
        for (int i = 0; i < capacity; ++i) {
            delete[] words[i];//Delete all characters...
        }
        delete[] words;//And delete the main pointer
    }
}


// Function: display
int Wordlist::display() const {
    if (words == nullptr) {
        return -1;
    }

    for (int i = 0; i < stored; ++i) {
        if (i > 0) {
        	cout << ' ';//Space between words
        }
    	cout << words[i];
    }
    cout << "\n";//Add a new line

    return stored;
}


//  Function: word
const char* Wordlist::word(const int index) const {
    if (index >= 0 && index < stored) {
        return words[index];//Perform appropriate checks and return the word
    } else {
        return nullptr;
    }
}


//  Function: size
int Wordlist::size() const {
    return stored;//Use method to access private data member
}


//  Function: insert
int Wordlist::insert(const int index, const char word[]) {
    if (strlen(word) == 0) {
        return -1;
    }

    if (words == nullptr) {
        capacity = 1;
        stored = 0;
        words = new char*[capacity];
    }
	//Edge cases

    int resizeNeeded = 0;//For determining return value

    if (stored == capacity) {
        resizeNeeded = 1;
        capacity += 1;
        char** newWords = new char*[capacity];
        for (int i = 0; i < stored; ++i) {
            newWords[i] = words[i];
        }
        delete[] words;//Deallocate
        words = newWords;//Reallocate
    }

    int insertIndex = index < 0 ? 0 : (index > stored ? stored : index);//If the index is <0, insert at 0. If more than stored,
	//Insert at stored. Else insert at index

    for (int i = stored; i > insertIndex; --i) {
        words[i] = words[i - 1];
    }//Free up space for the new word

    words[insertIndex] = new char[MAX_WORD_SIZE];
    strcpy(words[insertIndex], word);//Strcpy the word in

    ++stored;

    return resizeNeeded == 1 ? 1 : (words == nullptr ? -2 : 0);//Return 1,-2 or 0 as appropriate
}


//	Funtion: remove
int Wordlist::remove(const char word[]) {
    if (words == nullptr) {
        return -2;
    }

    int removed = 0;
    int newStored = 0;

    char** newWords = new char*[capacity];//Create fresh char**
    for (int i = 0; i < stored; ++i) {
        if (strcmp(words[i], word) != 0) {
            newWords[newStored] = new char[strlen(words[i]) + 1];
            strcpy(newWords[newStored], words[i]);
            newStored++;
        } else {
            removed++;
            delete[] words[i];
        }
    }

    if (removed == 0) {
        // No words removed, deallocating newWords
        for (int i = 0; i < newStored; ++i) {
            delete[] newWords[i];
        }
        delete[] newWords;
    } else {
        // Some words removed, updating words array
        delete[] words;
        words = newWords;
        stored = newStored;
    }

    return removed;
}




//  Funtion: prepend
int Wordlist::prepend(const Wordlist &other) {
    if (other.stored == 0) {
        return 0;
    }

    if (words == nullptr) {
        capacity = other.stored;
        stored = 0;
        words = new char*[capacity];
    }//Edge cases

    int newSize = stored + other.stored;
    if (newSize > capacity) {
        char** newWords = new char*[newSize];
        for (int i = 0; i < stored; ++i) {
            newWords[i + other.stored] = words[i];
        }
        delete[] words;
        words = newWords;
        capacity = newSize;
    } else {
        for (int i = stored - 1; i >= 0; --i) {
            words[i + other.stored] = words[i];
        }
    }

    for (int i = 0; i < other.stored; ++i) {
        words[i] = new char[MAX_WORD_SIZE];
        strcpy(words[i], other.words[i]);//Copy everything one word at a time
    }

    stored = newSize;

    return words == nullptr ? -1 : other.stored;
}


// Function: search
int Wordlist::search(const char word[]) const {
    if (words == nullptr) {
        return -1;
    }

    for (int i = 0; i < stored; ++i) {
        if (strcmp(words[i], word) == 0) {
            return i;//Return index
        }
    }

    return -2;
}


//	Funtion: sort
int Wordlist::sort(const bool asc) {
    if (words == nullptr) {
        return -1;
    }
    if (stored == 1) {
        return 1;
    }

    for (int i = 0; i < stored - 1; ++i) {
        for (int j = 0; j < stored - i - 1; ++j) {//Change here (Next line - asc -> !asc and !asc -> asc)
            if ((!asc && strcmp(words[j], words[j + 1]) > 0) || (asc && strcmp(words[j], words[j + 1]) < 0)) 
			{//Check for both ascending and descending sort case
                char* temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;//Use temp pointer to swap the values
            }
        }
    }

    return 0;
}

//Overloard '=' operator
Wordlist& Wordlist::operator=(const Wordlist &src) {
    if (this == &src) {
        return *this;
    }

    if (words!=nullptr) {
        for (int i = 0; i < stored; ++i) {
            delete[] words[i];
        }
        delete[] words;
    }

    stored = src.stored;
    capacity = src.capacity;
    words = new char*[capacity];

    for (int i = 0; i < stored; ++i) {
        words[i] = new char[MAX_WORD_SIZE];
        strcpy(words[i], src.words[i]);
    }

    return *this;
}


// Function: missyElliot
int Wordlist::missyElliot() {
    if (words == nullptr) {
        return -1;
    }

    int flippedChars = 0;

    for (int i = 0; i < stored / 2; ++i) {
        char* temp = words[i];
        words[i] = words[stored - i - 1];
        words[stored - i - 1] = temp;
    }//Reverse order of words

    for (int i = 0; i < stored; ++i) {
        int wordLen = strlen(words[i]);
        flippedChars += wordLen;
        for (int j = 0; j < wordLen / 2; ++j) {
            char temp = words[i][j];
            words[i][j] = words[i][wordLen - j - 1];
            words[i][wordLen - j - 1] = temp;
        }
    }//Reverse order of characters

    return flippedChars;
}
