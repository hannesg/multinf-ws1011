/*
Gruppe: 02
Serie 03
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
	PrimitiveLine(int x1, int y1, int x2, int y2) { Init(Coordinate(x1, y1), Coordinate(x2, y2), Color::black()); }


	/* Draw-Funktion */
	virtual void Draw(ImageBase *img) const;


protected:
	/* Anzahl der erlaubten Punkte */
	virtual int GetNumberOfPointsAllowed() const { return 2; }

private:
	/* Initialization function, called from constructors */
	void Init(const Coordinate &c1, const Coordinate &c2, const Color &c);

	void DrawLine(ImageBase *img, const Coordinate &c1, const Coordinate &c2,const Color &color) const;

	void DrawLineBresenham(ImageBase *img, const Coordinate &to,const Color &color,const char orthant, const Coordinate &offset) const;
	Coordinate DrawLineTranslateCoordinates(const Coordinate &base, const int x , const int y ,const char orthant) const;

};

}
#endif
