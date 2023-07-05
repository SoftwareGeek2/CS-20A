#include "life.h"
#include "slider.h"
#include "pent.h"
#include "blink4.h"
#include "square.h"
#include "simulation.h"


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
