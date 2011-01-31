/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/
#ifndef __COORDINATE_HH
#define __COORDINATE_HH

#include <cmath>
#include <iostream>

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
	
	inline float GetXAsFloat() const { return x_; }
	inline float GetYAsFloat() const { return y_; }

	/* comparison */
	bool operator == (const Coordinate &c) const { return (c.x_ == x_ && c.y_ == y_); }
	bool operator != (const Coordinate &c) const { return !(this->operator ==(c)); }
	
	/* weitere Operatoren */
	Coordinate operator + (const Coordinate &c) const;
	Coordinate operator - (const Coordinate &c) const;
	Coordinate operator * (float x) const;
	Coordinate operator / (float x) const;
	// Coordinate operator * (int x) const;
	
	Coordinate &operator += (const Coordinate &c);
	Coordinate &operator -= (const Coordinate &c);
	Coordinate &operator *= (float x);
	Coordinate &operator /= (float x);
	// Coordinate &operator *= (int x);

	// Skalarprodukt
	float operator * (const Coordinate &c) const { return scalarProduct(c); }
	float scalarProduct(const Coordinate &c) const;

	// computes the length of the vector represented by this coordinate
	float length() const { return sqrt(x_*x_ + y_*y_); }
	
	/* rotation */
	void Rotate(const Coordinate &c, float angle);

private:
	float x_, y_;
};

Coordinate operator * (float x, const Coordinate &c);
// Coordinate operator * (int x, const Coordinate &c);

ostream & operator << (ostream &out, const Coordinate &c);

}

#endif 
