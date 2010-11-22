/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#ifndef STAR_MODUS_CONTROLLER
#define STAR_MODUS_CONTROLLER

#include "ModusController.hh"
#include "Coordinate.hh"

namespace Graphics2D {

class StarModusController : public ModusController {

public:
	StarModusController(Painter &b) : ModusController(b), pressed_(false) { }
	virtual ~StarModusController() {}

	virtual void MouseDown(int x, int y);
	virtual void MouseUp(int x, int y);
	virtual void MouseMove(int x, int y);
	// virtual void KeyPressed(unsigned char ch, int x, int y) {} 

	virtual void Activate();
	virtual void Deactivate();

private:
	bool pressed_;
	Coordinate startingPoint_;

};


}

#endif
