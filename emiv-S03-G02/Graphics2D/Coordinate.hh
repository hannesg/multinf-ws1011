/*
Gruppe: 02
Serie 03
Matthias Boehm, 895778
Hannes Georg, 850360
*/
#ifndef __COORDINATE_HH
#define __COORDINATE_HH

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

	/* getters */
	inline int GetX() const { return (int)x_; };
	inline int GetY() const { return (int)y_; };

private:
	float x_, y_;
};

}

#endif 
