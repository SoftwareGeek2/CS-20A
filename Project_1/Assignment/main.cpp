#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

#ifdef _MSC_VER  // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
#include <windows.h>
#else			// DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
// not Microsoft Visual C++, so assume UNIX interface
#include <iostream>
#include <cstring>
#include <cstdlib>
#endif			// DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES

///////////////////////////////////////////////////////////////////////////
// Global Constants
///////////////////////////////////////////////////////////////////////////

const int CANVAS_ROW = 24;
const int CANVAS_COL = 24;

const int SQUARE_SIZE = 2;
const int PENT_SIZE = 3;
const int BLINK4_SIZE = 9;
const int SLIDER_SIZE = 3;

const int MAX_STEPS = 30;

const char ALIVE = 'X';
const char DEAD = '.';


///////////////////////////////////////////////////////////////////////////
// Type Definitions
///////////////////////////////////////////////////////////////////////////

class World;
class Simulation;

class Pent : public Life {
public:
	Pent(int r, int c) {
		m_col = c;
		m_row = r;
		m_height = PENT_SIZE;
		m_width = PENT_SIZE;

		//Allocate space for figure
		m_pattern = new char*[m_height];
		for (int i = 0; i < m_height; i++) {
			m_pattern[i] = new char[m_width];
		}

		//Initialize figure
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				m_pattern[i][j] = ALIVE;
			}
		}
		m_pattern[0][0] = DEAD;
		m_pattern[0][2] = DEAD;
		m_pattern[2][1] = DEAD;
		m_pattern[2][2] = DEAD;
	}
	~Pent() {
		for (int i = 0; i < m_height; i++) {
			delete[] m_pattern[i];
		}
		delete[] m_pattern;
	}
};

class Square : public Life {
public:
	Square(int r, int c) {
		m_col = c;
		m_row = r;
		m_height = SQUARE_SIZE;
		m_width = SQUARE_SIZE;

		//Allocate space for figure
		m_pattern = new char*[m_height];
		for (int i = 0; i < m_height; i++) {
			m_pattern[i] = new char[m_width];
		}

		//Initialize figure
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				m_pattern[i][j] = ALIVE;
			}
		}

	}
	~Square() {
		for (int i = 0; i < m_height; i++) {
			delete[] m_pattern[i];
		}
		delete[] m_pattern;
	}
};

class Slider : public Life {
public:
	Slider(int r, int c) {
		m_col = c;
		m_row = r;
		m_height = SLIDER_SIZE;
		m_width = SLIDER_SIZE;

		// Allocate space for figure
		m_pattern = new char*[m_height];
		for (int i = 0; i < m_height; i++) {
			m_pattern[i] = new char[m_width];
		}

		// Initialize figure
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				m_pattern[i][j] = DEAD;
			}
		}
		m_pattern[0][1] = ALIVE;
		m_pattern[1][2] = ALIVE;
		m_pattern[2][0] = ALIVE;
		m_pattern[2][1] = ALIVE;
		m_pattern[2][2] = ALIVE;
	}
	~Slider() {
		for (int i = 0; i < m_height; i++) {
			delete[] m_pattern[i];
		}
		delete[] m_pattern;
	}
};

class Blink4 : public Life {
public:
	Blink4(int r, int c) {
		m_col = c;
		m_row = r;
		m_height = BLINK4_SIZE;
		m_width = BLINK4_SIZE;

		//Allocate space for figure
		m_pattern = new char*[m_height];
		for (int i = 0; i < m_height; i++) {
			m_pattern[i] = new char[m_width];
		}

		//Initialize figure
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				m_pattern[i][j] = DEAD;
			}
		}
		m_pattern[0][4] = ALIVE;
		m_pattern[1][4] = ALIVE;
		m_pattern[2][4] = ALIVE;

		m_pattern[6][4] = ALIVE;
		m_pattern[7][4] = ALIVE;
		m_pattern[8][4] = ALIVE;

		m_pattern[4][0] = ALIVE;
		m_pattern[4][1] = ALIVE;
		m_pattern[4][2] = ALIVE;

		m_pattern[4][6] = ALIVE;
		m_pattern[4][7] = ALIVE;
		m_pattern[4][8] = ALIVE;
	
	}
	~Blink4() {
		for (int i = 0; i < m_height; i++) {
			delete[] m_pattern[i];
		}
		delete[] m_pattern;
	}
};

