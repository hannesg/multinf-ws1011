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

	center_ = c;
	innerRadius_ = innerRadius;
	outerRadius_ = outerRadius;

}


} 
