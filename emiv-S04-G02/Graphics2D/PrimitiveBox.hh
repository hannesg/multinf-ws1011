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
	/* creates empty box */
	PrimitiveBox() { Init(Coordinate(0, 0), Coordinate(0, 0), Color::black()); }

	/* constructors for convenience */
	PrimitiveBox(const Coordinate &c1, const Coordinate &c2) { Init(c1, c2, Color::black()); }
	PrimitiveBox(int x1, int y1, int x2, int y2) { Init(Coordinate(x1, y1), Coordinate(x2, y2), Color::black()); }
	PrimitiveBox(const Coordinate &c1, const Coordinate &c2, const Color &c) { Init(c1, c2, c); }
	PrimitiveBox(int x1, int y1, int x2, int y2, const Color &c) { Init(Coordinate(x1, y1), Coordinate(x2, y2), c); }

	/* setters and getters, for convenience */

	void SetTopLeft(const Coordinate &c) { Init(c, points_[2], GetColor()); }
	void SetBottomRight(const Coordinate &c) { Init(points_[0], c, GetColor()); }

	Coordinate GetTopLeft() const { return points_[0]; }
	Coordinate GetBottomRight() const { return points_[2]; }

	void SetTopLeft(int x, int y) { SetTopLeft(Coordinate(x, y)); }
	void SetBottomRight(int x, int y) { SetBottomRight(Coordinate(x, y)); }

	void Set(const Coordinate &c1, const Coordinate &c2) { Init(c1, c2, GetColor()); }
	void Set(int x1, int y1, int x2, int y2) { Init(Coordinate(x1, y1), Coordinate(x2, y2), GetColor()); }
	
	/* SetCoordinates, zum Setzen der Koordinaten (ueberschrieben) */
	virtual void SetCoordinates(const vector<Coordinate> &points);

	/* Draw-Funktion */
	virtual void Draw(ImageBase *img) const;

private:
	// Initialisation function, called by constructors 
	void Init(const Coordinate &c1, const Coordinate &c2, const Color &c);

};

}
#endif