class World {
public:
	World() {
		m_toggle = true;
		m_grid_1 = new char*[CANVAS_ROW];
		m_grid_2 = new char*[CANVAS_ROW];

		for (char i = 0; i < CANVAS_ROW; i++) {
			m_grid_1[i] = new char[CANVAS_COL];
			m_grid_2[i] = new char[CANVAS_COL];
		}
		for (char i = 0; i < CANVAS_ROW; i++) {
			for (char j = 0; j < CANVAS_COL; j++) {
				m_grid_1[i][j] = DEAD;
			}
		}
	}
	~World() {
		for (char i = 0; i < CANVAS_ROW; i++) {
			delete[] m_grid_1[i];
			delete[] m_grid_2[i];
		}
		delete[] m_grid_1;
		delete[] m_grid_2;

	}
	void render() const {
		clearScreen();
		if (m_toggle) {
			for (char i = 0; i < CANVAS_ROW; i++) {
				for (char j = 0; j < CANVAS_COL; j++) {
					std::cout << m_grid_1[i][j];
				}
				std::cout << std::endl;
			}
		}
		else {
			for (char i = 0; i < CANVAS_ROW; i++) {
				for (char j = 0; j < CANVAS_COL; j++) {
					std::cout << m_grid_2[i][j];
				}
				std::cout << std::endl;
			}
		}
		for (char i = 0; i < CANVAS_COL; i++) {
			std::cout << '=';
		}
		std::cout << std::endl;
	}
	void computeNextState() {
		if (m_toggle) {
			for (char i = 0; i < CANVAS_ROW; i++) {
				for (char j = 0; j < CANVAS_COL; j++) {
					m_grid_2[i][j] =
						nextState(m_grid_1[i][j], i, j, m_toggle);
				}
			}
			m_toggle = !m_toggle;
		}
		else {
			for (char i = 0; i < CANVAS_ROW; i++) {
				for (char j = 0; j < CANVAS_COL; j++) {
					m_grid_1[i][j] =
						nextState(m_grid_2[i][j], i, j, m_toggle);
				}
			}
			m_toggle = !m_toggle;
		}
	}
	bool initState(Life *life) {
		if (life == nullptr) {
			std::cout << "Cannot add nullptr life" << std::endl;
			return false;
		}
		for (char i = life->getRow(); i - life->getRow() < life->getHeight(); i++) {
			for (char j = life->getCol(); j - life->getCol() < life->getWidth(); j++) {
				if (i < CANVAS_ROW && j < CANVAS_COL) {
					m_grid_1[i][j] =
						life->getFigure(i - life->getRow(), j - life->getCol());
				}
			}
		}
		return true;
	}

private:

