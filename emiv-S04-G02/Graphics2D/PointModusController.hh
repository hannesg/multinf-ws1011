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

	/* The following functions are taken over from PointerBase */

	/// this function is called when a user presses a mouse button in the gui at (x,y)
	virtual void MouseDown(int x, int y);

	/// this function is called when a user releases a mouse button in the gui at (x,y)
	virtual void MouseUp(int x, int y);

	/// this function is called when a user holds a mouse button in the gui at (x,y)
	virtual void MouseMove(int x, int y);

	/// this function is called when a user presses a key in the gui. ch is the key pressed.
	// virtual void KeyPressed(unsigned char ch, int x, int y) {} 

	virtual void Activate();

private:
	Coordinate currentPoint_;
	bool pressed_;

};


}

#endif
