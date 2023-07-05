#include "simulation.h"
#include "world.h"
#include "life.h"
#include <iostream>
#include <thread>

Simulation::Simulation(Life **life, int numLife) {
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

Simulation::~Simulation() {
	delete m_world;
}

void Simulation::simulate() {
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

void Simulation::report() {
    //A3. This main may result in a successful build if simulation.h is directly including life.h, instead of using a foward declaration.
	std::string msg = "A1. The decoded string is never gonna let u down. A2. This may not compile if preprocessor directives have not been added before the header files indicating to the compiler to not re-declare them. A3. This main may result in a successful build if simulation.h is directly including life.h, instead of using a foward declaration.";
	std::cout << msg << std::endl;
}

int Simulation::two(int u) { 
	return u >> 1; 
}
int Simulation::three(int x) {
	if (x % 2 == 0)
		return 1;
	else
		return 2;
}
void Simulation::one(int t) {
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
	}
	k = three(watchme);
	watchme = k;
}

void Simulation::delay(int ms) const {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}