	void clearScreen() const {
#ifdef _MSC_VER  // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		COORD upperLeft = { 0, 0 };
		DWORD dwCharsWritten;
		FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
			&dwCharsWritten);
		SetConsoleCursorPosition(hConsole, upperLeft);
#else  // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
		static const char* term = getenv("TERM");// will just write a newline in an Xcode output window
		if (term == nullptr || strcmp(term, "dumb") == 0)
			std::cout << std::endl;
		else {
			static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
			std::cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << std::flush;
		}
#endif // DO NOT BREAK APART THE PREPROCESSOR DIRECTIVES
	}
	char nextState(char state, char row, char col, bool toggle) const {
		int yCoord = row;
		int xCoord = col;
		char neighbors = 0;
		if (toggle) {
			for (char i = yCoord - 1; i <= yCoord + 1; i++) {
				for (char j = xCoord - 1; j <= xCoord + 1; j++) {
					if (i == yCoord && j == xCoord) {
						continue;
					}
					if (i > -1 && i < CANVAS_ROW && j > -1 && j < CANVAS_COL) {
						if (m_grid_1[i][j] == ALIVE) {
							neighbors++;
						}
					}
				}
			}
		}
		else {
			for (char i = yCoord - 1; i <= yCoord + 1; i++) {
				for (char j = xCoord - 1; j <= xCoord + 1; j++) {
					if (i == yCoord && j == xCoord) {
						continue;
					}
					if (i > -1 && i < CANVAS_ROW && j > -1 && j < CANVAS_COL) {
						if (m_grid_2[i][j] == ALIVE) {
							neighbors++;
						}
					}
				}
			}
		}
		if (state == ALIVE) {
			return (neighbors > 1 && neighbors < 4) ? ALIVE : DEAD;
		}
		else {
			return (neighbors == 3) ? ALIVE : DEAD;
		}
	}

	// The rules of Conway's Simulation of Life requires each cell to
	// examine it's neighbors.  So, we have to check the entire world
	// first before we change it.  We can use two copies of the world, 
	// one to check the current state (current day) then another to generate 
	// the next state(for the next day). We can toggle between them each 
	// step, to avoid having to copy between worlds each step (day) of the game.
	char **m_grid_1;
	char **m_grid_2;
	bool m_toggle;
};

class Simulation {
public:
	Simulation(Life **life, int numLife) {
		watchme = 4;
		m_steps = 0;
		m_automate = false;
		m_world = new World();

		if (life != nullptr) {
			for (int i = 0; i < numLife; i++) {
				if (life[i] != nullptr) {
					bool success = m_world->initState(life[i]);
					if (!success) {
						std::cout << "Failed to add life to the world" << std::endl;
					}
				}
			}
		}
	}
	~Simulation() {
		delete m_world;
	}
	void simulate() {
		while (true) {
			m_world->render();

			if (!m_automate) {
				std::cout << "command (<space> to step, <a> to automate, <q> to quit): ";

				std::string action;
				std::getline(std::cin, action);

				switch (action[0])
				{

				default:
					std::cout << '\a' << std::endl;  // beep
					continue;
				case 'q':
					std::cout << "Quitting Game." << std::endl;
					return;
				case 's':

					continue;
				case ' ':

					break;
				case 'a':
					m_automate = true;
					break;
				}
			}
			else {
				if (m_steps >= MAX_STEPS) {
					std::cout << "Reached max steps, quitting." << std::endl;
					return;
				}
				delay(300);
			}
			m_steps++;
			m_world->computeNextState();
		}
	}
	void report() {
		std::string msg = "Hello World!"; // Replace Hello World with your answer.
		std::cout << msg << std::endl;
	}
	int two(int u) { 
		return u >> 1; 
	}
	int three(int x) {
		if (x % 2 == 0)
			return 1;
		else
			return 2;
	}
	void one(int t) {
		int i = 7;
		int k = watchme;
		while (--i > t) {
			if (i == 0) 
				k = 7;
			else if (i == 1) 
				k = 9;
			else if (i == 4) 
				k = 8;
			else if (i == 5) 
				k = 5;
			else 
				k = two(watchme);
			watchme = k;
			//DELME std::cout << watchme << std::endl;
		}
		k = three(watchme);
		watchme = k;
		//DELME std::cout << watchme << std::endl;
	}
private:
	void delay(int ms) const {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	int watchme;
	World * m_world;
	int m_steps;
	bool m_automate;
};

int main() {

	const int numLife = 4;
	Life **population = new Life*[numLife];

	population[0] = new Slider(8, 4); 
	population[1] = new Pent(18, 14);
	population[2] = new Blink4(3, 13);
	population[3] = new Square(14, 10);
	
	// Create the game
	Simulation s(population, numLife);

	// Debugger Exercise
	s.one('k' - 'h');

	// Run the game
	s.simulate();

	// Report
	s.report();

	// Clean up
	delete population[0];
	delete population[1];
	delete population[2];
	delete population[3];
	delete[] population;

}
