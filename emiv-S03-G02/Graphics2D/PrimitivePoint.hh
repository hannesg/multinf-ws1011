#ifndef __PRIMITIVE_POINT
#define __PRIMITIVE_POINT

#include "PrimitiveBase.hh"
#include "Color.hh"
#include "Coordinate.hh"

namespace Graphics2D {

class PrimitivePoint : public PrimitiveBase
{
public:
	/* constructors. Note that they all call the base constructor PrimitiveBase with an 
	 * argument of 1; this enables checking, that there is only *one* coordinate given 
	 * to the function "SetCoordinates()" */
	PrimitivePoint() { Init(Coordinate(0, 0), Color(0, 0, 0)); }

	PrimitivePoint(Coordinate coor) { Init(coor, Color(0, 0, 0)); }
	PrimitivePoint(Coordinate coor, Color c) { Init(coor, c); }

	PrimitivePoint(int x, int y) { Init(Coordinate(x, y), Color(0, 0, 0)); }
	PrimitivePoint(int x, int y, Color c) { Init(Coordinate(x, y), c); }

	/* overwrite Draw function */
	virtual void Draw(ImageBase *img) const;
	
	/* special setters/getters */
	void SetCoordinate(Coordinate c);
	Coordinate GetCoordinate() const { return points_.front(); }

private:
	/* how many points are allowed? */
	virtual int GetNumberOfPointsAllowed() { return 1; }

	/* initialization, called from constructors */
	void Init(Coordinate coor, Color c);

};

}


#endif 
