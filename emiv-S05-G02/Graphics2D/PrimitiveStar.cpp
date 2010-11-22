/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <cassert>
#include "PrimitiveStar.hh"

using namespace std;

namespace Graphics2D {

void PrimitiveStar::Draw(ImageBase *img) const {
	PrimitivePolygon::Draw(img);
}

void PrimitiveStar::Init(const Coordinate &c, float innerRadius, float outerRadius) {

	points_.clear();

	center_ = c;
	innerRadius_ = innerRadius;
	outerRadius_ = outerRadius;

	Coordinate outPoint = c + Coordinate(outerRadius, 0);
	Coordinate inPoint = c + Coordinate(innerRadius, 0);
	
	outPoint.Rotate(center_, -M_PI/8);

	for(int i = 0; i < 8; i++) {
		points_.push_back(outPoint);
		points_.push_back(inPoint);

		outPoint.Rotate(center_, M_PI/4);
		inPoint.Rotate(center_, M_PI/4);
	}
}


} 
