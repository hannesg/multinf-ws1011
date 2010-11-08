#ifndef __PRIMITIVE_POINT
#define __PRIMITIVE_POINT

#include "PrimitiveBase.hh"
#include "Color.hh"
#include "Coordinate.hh"

namespace Graphics2D {

class PrimitivePoint : public PrimitiveBase
{
public:
	PrimitivePoint() : color_(0, 0, 0), num_points_(1) { coor_.push(Coordinate(0, 0)); }
	PrimitivePoint(Coordinate c) : color_(0, 0, 0), num_points_(1) { coor_.push(c); }
	PrimitivePoint(Coordinate coor, Color c) : color_(c), num_points_(1) { coor_.push(coor); }

	virtual void Draw(ImageBase *img);
	
	// virtual void SetCoordinate(Coordinate c);

};

}


#endif 
