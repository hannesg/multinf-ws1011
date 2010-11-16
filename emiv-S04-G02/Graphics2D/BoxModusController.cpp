/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/


#include <cassert>
#include "BoxModusController.hh"
#include "Painter.hh"
#include "PrimitiveLine.hh"

using namespace std;

namespace Graphics2D {

void BoxModusController::Activate() {

	pressed_ = false;
}

void BoxModusController::Deactivate() {
	// Aufrauemen (loescht auch automatisch die hier in der Klasse
	// erzeugten Zeiger)! 
	RemoveAllTemporaryPrimitives();

	pressed_ = false;
}

void BoxModusController::MouseDown(int x, int y) {

	pressed_ = true;

	// Startpunkt merken
	startingPoint_.Set(x, y);

	// Temporaeres Rechteck erzeugen
	// oben
	tempPrimitives_.push_back(new PrimitiveLine(startingPoint_, startingPoint_, myPainter_.GetCurrentColor()));
	// links
	tempPrimitives_.push_back(new PrimitiveLine(startingPoint_, startingPoint_, myPainter_.GetCurrentColor()));
	// rechts
	tempPrimitives_.push_back(new PrimitiveLine(startingPoint_, startingPoint_, myPainter_.GetCurrentColor()));
	// unten
	tempPrimitives_.push_back(new PrimitiveLine(startingPoint_, startingPoint_, myPainter_.GetCurrentColor()));
}

void BoxModusController::MouseUp(int x, int y)  {

	if(pressed_) {
		pressed_ = false;

		// Das Rechteck endgueltig hinzufuegen
		// TODO! 
		// myPainter_.AddPrimitive(new PrimitiveBox(startingPoint_, Coordinate(x, y), myPainter_.GetCurrentColor()));

		// Temporaere Objekte loeschen
		RemoveAllTemporaryPrimitives();
	}
}

void BoxModusController::MouseMove(int x, int y)  {

	// Das temporaere Rechteck verschieben
	if(pressed_ && tempPrimitives_.size() == 4) {

		PrimitiveLine *top = dynamic_cast<PrimitiveLine *>(tempPrimitives_[0]);
		PrimitiveLine *left = dynamic_cast<PrimitiveLine *>(tempPrimitives_[1]);
		PrimitiveLine *right = dynamic_cast<PrimitiveLine *>(tempPrimitives_[2]);
		PrimitiveLine *bottom = dynamic_cast<PrimitiveLine *>(tempPrimitives_[3]);

		assert(top != NULL && left != NULL && right != NULL && bottom != NULL);

		top->SetEndingPoint(x, startingPoint_.GetY());
		left->SetEndingPoint(startingPoint_.GetX(), y);

		right->SetStartingPoint(x, startingPoint_.GetY());
		right->SetEndingPoint(x, y);

		bottom->SetStartingPoint(startingPoint_.GetX(), y);
		bottom->SetEndingPoint(x, y);
	}

}

}