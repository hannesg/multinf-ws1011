/*
Gruppe: 02
Serie 03
Matthias Boehm, 895778
Hannes Georg, 850360
*/
#ifndef __COORDINATE_HH
#define __COORDINATE_HH

#include <cmath>

using namespace std;

namespace Graphics2D {

class Coordinate
{
public:

	/* constructors */
	Coordinate() : x_(0), y_(0) { }
	Coordinate(float x, float y) : x_(x), y_(y) {}

	/* setters */
	inline void SetX(float x) { x_ = x; }
	inline void SetY(float y) { y_ = y; }
	inline void SetX(int x) { x_ = x; }
	inline void SetY(int y) { y_ = y; }

	inline void Set(float x, float y) { x_ = x; y_ = y; }
	inline void Set(int x, int y) { x_ = x; y_ = y; }

	/* getters */
	inline int GetX() const { return (int)rint(x_); };
	inline int GetY() const { return (int)rint(y_); };

	/* comparison */
	bool operator == (const Coordinate &c) const { return (c.x_ == x_ && c.y_ == y_); }
	bool operator != (const Coordinate &c) const { return !(this->operator ==(c)); }

private:
	float x_, y_;
};

}

#endif 
