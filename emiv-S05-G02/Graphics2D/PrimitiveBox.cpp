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
	// check that we have a box

	if(points.size() == 5) {
		if(points[0] == points[4]) {
			if(( points[0].GetX() == points[1].GetX() 
				&& points[1].GetY() == points[2].GetY() 
				&& points[2].GetX() == points[3].GetX()
				&& points[3].GetY() == points[4].GetY())
				||
				(points[0].GetY() == points[1].GetY()
				&& points[1].GetX() == points[2].GetX()
				&& points[2].GetY() == points[3].GetY()
				&& points[3].GetX() == points[4].GetX())) {

					points_ = points;

					// delete last point
					points_.pop_back();
			}
		}
	}
}
	

void PrimitiveBox::Init(const Coordinate &c1, const Coordinate &c2, const Color &c) {

	points_.clear();

	// construct rectangle
	points_.push_back(c1);
	points_.push_back(Coordinate(c1.GetX(), c2.GetY()));
	points_.push_back(c2);
	points_.push_back(Coordinate(c2.GetX(), c1.GetY()));
	SetColor(c);
}

}
