/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include "Painter.hh"
#include "PrimitiveLine.hh"
#include "BackgroundImage.hh"
#include "ColorConversion.hh"
#include "Histogram.hh"

using namespace std;

namespace Graphics2D {

Painter::Painter(const Image &backgroundImage) 
	: pointModusController_(*this), 
	lineModusController_(*this), 
	boxModusController_(*this), 
	polygonModusController_(*this), 
	starModusController_(*this)
{

	currentColor_ = Color::black();

	// Das Hintergrundbild hinzufuegen
	backgroundOriginal_ = new BackgroundImage(backgroundImage);
	
	// Graubild erstellen
	Image greyPicture;
		
	ColorConversion::ToGrey(backgroundOriginal_->GetImage(), greyPicture);
	backgroundGrey_ = new BackgroundImage(greyPicture);

	// Bild mit besserem Kontrast erstellen
	Image betterContrastPicture;
	Histogram::Autocontrast(backgroundOriginal_->GetImage(),betterContrastPicture);
	backgroundBetterContrast_ = new BackgroundImage(betterContrastPicture);
	
	// Modus am Start ist Punkte zeichnen
	currentController_ = NULL;
	SetModus(POINT);

	currentBGModus_ = BG_ORIGINAL;
	currentHistogramModus_ = HM_NONE;

	pause_ = false;
}

Painter::~Painter() {

	// Aufraeumen
	RemoveAllPrimitives();

	delete backgroundOriginal_;
	delete backgroundGrey_;
	delete backgroundBetterContrast_;
}

void Painter::Draw() {

	vector<PrimitiveBase *>::iterator it;
	
	// Hintergrundbild auswaehlen und zeichnen
	BackgroundImage *currentImage;

	switch(currentBGModus_) {
	case BG_ORIGINAL:
		currentImage = backgroundOriginal_;
		break;
	case BG_GREY:
		currentImage = backgroundGrey_;
		break;
	case BG_BETTER_CONTRAST:
		currentImage = backgroundBetterContrast_;
		break;
	}
	
	currentImage->Draw(image_);

	/* Alle Elemente durchgehen */
	for(it = primitives_.begin(); it != primitives_.end(); it++) {
		if(!pause_) {
			// rotieren
			(*it)->Rotate(2*M_PI/100);
		}
		(*it)->Draw(image_);
	}
	
	/* Histogramme zeichnen */
	if( currentHistogramModus_ == HM_RGB ) {
		Image image = currentImage->GetImage();

		int y=0;
		int histogramHeight = image.GetHeight()/3;

		for( int channel=0; channel<3; channel++ ){
			/* Jedes Histogramm entsprechend seiner Farbe faerben */
			Color color(channel==0 ? 255 : 0, channel==1 ? 255 : 0 , channel==2 ? 255 : 0);

			Histogram hist( Coordinate(0,y), Coordinate(image.GetWidth(),histogramHeight),color);
			hist.FromImage(image,channel);
			hist.Draw(image_);

			y+= histogramHeight;
		}
	} else if( currentHistogramModus_ == HM_HSV ) {
		Image image;
		// Konversion durchfuehren
		ColorConversion::ToHSV(currentImage->GetImage(),image);

		int y=0;
		int histogramHeight = image.GetHeight()/3;

		/* Die drei Histogramme ausgeben */
		for( int channel=0; channel<3; channel++ ) {
			Color color(channel * 127 , channel * 127 , channel * 127);

			Histogram hist( Coordinate(0,y), Coordinate(image.GetWidth(),histogramHeight),color);
			hist.FromImage(image,channel);
			hist.Draw(image_);

			y+= histogramHeight;
		}
	}

	/* Auch die temporaeren Elemente durchgehen */
	const vector<PrimitiveBase *> &temps = currentController_->GetTemporaryPrimitives();
	vector<PrimitiveBase *>::const_iterator itc;

	for(itc = temps.begin(); itc != temps.end(); itc++) {
		(*itc)->Draw(image_);
	}
}

void Painter::UpdateHistogramModus() {
	switch( currentHistogramModus_ ){
	case HM_NONE:
		currentHistogramModus_ = HM_RGB;
		break;
	case HM_RGB:
		currentHistogramModus_ = HM_HSV;
		break;
	case HM_HSV:
		currentHistogramModus_ = HM_NONE;
		break;
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
	case BOX:
		return "Rechteck";
		break;
	case POLYGON:
		return "Polygon";
		break;
	case STAR:
		return "Stern";
		break;
	default:
		return "";
	}
}

void Painter::MouseDown(int x, int y) {
	// cout << "d" << flush;

	// Weiterleiten 
	currentController_->MouseDown(x, y);
}

void Painter::MouseUp(int x, int y) {
	// cout << "u" << flush;

	// Weiterleiten 
	currentController_->MouseUp(x, y);
}

void Painter::MouseMove(int x, int y) {
	// cout << "m" << flush;

	// Weiterleiten 
	currentController_->MouseMove(x, y);
}

void Painter::KeyPressed(unsigned char ch, int x, int y) {
	
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
	case 'g':
		UpdateHistogramModus();
		break;
	case 'p':
		SetModus(POINT);
		break;
	case 'l':
		SetModus(LINE);
		break;
	case 'r':
		SetModus(BOX);
		break;
	case 'y':
		SetModus(POLYGON);
		break;
	case 's':
		SetModus(STAR);
		break;
	case 'h':
		PrintHelp();
		break;
	case '.':
		pause_ = !pause_;
		break;
	case 'c':
		if(currentBGModus_ == BG_GREY) {
			currentBGModus_ = BG_ORIGINAL;
		} else {
			currentBGModus_ = BG_GREY;
		}
		break;
	case 'k':
		if(currentBGModus_ == BG_BETTER_CONTRAST) {
			currentBGModus_ = BG_ORIGINAL;
		} else {
			currentBGModus_ = BG_BETTER_CONTRAST;
		}
		break;
	case ' ':
		printColor(x, y);
		break;
	case 'x':
		ConvertBackgroundImage();
		break;
	case 'm':
		printMinMaxVChannel();
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
	case BOX:
		currentController_ = &boxModusController_;
		break;
	case POLYGON:
		currentController_ = &polygonModusController_;
		break;
	case STAR:
		currentController_ = &starModusController_;
	// Hier mehr Controller hinzufuegen
	default:
		break;
	}

