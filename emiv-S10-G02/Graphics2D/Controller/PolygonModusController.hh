/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#ifndef POLYGON_MODUS_CONTROLLER
#define POLYGON_MODUS_CONTROLLER

#include "ModusController.hh"
#include "Coordinate.hh"

#define MAX_DELTA 5

namespace Graphics2D {

class PolygonModusController : public ModusController {

public:
	PolygonModusController(Painter &b) : ModusController(b), delta(MAX_DELTA) { }
	virtual ~PolygonModusController() {}

	virtual void MouseDown(int x, int y);
	virtual void MouseUp(int x, int y);
	virtual void MouseMove(int x, int y);
	// virtual void KeyPressed(unsigned char ch, int x, int y) {} 

	virtual void Activate();
	virtual void Deactivate();

private:
	vector<Coordinate> points_;

	// Entfernung vom Startpunkt, innerhalb der ein Punkt als Endpunkt betrachtet wird
	const int delta;

	// Gibt true zurueck, wenn Punkt nahe dem Startpunkt ist
	bool IsCloseToStartingPoint(const Coordinate &c) const;

};


}

#endif
