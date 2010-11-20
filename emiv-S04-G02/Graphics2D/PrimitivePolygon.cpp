/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include "PrimitivePolygon.hh"
#include "PrimitiveLine.hh"

namespace Graphics2D {

void PrimitivePolygon::Draw(ImageBase *img) const
{
	// Linien erstellen (Zeiger werden benoetigt, da dynamisch 
	// erzeugt wird)
	PrimitiveLine *lines = new PrimitiveLine[points_.size()];

	for(unsigned int i = 0; i < points_.size(); i++) {
		lines[i].SetStartingPoint(points_[i]);
		if(i+ 1 < points_.size()) {
			lines[i].SetEndingPoint(points_[i+1]);
		} else {
			// Wieder an den Startpunkt zurueckgehen
			lines[i].SetEndingPoint(points_[0]);
		}

		lines[i].SetColor(GetColor());
	}
	
	for(unsigned int i = 0; i < points_.size(); i++) {
		lines[i].Draw(img);
	}

	// aufraumen
	delete [] lines;
}

void PrimitivePolygon::SetCoordinates(const vector<Coordinate> &points) 
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
