/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include "Painter.hh"
#include "PrimitiveLine.hh"

using namespace std;

namespace Graphics2D {

Painter::Painter() {
	currentColor_ = Color::black();

	// Zum Test
	PrimitiveLine *l1 = new PrimitiveLine(0, 0, 10, 10);
	PrimitiveLine *l2 = new PrimitiveLine(10, 0, 0, 10);

	AddPrimitive(l1);
	AddPrimitive(l2);

	// Modus am Start ist Punkte zeichnen
	currentModus_ = POINT;
}

Painter::~Painter() {

	// Aufraeumen
	RemoveAllPrimitives();
	RemoveAllTemporaryPrimitives();
}

void Painter::Draw() {

	vector<PrimitiveBase *>::iterator it;

	/* Alle Elemente durchgehen */
	for(it = primitives_.begin(); it != primitives_.end(); it++) {
		(*it)->Draw(image_);
	}

	/* Auch die temporaeren Elemente durchgehen */
	for(it = tempPrimitives_.begin(); it != tempPrimitives_.end(); it++) {
		(*it)->Draw(image_);
	}
}

void Painter::AddPrimitive(PrimitiveBase *p)
{
	// Hier werden wirklich auch Pointer benoetigt!
	primitives_.push_back(p);
}

void Painter::RemoveAllPrimitives() {
	vector<PrimitiveBase *>::iterator it;

	// Alle Primitives loeschen
	for(it = primitives_.begin(); it != primitives_.end(); it++) {
		delete *it;
	}

	// Liste leeren
	primitives_.clear();
}

void Painter::AddTemporaryPrimitive(PrimitiveBase *p) {
	tempPrimitives_.push_back(p);
}

void Painter::RemoveAllTemporaryPrimitives() {
	vector<PrimitiveBase *>::iterator it;

	// Alle temporaere Primitives loeschen
	for(it = tempPrimitives_.begin(); it != tempPrimitives_.end(); it++) {
		delete *it;
	}

	// Liste leeren
	tempPrimitives_.clear();
}

PrimitiveBase *Painter::GetTemporaryPrimitive(int i) {
	return tempPrimitives_[i];
}

string Painter::GetColorString() {
	return currentColor_.GetName();
}

string Painter::GetString() {
	switch(currentModus_) {
	case LINE:
		return "Linien";
		break;
	case POINT:
		return "Punkte";
		break;
	default:
		return "";
	}
}

void Painter::MouseDown(int x, int y) {
	cerr << "MouseDown " << x << " " << y << endl;
}

void Painter::MouseUp(int x, int y) {
	cerr << "MouseUp " << x << " " << y << endl;
}

void Painter::MouseMove(int x, int y) {
	cerr << "MouseMove " << x << " " << y << endl;
}

void Painter::KeyPressed(unsigned char ch, int x, int y) {
	cerr << "KeyPressed " << ch << " " << x << " " << y << endl;
	switch(ch) {
	case '1':
		currentColor_ = Color::black();
		break;
	case '2':
		currentColor_ = Color::red();
		break;
	case '3':
		currentColor_ = Color::green();
		break;
	case '4':
		currentColor_ = Color::blue();
		break;
	case 'p':
		currentModus_ = POINT;
		break;
	case 'l':
		currentModus_ = LINE;
		break;
	case 'h':
		PrintHelp();
		break;
	default:
		break;
	}
}

void Painter::PrintHelp() {
	cout << "1 bis 4 stehen fuer die verschiedenen Farben Schwarz, Rot, Gruen, Blau. " << endl;
	cout << "Weitere Kuerzel fuer Auswahl der verschiedenen Modi: " << endl;
	cout << " p: Punkte" << endl;
	cout << " l: Linien" << endl;
	cout << "h druckt diese Hilfe aus" << endl;
}

}