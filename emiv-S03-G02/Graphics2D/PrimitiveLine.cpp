
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
	PrimitiveLine::DrawLine(img,points_[0],points_[1],color_);
}

Coordinate PrimitiveLine::DrawLineTranslateCoordinates(const Coordinate &base, const int x , const int y ,const char orthant){
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
void PrimitiveLine::DrawLineBresenham(ImageBase *img, const Coordinate &to,const Color &color,const char orthant, const Coordinate &offset){
	int deltaX = to.GetX();
	int deltaY = to.GetY();
	int e= 2*deltaY - deltaX;
	int x = 0;
	int y = 0;
	Coordinate coord;
	while( x <= deltaX ){
		coord = PrimitiveLine::DrawLineTranslateCoordinates(offset,x,y,orthant);
		img->SetPixel(coord.GetX(),coord.GetY(),0,color.GetR());
		img->SetPixel(coord.GetX(),coord.GetY(),1,color.GetG());
		img->SetPixel(coord.GetX(),coord.GetY(),2,color.GetB());
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
void PrimitiveLine::DrawLine(ImageBase *img, const Coordinate &c1, const Coordinate &c2,const Color &color){
	int dX = (c2.GetX() - c1.GetX());
	int dY = (c2.GetY() - c1.GetY());
	char orthant = 0;
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
	DrawLineBresenham(img,Coordinate(dX,dY),color,orthant,c1);
}



}
