#ifndef SLIDER_H
#define SLIDER_H

#include "life.h"
#include "constants.h"

class Slider : public Life {
public:
	Slider(int r, int c);
	
	~Slider();
};

#endif //SLIDER_H