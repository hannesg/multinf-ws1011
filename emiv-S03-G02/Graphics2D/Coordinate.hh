#ifndef __COORDINATE_HH
#define __COORDINATE_HH

namespace Graphics2D {

class Coordinate
{
public:

	Coordinate() : x_(0), y_(0) { }
	Coordinate(float x, float y) : x_(x), y_(y) {}
	inline void SetX(float x) { x_ = x; }
	inline void SetY(float y) { y_ = y; }
	inline int GetX() { return (int)x_; }
	inline int GetY() { return (int)y_; }

private:
	float x_, y_;
};

}

#endif 
