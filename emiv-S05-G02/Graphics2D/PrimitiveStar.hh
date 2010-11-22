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

	// constructors
	PrimitiveStar() { Init(Coordinate(0, 0), 0, 0); }
	PrimitiveStar(const Coordinate &c, float ir, float ro) { Init(c, ir, ro); }

	// deconstructor
	virtual ~PrimitiveStar() {}

	// setters/getters
	void SetCenter(const Coordinate &c) { Init(c, innerRadius_, outerRadius_); }
	void SetInnerRadius(float ir) { Init(center_, ir, outerRadius_); }
	void SetOuterRadius(float ro) { Init(center_, innerRadius_, ro); }

	Coordinate GetCenter() const { return center_; }
	float GetInnerRadius() const { return innerRadius_; }
	float GetOuterRadius() const { return outerRadius_; }
	
	// Zeichenfunktion
	virtual void Draw(ImageBase *img) const;

	// SetCoordinates nicht ueberladen

	

private:
	// Initialisation function
	void Init(const Coordinate &c, float innerRadius, float outerRadius);

	// variables
	float innerRadius_;
	float outerRadius_;
	Coordinate center_;

};


}


#endif 
