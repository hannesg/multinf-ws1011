/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef __PRIMITIVE_BOX_HH
#define __PRIMITIVE_BOX_HH

#include "PrimitivePolygon.hh"

namespace Graphics2D {

class PrimitiveBox : public PrimitivePolygon
{
public:
	
	/* SetCoordinates, zum Setzen der Koordinaten (ueberschrieben) */
	virtual void SetCoordinates(const vector<Coordinate> &points);

	/* Draw-Funktion */
	virtual void Draw(ImageBase *img) const;



};

}
#endif
