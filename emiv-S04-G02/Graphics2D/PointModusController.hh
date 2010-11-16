/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#ifndef POINT_MODUS_CONTROLLER
#define POINT_MODUS_CONTROLLER

#include "ModusController.hh"
#include "Coordinate.hh"

namespace Graphics2D {

class PointModusController : public ModusController {

public:
	PointModusController(Painter &b) : ModusController(b), pressed_(false) { }

	virtual void MouseDown(int x, int y);
	virtual void MouseUp(int x, int y);
	virtual void MouseMove(int x, int y);
	// virtual void KeyPressed(unsigned char ch, int x, int y) {} 

	virtual void Activate();
	virtual void Deactivate();

private:
	bool pressed_;

};


}

#endif
