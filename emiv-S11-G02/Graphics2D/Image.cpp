/*
Gruppe: 02
Serie 02
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <fstream>
#include <sstream>
#include <string.h>
#include <stdexcept>
#include "Image.hh"

using namespace std;

namespace Graphics2D {

Image::Image() : ImageBase::ImageBase() {
}

Image::Image(const Image &other) : ImageBase::ImageBase(other) {
}

Image &Image::operator=(const Image &other) {
	ImageBase::operator=(other);
	return *this;
}

Image::~Image() {
}

void Image::FillZero() {
	if(!Valid()) {
		throw exception();
	}
	/* Alle Pixel durchgehen und jeden Channel auf 0 setzen */
	for(unsigned int i = 0; i < width_; i++) {
		for(unsigned int j = 0; j < height_; j++) {
			SetPixel(i, j, 0, 0);
			SetPixel(i, j, 1, 0);
			SetPixel(i, j, 2, 0);
		}
	}
}

void Image::FillColor(const Color &c) {
	if(!Valid()) {
		throw exception();
	}
	/* Alle Pixel durchgehen und jeden Channel auf die entsprechende Farbe setzen */
	for(unsigned int i = 0; i < width_; i++) {
		for(unsigned int j = 0; j < height_; j++) {
			SetPixel(i, j, 0, c.GetR());
			SetPixel(i, j, 1, c.GetG());
			SetPixel(i, j, 2, c.GetB());
		}
	}
}

void Image::SetPixel(const int &x, const int &y, const int &ch, const unsigned char &value) {
	if(!Valid()) {
		throw exception();
	}
	/* Gueltige Parameter? */
	if(x >= 0 && y >= 0 && ch >= 0 && ch < 3 && (unsigned)x < width_ && (unsigned)y < height_) {
		data_[(width_*y + x)*3+ch] = value;
	} else {
		stringstream str; 
		str << "Index out of range " << x << " " << y << " " << ch << ", " << width_ << " " << height_;
		throw out_of_range(str.str());
	}
}

unsigned char Image::GetPixel(const int &x, const int &y, const int &ch) const {
	if(!Valid()) {
		throw exception();
	}
	/* Gueltige Parameter? */
	if(x >= 0 && y >= 0 && ch >= 0 && ch < 3 && (unsigned)x < width_ &&  (unsigned)y < height_) {
		return data_[(width_*y + x)*3+ch];
	} else {
		stringstream str; 
		str << "Index out of range " << x << " " << y << " " << ch << ", " << width_ << " " << height_;
		throw out_of_range(str.str());
	}
}

int Image::LoadPPM(const std::string &filename) {
	
	ifstream in;

	/* Open file (binary!) */
	in.open(filename.c_str(), ios_base::binary);

	if(!in) {
		in.close();
		return -1;
	}

	/* Header einlesen */

	bool Binary;
	int width;
	int height;
	unsigned int max;

	if(!readHeader(in, Binary, width, height, max)) {
		in.close();
		return -1;
	}

	/* Bild initialisieren */
	Init(width, height);

	/* in ist jetzt auf der Position des ersten Daten-Bytes */

	/* Datei lesen */
	for(unsigned int y = 0; y < height_; y++) {
		for(unsigned int x = 0; x < width_; x++) {
			for(int i = 0; i < 3; i++) {
				/* Fehler? */
				if(!in || in.eof()) {
					in.close();
					return -1;
				}

				unsigned char c; /* Haelt die Daten */

				if(Binary) {
					/* Binaere Eingabe */
					c = in.get();

					/* Fehler? */
					if(!in) {
						in.close();
						return -1;
					}

				} else {
					/* ASCII-Eingabe */

					unsigned int number;
					
					in >> number;

					/* ungueltige Nummer? */
					if(!in || number > max) {
						in.close();
						return -1;
					}

					/* Konvertieren */
					c = (unsigned char)number;
				}

				/* Pixel faerben */
				SetPixel(x, y, i, c);
			}
		}
	}

	in.close();

	/* Erfolg */
	return 0;
}

bool Image::readHeader(ifstream &in, bool &Binary, int &width, int &height, unsigned int &max)
{
	const int maxLineLength = 100;
	char line[maxLineLength+1]; 

	/* Erste Zeile */
	in.getline(line, maxLineLength);
	/* remove windows line ending. 
	 * benoetigt, wenn die Datei von einem Windows-System stammt, da die
	 * Datei im BINARY Mode geoeffnet wird, und daher das '\r' mitgelesen wird
	 * (Windows line ending: "\r\n", unix line ending: "\n") */
	if(line[strlen(line)-1] == '\r') {
		line[strlen(line)-1] = '\0';
	}

	if(!in || in.eof()) {
		return false;
	}

	/* Welches Format? */
	if(strcmp(line, "P3") == 0) {
		Binary = false;
	} else if(strcmp(line, "P6") == 0) {
		Binary = true;
	} else { 
		/* Ungueltiges Format */
		return false;
	}

	/* Zweite Zeile */

	while(in.peek() == '#') {
		/* Kommentar, noch eine Zeile einlesen */
		in.getline(line, maxLineLength);

		// Windows line ending entfernen
		if(line[strlen(line)-1] == '\r') {
			line[strlen(line)-1] = '\0';
		}

		if (strcmp(line, "# cm_RGB")==0) {
			colormodel_ = cm_RGB;
		} else if (strcmp(line, "# cm_Grey")==0) {
			colormodel_ = cm_Grey;
		} else if (strcmp(line, "# cm_HSV")==0) {
			colormodel_ = cm_HSV;
		}

		// cout << "Colormodel: " << (colormodel_ == cm_RGB ? " rgb " : "grey/hsv") << endl;
	}

	if(!in || in.eof()) {
		return false;
	}

	/* Drei Zahlen einlesen */
	in >> width >> height >> max;

	/* Noch bis zum Anfang der naechsten Zeile, wo die Daten anfangen, 
	   lesen */
	in.getline(line, maxLineLength);

	if(!in || in.eof()) {
		return false;
	}

	return true;
}

int Image::SavePPM(const std::string &filename) const {
	
	if( !this->Valid() ){
		/* keine Daten zum schreiben */
		return 1;
	}

	ofstream out;
	
	/* Open file (binary!!!) */
	out.open(filename.c_str(), ios_base::binary);
	
	if(!out) {
		return -1;
	}
	
	/* Header schreiben */
	out << "P6" << endl;

	switch (colormodel_) {
	case cm_Grey:
		out << "# cm_Grey" << endl;
		break;
	case cm_RGB:
		out << "# cm_RGB" << endl;
		break;
	case cm_HSV:
		out << "# cm_HSV" << endl;
		break;
	default:
		out << "# mip" << endl;
		break;
	}
	
	out << width_ << endl;
	out << height_ << endl;
	out << "255" << endl;
	
	/* Daten schreiben */
	
	/* Alle Pixel Stueck fuer Stueck ausgeben (nicht einfach out << data_ verwenden, 
	 * da sonst beim ersten '\0'-Zeichen aufgehoehrt wird) */
	for(unsigned int y = 0; y < height_; y++) {
		for(unsigned int x = 0; x < width_; x++) {
			for(unsigned int k = 0; k < 3; k++) {
				out.put(GetPixel(x, y, k));
			}
		}
	}

	out.close();
	
	return 0;
}

} 
