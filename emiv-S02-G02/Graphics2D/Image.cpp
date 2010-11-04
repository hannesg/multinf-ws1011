/*
Gruppe: 02
Serie 02
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <fstream>
#include <string.h>
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
	for(unsigned int i = 0; i < width_; i++) {
		for(unsigned int j = 0; j < height_; j++) {
			SetPixel(i, j, 0, 0);
			SetPixel(i, j, 1, 0);
			SetPixel(i, j, 2, 0);
		}
	}
}

void Image::SetPixel(const int &x, const int &y, const int &ch, const unsigned char &value) {
	if(x >= 0 && x < width_ && y >= 0 && y < height_ && ch >= 0 && ch < 3) {
		data_[(width_*y + x)*3+ch] = value;
	} else {
		throw "Index out of range! ";
	}
}

unsigned char Image::GetPixel(const int &x, const int &y, const int &ch) const {
	if(x >= 0 && x < width_ && y >= 0 && y < height_ && ch >= 0 && ch < 3) {
		return data_[(width_*y + x)*3+ch];
	} else {
		throw "Index out of range! ";
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

	/* Erfolg */
	return 0;
}

bool Image::readHeader(ifstream &in, bool &Binary, int &width, int &height, unsigned int &max) const
{
	const int maxLineLength = 100;
	char line[maxLineLength]; 

	/* Erste Zeile */
	in.getline(line, maxLineLength);

	if(!in || in.eof()) {
		return false;
	}

	if(strcmp(line, "P3") == 0) {
		Binary = false;
	} else if(strcmp(line, "P6") == 0) {
		Binary = true;
	} else { 
		/* Ungueltiges Format */
		return false;
	}

	/* Zweite Zeile */

	if(in.peek() == '#') {
		/* Kommentar, noch eine Zeile einlesen */
		in.getline(line, maxLineLength);
	}

	if(!in || in.eof()) {
		return false;
	}

	/* Drei Zahlen einlesen */
	in >> width >> height >> max;

	/* Noch einen Absatz einlesen */
	in.getline(line, maxLineLength);

	if(!in || in.eof()) {
		return false;
	}

	// cout << "Header read! " << Binary << " " << width << " " << height << " " << max << endl;

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
	
	out << width_ << endl;
	out << height_ << endl;
	out << "255" << endl;
	
	/* Daten schreiben */
	
	out << data_;

	out.close();
	
	return 0;
}

} 
