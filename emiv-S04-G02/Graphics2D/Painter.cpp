/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include "Painter.hh"
#include "PrimitiveLine.hh"
#include "PointModusController.hh"
#include "BackgroundImage.hh"

using namespace std;

namespace Graphics2D {

Painter::Painter(const Image &backgroundImage) 
	: pointModusController_(*this), lineModusController_(*this) {
	currentColor_ = Color::black();

	// Das Hintergrundbild hinzufuegen
	BackgroundImage *img = new BackgroundImage(backgroundImage);
	AddPrimitive(img);

	// Modus am Start ist Punkte zeichnen
	currentController_ = NULL;
	SetModus(POINT);
}

Painter::~Painter() {

	// Aufraeumen
	RemoveAllPrimitives();
}

void Painter::Draw() {

	vector<PrimitiveBase *>::iterator it;

	/* Alle Elemente durchgehen */
	for(it = primitives_.begin(); it != primitives_.end(); it++) {
		(*it)->Draw(image_);
	}

	const vector<PrimitiveBase *> &temps = currentController_->GetTemporaryPrimitives();
	vector<PrimitiveBase *>::const_iterator itc;

	/* Auch die temporaeren Elemente durchgehen */
	for(itc = temps.begin(); itc != temps.end(); itc++) {
		(*itc)->Draw(image_);
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

	// Weiterleiten 
	currentController_->MouseDown(x, y);
}

void Painter::MouseUp(int x, int y) {
	cerr << "MouseUp " << x << " " << y << endl;

	// Weiterleiten 
	currentController_->MouseUp(x, y);
}

void Painter::MouseMove(int x, int y) {
	cerr << "MouseMove " << x << " " << y << endl;

	// Weiterleiten 
	currentController_->MouseMove(x, y);
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
		SetModus(POINT);
		break;
	case 'l':
		SetModus(LINE);
		break;
	case 'h':
		PrintHelp();
		break;
	default:
		break;
	}
}

void Painter::SetModus(Modus m) {
	// Neuen Modus speichern
	currentModus_ = m;

	// Alten Modus deaktivieren
	if(currentController_) {
		currentController_->Deactivate();
	}

	// Neuen Modus zuweisen
	switch(m) {
	case POINT:
		currentController_ = &pointModusController_;
		break;
	case LINE:
		currentController_ = &lineModusController_;
		break;
	// Hier mehr Controller hinzufuegen
	default:
		break;
	}

	// Neuen Modus aktivieren
	currentController_->Activate();
}

void Painter::PrintHelp() {
	cout << "1 bis 4 stehen fuer die verschiedenen Farben Schwarz, Rot, Gruen, Blau. " << endl;
	cout << "Weitere Kuerzel fuer Auswahl der verschiedenen Modi: " << endl;
	cout << " p: Punkte" << endl;
	cout << " l: Linien" << endl;
	cout << "h druckt diese Hilfe aus" << endl;
}

}