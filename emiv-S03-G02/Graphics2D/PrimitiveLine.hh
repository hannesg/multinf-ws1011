#ifndef __PRIMITIVE_LINE_HH
#define __PRIMITIVE_LINE_HH

#include "PrimitiveBase.hh"
#include "ImageBase.hh"

namespace Graphics2D {

class PrimitiveLine : public PrimitiveBase
{
public:
	/* constructors */

	/* creates a line from origin to the origin, that is, an "empty" line */
	PrimitiveLine();

	/* creates a line from c1 to c2 */
	PrimitiveLine(Coordinate c1, Coordinate c2);

	/* creates a line from (x1, y1) to (x2, y2)  */
	PrimitiveLine(int x1, int y1, int x2, int y2);


	/* Draw-Funktion */
	virtual void Draw(ImageBase *img) const;


protected:
	/* Anzahl der erlaubten Punkte */
	virtual int GetNumberOfPointsAllowed() const { return 2; }

};

}





#endif