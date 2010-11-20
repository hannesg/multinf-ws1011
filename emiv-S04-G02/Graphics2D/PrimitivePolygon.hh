/*
Gruppe: 02
Serie 03
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef __PRIMITIVE_POLYGON_HH
#define __PRIMITIVE_POLYGON_HH

#include "PrimitiveBase.hh"
namespace Graphics2D {

class PrimitivePolygon : public PrimitiveBase
{
public:
	
	/* SetCoordinates, zum Setzen der Koordinaten (ueberschrieben) */
	virtual void SetCoordinates(const vector<Coordinate> &points);

	/* Draw-Funktion */
	virtual void Draw(ImageBase *img) const;



};

}
#endif
