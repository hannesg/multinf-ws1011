/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef __PRIMITIVE_STAR
#define __PRIMITIVE_STAR

#include "PrimitivePolygon.hh"
#include "Color.hh"
#include "Coordinate.hh"

namespace Graphics2D {

class PrimitiveStar : public PrimitivePolygon
{
public:
	
	virtual void Draw(ImageBase *img) const;

	// deconstructor
	virtual ~PrimitiveStar() {}
	

private:

};


}


#endif 
