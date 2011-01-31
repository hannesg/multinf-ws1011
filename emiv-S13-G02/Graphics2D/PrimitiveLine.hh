/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef __PRIMITIVE_LINE_HH
#define __PRIMITIVE_LINE_HH

#include "PrimitiveBase.hh"
namespace Graphics2D {

class PrimitiveLine : public PrimitiveBase
{
public:
	/* constructors */

	/* creates a line from origin to the origin, that is, an "empty" line */
	PrimitiveLine() { Init(Coordinate(0, 0), Coordinate(0, 0), Color::black()); }

	/* creates a line from c1 to c2 */
	PrimitiveLine(const Coordinate &c1, const Coordinate &c2) { Init(c1, c2, Color::black()); }
	PrimitiveLine(const Coordinate &c1, const Coordinate &c2, const Color &c) { Init(c1, c2, c); }

	/* creates a line from (x1, y1) to (x2, y2), for convenience  */
	PrimitiveLine(float x1, float y1, float x2, float y2) { Init(Coordinate(x1, y1), Coordinate(x2, y2), Color::black()); }
	PrimitiveLine(float x1, float y1, float x2, float y2, const Color &c) { Init(Coordinate(x1, y1), Coordinate(x2, y2), c); }

	// deconstructor
	virtual ~PrimitiveLine() {}

	/* setters and getters for convenience */
	void SetStartingPoint(const Coordinate &c) { points_[0] = c; }
	void SetStartingPoint(float x, float y) { points_[0] = Coordinate(x, y); }
	void SetEndingPoint(const Coordinate &c) { points_[1] = c; }
	void SetEndingPoint(float x, float y) { points_[1] = Coordinate(x, y); }

	Coordinate GetStartingPoint() const { return points_[0]; }
	Coordinate GetEndingPoint() const { return points_[1]; }

	/* geben die jeweils kleinsten/groessten X/Y-Werte zurueck */
	int GetXMin() const { return (int)rint(min(points_[0].GetX(), points_[1].GetX())); }
	int GetXMax() const { return (int)rint(max(points_[0].GetX(), points_[1].GetX())); }
	int GetYMin() const { return (int)rint(min(points_[0].GetY(), points_[1].GetY())); }
	int GetYMax() const { return (int)rint(max(points_[0].GetY(), points_[1].GetY())); }

	// Gibt den X-Wert des Schnittpunktes mit der Geraden y = y0 zurueck
	int getXValue(float y0) const;

	/* Draw-Funktion */
	virtual void Draw(ImageBase *img) const;

	// computes distance from point to this line
	float Distance(const Coordinate &point) const;

	// computes the intersection with another line
	bool Intersection(const PrimitiveLine &other, Coordinate &intersection) const;


protected:
	/* Anzahl der erlaubten Punkte */
	virtual int GetNumberOfPointsAllowed() const { return 2; }

private:
	/* Initialization function, called from constructors */
	void Init(const Coordinate &c1, const Coordinate &c2, const Color &c);

	/* Hilfsfunktion zum Zeichnen einer Geraden */
	void DrawLine(ImageBase *img, const Coordinate &c1, const Coordinate &c2) const;

	/* Implementiert Bresenham-Algorithmus */
	void DrawLineBresenham(ImageBase *img, const Coordinate &to,const char orthant, const Coordinate &offset) const;

	/* Fuehrt die Ruecktransformation von durch den Bresenham-Algorithmus bestimmten Koordinaten durch */
	Coordinate DrawLineTranslateCoordinates(const Coordinate &base, const int x , const int y ,const char orthant) const;

	friend ostream & operator << (ostream &out, const PrimitiveLine &p);
};

ostream & operator << (ostream &out, const PrimitiveLine &p);

}
#endif