	// Neuen Modus aktivieren
	currentController_->Activate();
}

void Painter::PrintHelp() const {
	cout << "1 bis 4 stehen fuer die verschiedenen Farben Schwarz, Rot, Gruen, Blau. " << endl;
	cout << "Weitere Kuerzel fuer Auswahl der verschiedenen Modi: " << endl;
	cout << " p: Punkte" << endl;
	cout << " l: Linien" << endl;
	cout << " r: Rechteck" << endl;
	cout << " y: Polygon" << endl;
	cout << " s: Stern" << endl;
	cout << "Im Polygonmodus muss fuer jeden Punkt des Polygons geklickt werden (also " << endl;
	cout << " Maustaste druecken *und* wieder loslassen). " << endl;
	cout << "'.' pausiert die Rotationsanimation. " << endl;
	cout << "h druckt diese Hilfe aus" << endl;
	cout << "c toggelt Graubild/Originalbild" << endl;
	cout << "k togglet Orignalbild/Bild mit besserem Kontrast" << endl;
	cout << "g Histogram durchschalten ( Keins -> RGB -> HSV )" << endl;
	cout << "Leertaste zeigt aktuellen Wert unter Cursor an" << endl;
	cout << "x fuer Hin- und Rueckkonvertieren von Bild nach HSV und zurueck nach RGB" << endl;
	cout << " Dies wird 50 mal durchgefuehrt. Wenn danach das Bild immer noch gleich" << endl;
	cout << " aussieht, sind die Konvertierungsfunktionen hoechstwahrscheinlich korrekt. " << endl;
	cout << "m gibt maximalen und minimalen Helligkeitswert des V-Kanals aus" << endl;
}

void Painter::printColor(int x, int y) const
{
	int r = image_->GetPixel(x, y, 0);
	int g = image_->GetPixel(x, y, 1);
	int b = image_->GetPixel(x, y, 2);

	cout << r << " " << g << " " << b << endl;	
}

void Painter::ConvertBackgroundImage() {
	Image tmp;

	// wie oft konvertieren?
	const int n = 50;

	for(int i = 1; i <= n; i++) {
		ColorConversion::ToHSV(backgroundOriginal_->GetImage(), tmp);

		ColorConversion::ToRGB(tmp, backgroundOriginal_->GetImage());
		if(i % 1 == 0) {
			cout << i*100/n << "%" << endl;
		}
	}
}

void Painter::printMinMaxVChannel() const {
	// Minimalen und Maximalen Helligkeitswert des V-Kanals ausgeben 
	// fuer Aufgabe 2b)

	Image img;
	BackgroundImage *currentImage = NULL;

	switch(currentBGModus_) {
	case BG_ORIGINAL:
		currentImage = backgroundOriginal_;
		break;
	case BG_BETTER_CONTRAST:
		currentImage = backgroundBetterContrast_;
		break;
	case BG_GREY:
		currentImage = backgroundGrey_;
		break;
	}

	ColorConversion::ToHSV(currentImage->GetImage(), img);

	Histogram hist;
	hist.FromImage(img, 2);

	cout << "Minimum: " << hist.Min() << ", Maximum: " << hist.Max() << endl;
}

}
