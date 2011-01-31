/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <cmath>
#include "Coordinate.hh"

using namespace std;

namespace Graphics2D {

Coordinate Coordinate::operator + (const Coordinate &c) const {
	return Coordinate(x_ + c.x_, y_ + c.y_);
}

Coordinate Coordinate::operator - (const Coordinate &c) const {
	return Coordinate(x_ - c.x_, y_ - c.y_);
}

Coordinate Coordinate::operator * (float c) const {
	return Coordinate(x_*c, y_*c);
}

Coordinate Coordinate::operator / (float c) const {
	return Coordinate(x_/c, y_/c);
}

/*Coordinate Coordinate::operator * (int c) const {
	return Coordinate(x_*c, y_*c);
} */

Coordinate operator * (float f, const Coordinate &c) {
	return Coordinate(f*c.GetXAsFloat(), f*c.GetYAsFloat());
}

/* Coordinate operator / (const Coordinate &c, float f) {
	return Coordinate(c.GetXAsFloat()/f, c.GetYAsFloat()/f);
} */

/* Coordinate operator * (int f, const Coordinate &c) {
	return Coordinate(f*c.GetXAsFloat(), f*c.GetYAsFloat());
} */

Coordinate &Coordinate::operator += (const Coordinate &c) {
	*this = *this + c;
	return *this;
}

Coordinate &Coordinate::operator -= (const Coordinate &c) {
	*this = *this - c;
	return *this;
}

Coordinate &Coordinate::operator *= (float x) {
	*this = *this * x;
	return *this;
}

Coordinate &Coordinate::operator /= (float x) {
	*this = *this / x;
	return *this;
}

/* Coordinate &Coordinate::operator *= (int x) {
	*this = *this * x;
	return *this;
}*/

void Coordinate::Rotate(const Coordinate &c, float angle) {

	Coordinate o = *this - c;
	
	float newx = o.x_*cos(angle) - o.y_*sin(angle);
	float newy = o.x_*sin(angle) + o.y_*cos(angle);

	x_ = newx;
	y_ = newy;
	
	*this += c;
}

float Coordinate::scalarProduct(const Coordinate &c) const {

	return x_*c.x_ + y_*c.y_;
}

ostream & operator << (ostream &out, const Coordinate &c) {

	out << "(" << c.GetXAsFloat() << ", " << c.GetYAsFloat() << ")";
	return out;
}

}
