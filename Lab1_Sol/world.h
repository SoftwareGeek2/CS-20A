#ifndef WORLD_H
#define WORLD_H

#include "constants.h"
//#include "life.h"
class Life;

class World {
public:
	World();
	
	~World();
	
	void render() const;
	
	void computeNextState();
	
	bool initState(Life *life);

private:

	void clearScreen() const;
	
	char nextState(char state, char row, char col, bool toggle) const;
	
	char **m_grid_1;
	char **m_grid_2;
	bool m_toggle;
	
};

#endif //WORLD_H
