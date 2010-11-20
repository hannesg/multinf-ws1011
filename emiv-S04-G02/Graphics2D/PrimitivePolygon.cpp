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
	unsigned int countLines = points_.size() -1;
	PrimitiveLine *lines = new PrimitiveLine[countLines];

	for(unsigned int i = 0; i < countLines; i++) {
		lines[i].SetStartingPoint(points_[i]);
		lines[i].SetEndingPoint(points_[i+1]);
		
		lines[i].SetColor(GetColor());
	}
	
	// Die erzeugten Linien, aus denen das Polygon besteht, zeichnen!
	for(unsigned int i = 0; i < countLines; i++) {
		lines[i].Draw(img);
	}

	// aufraeumen
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
