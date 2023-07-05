#include "life.h"

int getCol() const {
	return m_col;
}
int getRow() const {
	return m_row;
}
int getHeight() const {
	return m_height;
}
int getWidth() const {
	return m_width;
}
char getFigure(int r, int c) const {
	return m_pattern[r][c];
}
void inWorld(World *w) {
	m_world = w;
}
void inSimulation(Simulation *s) {
	m_simulation = s;
}
bool areWeInASimulation() {
	return m_simulation != nullptr;
}