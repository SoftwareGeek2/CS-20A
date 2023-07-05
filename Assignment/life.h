#ifndef life_h
#define life_h

class World;
class Simulation;

class Life {
public:
	int getCol() const;

	int getRow() const;

	int getHeight() const;

	int getWidth() const;

	char getFigure(int r, int c) const;

	void inWorld(World *w);

	void inSimulation(Simulation *s);

	bool areWeInASimulation();
    
protected:
	int m_col;
	int m_row;
	int m_height;
	int m_width;
	char **m_pattern;
	World *m_world;
	Simulation *m_simulation;
};

#endif /* life_h */