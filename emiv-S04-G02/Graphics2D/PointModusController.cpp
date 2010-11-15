/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#include "PointModusController.hh"

namespace Graphics2D {

void PointModusController::Activate() {

	pressed_ = false;
}

void PointModusController::MouseDown(int x, int y) {

	currentPoint_ = Coordinate(x, y);
	pressed_ = true;
}

void PointModusController::MouseUp(int x, int y)  {

}

void PointModusController::MouseMove(int x, int y)  {

}

}