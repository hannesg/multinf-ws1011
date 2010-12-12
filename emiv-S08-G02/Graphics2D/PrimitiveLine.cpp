/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include "PrimitiveLine.hh"

namespace Graphics2D {

void PrimitiveLine::Init(const Coordinate &c1, const Coordinate &c2, const Color &c) {
	points_.push_back(c1);
	points_.push_back(c2);
	SetColor(c);
}

void PrimitiveLine::Draw(ImageBase *img) const
{
	DrawLine(img,points_[0],points_[1]);
}

/* Fuehrt die Ruecktransformation von durch den Bresenham-Algorithmus bestimmten Koordinaten durch */
Coordinate PrimitiveLine::DrawLineTranslateCoordinates(const Coordinate &base, const int x , const int y ,const char orthant) const {
	Coordinate result(x,y);

	if( orthant & 1 ){
		result.SetX(y);
		result.SetY(x);
	}
	if( orthant & 2 ){
		result.SetX(-result.GetX());
	}
	if( orthant & 4 ){
		result.SetY(-result.GetY());
	}
	result.SetX( result.GetX() + base.GetX() );
	result.SetY( result.GetY() + base.GetY() );
	return result;
}

/*
 * Das ist die Standart Bresenham-Algorithmus.
 * Die Lage der Punkte wird nicht geprüft, sondern davon ausgegangen, dass dies schon passiert ist.
 * Die Angabe des Orthanden und der Basis dient der Translation der Koordinaten.
 */
void PrimitiveLine::DrawLineBresenham(ImageBase *img, const Coordinate &to,const char orthant, const Coordinate &offset) const {
	int deltaX = to.GetX();
	int deltaY = to.GetY();
	int e= 2*deltaY - deltaX;
	int x = 0;
	int y = 0;
	Coordinate coord;
	while( x <= deltaX ){
		/* Ruecktransformation der Koordinaten */
		coord = DrawLineTranslateCoordinates(offset,x,y,orthant);

		/* Pixel zeichnen (wenn Koordinaten im Bild) */
		if(coord.GetX() >= 0 && (unsigned)coord.GetX() < img->GetWidth() 
			&& coord.GetY() >= 0 && (unsigned)coord.GetY() < img->GetHeight()) {
			img->SetPixel(coord.GetX(),coord.GetY(),0,GetColor().GetR());
			img->SetPixel(coord.GetX(),coord.GetY(),1,GetColor().GetG());
			img->SetPixel(coord.GetX(),coord.GetY(),2,GetColor().GetB());
		}

		/* Gemaess Bresenham-Algorithmus bestimmen, ob das Pixel rechts vom 
		 * vorigen Pixel oder rechtsoben vom vorigen Pixel gesetzt werden muss */
		if( e > 0 ){
			y++;
			e += 2*(deltaY - deltaX);
		}else{
			e += 2*deltaY;
		}
		x++;
	}
}
/*
 * Diese Funktion bereitet die Parameter für die Bresenhamfunktion vor.
 */
void PrimitiveLine::DrawLine(ImageBase *img, const Coordinate &c1, const Coordinate &c2) const {
	int dX = (c2.GetX() - c1.GetX());
	int dY = (c2.GetY() - c1.GetY());
	char orthant = 0;
	/* Transformationen bestimmen und Informationen darueber fuer die Ruecktransformation 
	 * in orthant speichern */
	if( dY < 0 ){
		orthant |= 4;
		dY = -dY;
	}
	if( dX < 0 ){
		orthant |= 2;
		dX = -dX;
	}
	if( dY > dX ){
		orthant |= 1;
		int z=dX;
		dX = dY;
		dY = z;
	}
	DrawLineBresenham(img,Coordinate(dX,dY),orthant,c1);
}

int PrimitiveLine::getXValue(float y0) const {
		int x1 = points_[0].GetX();
		int x2 = points_[1].GetX();
		int y1 = points_[0].GetY();
		int y2 = points_[1].GetY();

		// nicht durch Null dividieren!
		if(y2 == y1) { throw exception(); }

		return x1 + (int)rint(
			((y0-y1)*(x2-x1))/(float)(y2-y1));
}

}
