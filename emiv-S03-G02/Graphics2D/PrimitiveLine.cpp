
#include "PrimitiveLine.hh"

namespace Graphics2D {

PrimitiveLine::PrimitiveLine() {
	/* creates a line from origin to the origin, that is, an "empty" line */
	points_.push_back(Coordinate(0, 0));
	points_.push_back(Coordinate(0, 0));
}

PrimitiveLine::PrimitiveLine(const Coordinate &c1, const Coordinate &c2) {
	points_.push_back(c1);
	points_.push_back(c2);
}

PrimitiveLine::PrimitiveLine(int x1, int y1, int x2, int y2) {
	points_.push_back(Coordinate(x1, y1));
	points_.push_back(Coordinate(x2, y2));
}

void PrimitiveLine::Draw(ImageBase *img) const
{
	/* to be implemented */
}


}