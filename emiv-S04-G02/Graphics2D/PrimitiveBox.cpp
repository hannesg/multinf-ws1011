/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include "PrimitiveBox.hh"
#include "PrimitiveLine.hh"

namespace Graphics2D {

void PrimitiveBox::Draw(ImageBase *img) const
{
	// Einfach die Polygon-Zeichenmethode aufrufen
	PrimitivePolygon::Draw(img);
}

void PrimitiveBox::SetCoordinates(const vector<Coordinate> &points) 
{
	// Check whether we really have a polygon
	if(points.size() < 4) {
		return;
	}

	if(points[0] != points[points.size()-1]) {
		return;
	}

	points_ = points;

}

}
