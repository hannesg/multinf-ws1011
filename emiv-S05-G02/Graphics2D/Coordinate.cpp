/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include "Coordinate.hh"

namespace Graphics2D {

Coordinate Coordinate::operator + (const Coordinate &c) {
	return Coordinate(x_ + c.x_, y_ + c.y_);
}

Coordinate Coordinate::operator - (const Coordinate &c) {
	return Coordinate(x_ - c.x_, y_ - c.y_);
}

Coordinate Coordinate::operator * (float c) {
	return Coordinate(x_*c, y_*c);
}

Coordinate Coordinate::operator * (int c) {
	return Coordinate(x_*c, y_*c);
}

Coordinate operator * (float f, const Coordinate &c) {
	return Coordinate(f*c.GetXAsFloat(), f*c.GetYAsFloat());
}

Coordinate operator * (int f, const Coordinate &c) {
	return Coordinate(f*c.GetXAsFloat(), f*c.GetYAsFloat());
}

}
