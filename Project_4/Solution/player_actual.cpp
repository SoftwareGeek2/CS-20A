/**

#include"player.h"
#include"entity.h"
#include"stack.h"
#include"dllist.h"
#include"room.h"
#include"maze.h"
#include<unistd.h> 
#include<iostream>

//  Player( ... )
//		Constructs and initializes the Player/Entity and its member variables
//		Remembers and discovers the starting room.
Player::Player(Maze* maze, Room p, std::string name, char sprite, const bool tbacktrack)
	:Entity(maze, p, name, sprite),
	m_lookingPaper(),
	m_discoveredRooms(),
	m_btQueue(),
	m_btStack(),
	BACKTRACKENABLED(tbacktrack) {

	// Discover the starting room
	m_discoveredRooms.insert_front(p);
	m_lookingPaper.enqueue(p);
}

//  stuck() 
//		See if the player is stuck in the maze (no solution)
bool Player::stuck() const {
	return Entity::state() == State::NOEXIT;
}

//  foundExit()
//		See if the player has found the exit
bool Player::foundExit() const {
	return Entity::state() == State::EXIT;
}

//  getTargetRoom()
//		Get the room the player wants to look around next.
//      If m_lookingPaper is empty then return an invalid room.
Room Player::getTargetRoom() const {
	if (m_lookingPaper.empty()) return Room(-1, -1);
	return m_lookingPaper.peek();
}

// discovered
//		returns true if the item is in the list
bool Player::discovered(const Room &p) const {
	return (m_discoveredRooms.find(p) != -1);
}



// say()
//		What does the player say?
//		Already Implemented, nothing to do here
void Player::say() {

	// Freedom supercedes being eaten
	if (state() == State::EXIT) {
		std::cout << name() << ": WEEEEEEEEE!";
		return;
	} 
 
	// Being eaten supercedes being lost
	switch (interact()) {
	case Interact::ATTACK:
		std::cout << name() << ": OUCH!";
		break;
	case Interact::GREET:
		break;
	case Interact::ALONE:
	default:
		switch (state()) {
		case State::LOOK:
			std::cout << name() << ": Where is the exit?";
			break;
		case State::NOEXIT:
			std::cout << name() << ": Oh no! I am Trapped!";
			break;
		case State::BACKTRACK:
			std::cout << name() << ": Got to backtrack...";
			break;
		default:
			break;
		}

		break;
	}
}


//  update() 
//		This function implements an algorithm to look through the maze
//      for places to move (STATE::LOOK). update also handles moving the 
//		player as well, if there is an open undiscovered cell to move to the  
//		player just moves there.  However, there will be cases in the next 
//		desired room to look around is not adjacent (more than one cell away), 
//		at this room the player must backtrack (State::BACKTRACK) to a room 
//		that is adjacent to the next room the player was planning to visit
//
//		The player can only do one thing each call, they can either LOOK or 
//		BACKTRACK not both.  Nor should the player move more than one cell per
//		call to update.  If you examine the function calls for the entire game
//		you should observe that this is already be called within a loop. Your
//		Implementation should NOT have any loops that pertain to actual movement 
//		of the player.  
//
//		Backtracking is challenging, save it for the very very very last thing.
//		Make sure the STATE::LOOK aspect compiles and works first.
void Player::update() {
  //bool doConcludeBackTrack = false;
	// Backtracking enabled
	if (BACKTRACKENABLED) {
		//Case for NOEXIT
		if (m_lookingPaper.empty()) {
			state(State::NOEXIT);
			return;
		}
    //std::cout << room() << std::endl;

		bool n = room().adjacent(getTargetRoom());

    //std::cout << "The room we called with is " << room() << std::endl;
    //std::cout << "Target room is : " << getTargetRoom() << std::endl;
		if (!n) 
    {

      if(state()!=State::BACKTRACK)//I.e. we have just begun to backtrack
      {
        state(State::BACKTRACK);
        
        
        //Pop onto m_btList
        //But place the first value (current location) into m_btQueue
        m_btQueue.enqueue(m_btStack.peek());
        //m_btList.insert_front(m_btStack.peek());//DONT Insert the very first value onto the backtrack lsit
        m_btStack.pop();
  
        //Go to the popped position
  			//move(m_btList.peek_front());
        //Since we just began to backtrack, do not travel to the first value
        //(We are already there)

        m_btList.insert_front(m_btStack.peek());
        m_btStack.pop();
        move(m_btList.peek_front());//Now move
        //std::cout << "Now move to :" << m_btList.peek_front() << std::endl;
        
  			return;
  	  } 
    
      //Pop onto m_btList
      m_btList.insert_front(m_btStack.peek());
      m_btStack.pop();

      //Go to the popped position
			move(m_btList.peek_front());
      //std::cout << "Now move to :" << m_btList.peek_front() << std::endl;
			return;
		} 

    state(State::LOOK);
    //Reset state to looking
		Room pos = m_lookingPaper.peek();
    
		if (maze()->foundExit(pos)) {
			state(State::EXIT);
			return;
		}


    //std::cout << "The backtrack list is : ";
    //m_btList.print();
    //std::cout << std::endl;
    //std::cout << "Current state of m_btStack is :" << std::endl;
    //m_btStack.print();
    //std::cout << std::endl;

    DLList<Room>  m_btList_dup = m_btList;
    
    while(!m_btList.empty())//Since backtracking is now finished, pop off from the list back onto m_btStack to reconstruct it
    {
      
      //std::cout << Room() << std::endl;
      //doConcludeBackTrack = true;
        m_btStack.push(m_btList.peek_front());
        //std::cout << "The value pushed onto m_btStack from the list is :" << m_btList.peek_front() << std::endl;
        m_btList.remove_front();
    }

    if(!m_btQueue.empty())
      {
        m_btStack.push(m_btQueue.peek());
        m_btQueue.dequeue();
        //Put back the first value that we had removed
      }

    while(!m_btList_dup.empty())
    {
      //std::cout << "The room I want to add here is " << room() << std::endl;
      m_btStack.push(m_btList_dup.peek_rear());
      m_btList_dup.remove_rear();
      //doConcludeBackTrack = false;
    }

    //What is critical here is that both m_btStack and m_btList use LIFO structuring, meaning the rooms that were visited will be sent (i.e. popped either way) to the data structure in that exact order.

    //m_btStack will hold all rooms we visit in that exact order
    
    
		m_lookingPaper.dequeue();
    //std::cout << "The room we are moving to is " << pos << std::endl;
		move(pos);
    m_btStack.push(pos);//Push the rooms only just after we move

    //std::cout << "Entire history of visits thus far is :" << std::endl;
    //m_btStack.print();
    //std::cout << std::endl;

    //An important nuance here while reconstructing the stack; since m_btStack is storing all the rooms visited in the exact order, assuming we are just about to finish backtracking, we will not enter into the backtracking if-clause, however the command m_btStack.push(room()) will take care of adding the current room to the stack
 
		Room west = Room(pos.x() - 1, pos.y());
		Room east = Room(pos.x() + 1, pos.y());
		Room north = Room(pos.x(), pos.y() - 1);
		Room south = Room(pos.x(), pos.y() + 1);

		if (maze()->open(west) and !discovered(west)) {
			m_lookingPaper.enqueue(west);
			m_discoveredRooms.insert_front(west);
		}

		if (maze()->open(east) and !discovered(east)) {
			m_lookingPaper.enqueue(east);
			m_discoveredRooms.insert_front(east);
		}

		if (maze()->open(north) and !discovered(north)) {
			m_lookingPaper.enqueue(north);
			m_discoveredRooms.insert_front(north);
		}

		if (maze()->open(south) and !discovered(south)) {
			m_lookingPaper.enqueue(south);
			m_discoveredRooms.insert_front(south);
		}

	}
	else {
		//No space to move -> STUCK return
		if (m_lookingPaper.empty()) {
      //std::cout << "HELLLLOOOOO I WAS HEREEEEEEEE" << std::endl;
			state(State::NOEXIT);
			return;
		}

    //std::cout << "HELLLLOOOOO I WAS HEREEEEEEEE" << std::endl;
    //exit(0);

		//READ FROM THE BOTTOM
		//get current pos.
		//if(pos == exit), then state EXIT. return;
		//m_lookingPaper.dequeue();
		//set current position to the pos.
		//Begin algorithm same as lecture using queue

		Room pos = m_lookingPaper.peek();
		if (maze()->foundExit(pos)) {
			state(State::EXIT);
			return;
		}
		m_lookingPaper.dequeue();
		move(pos);
    //std::cout << "HELLLLOOOOO I WAS HEREEEEEEEE" << std::endl;
    //exit(0);
		Room west = Room(pos.x()-1, pos.y());
		Room east = Room(pos.x()+1, pos.y());
		Room north = Room(pos.x(), pos.y()-1);
		Room south = Room(pos.x(), pos.y()+1);

		if (maze()->open(west) and !discovered(west)) {
      //std::cout << "HELLLLOOOOO I WAS HEREEEEEEEE" << std::endl;
      //exit(0);
			m_lookingPaper.enqueue(west);
			m_discoveredRooms.insert_front(west);
		}

		if (maze()->open(east) and !discovered(east)) {
      //std::cout << "HELLLLOOOOO I WAS HEREEEEEEEE" << std::endl;
      //exit(0);
			m_lookingPaper.enqueue(east);
			m_discoveredRooms.insert_front(east);
		}

		if (maze()->open(north) and !discovered(north)) {
			m_lookingPaper.enqueue(north);
			m_discoveredRooms.insert_front(north);
		}

		if (maze()->open(south) and !discovered(south)) {
			m_lookingPaper.enqueue(south);
			m_discoveredRooms.insert_front(south);
		}

	}
}

*/