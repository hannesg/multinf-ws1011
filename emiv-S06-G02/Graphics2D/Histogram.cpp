/*
 * Histogram.cpp
 *
 *  Created on: Nov 30, 2010
 *      Author: hannes
 */

#include "Histogram.hh"
#include <vector>

namespace Graphics2D {

Histogram::Histogram(): histogram_(256,0) {
}

Histogram::Histogram(const Coordinate &c1, const Coordinate &c2, const Color &c): histogram_(256,0) {
	Init(c1, c2, c);
}
void Histogram::Init(const Coordinate &c1, const Coordinate &c2, const Color &c){
	points_.push_back(c1);
	points_.push_back(c2);
	SetColor(c);
}

Histogram::~Histogram() {
	
}

int Histogram::Min() const {
	int size = histogram_.size();
	for( int i = 0; i < size; i++ ){
		if( histogram_[i] != 0 ){
			return i;
		}
	}
	return -1;
}

int Histogram::Max() const {
	int size = histogram_.size();
	for( int i = size-1; i >= 0; i-- ){
		if( histogram_[i] != 0 ){
			return i;
		}
	}
	return -1;
}

int Histogram::MaxValue() const {
	int size = histogram_.size();
	int max = 0;
	for( int i = size-1; i >= 0; i-- ){
		if( histogram_[i] > max ){
			max = histogram_[i];
		}
	}
	return max;
}

int Hisogram::MinValue() const {
	int size = histogram_.size();
	int min = histogram_[0];

	for(int i = 1; i < size; i++) {
		if (histogram_[i] < min) {
			min = histogram_[i];
		}
	} 
	return min;
}

void Histogram::Autocontrast(const Image &src, Image &dest){
	Histogram hist;
	Image imgHSV;

	/* Umwandlung des Quellbildes nach HSV */
	ColorConversion::ToHSV(src,imgHSV);
	hist.FromImage(imgHSV,2);

	/* Minimal- und Maximalwerte aus Histogramm bestimmen */
	int min = hist.Min(), max = hist.Max();

	// calculate mapping parameters
	float a = ((float) 255) / (max - min);
	float b = -( min * a );

	int w = src.GetWidth(), h = src.GetHeight();

	// Temporaeres Bild anlegen
	Image temp;
	temp.Init(w,h);
	temp.SetColorModel(ImageBase::cm_HSV);

	// Punktoperation durchfuehren
	int v;
	for( int y = 0; y < h ; y ++ ){
		for( int x = 0; x < w ; x++ ){

			// Hue und Saturation bleiben gleich
			temp.SetPixel(x,y,0,imgHSV.GetPixel(x,y,0));
			temp.SetPixel(x,y,1,imgHSV.GetPixel(x,y,1));

			// Skalierung durchfuehren
			v = a * imgHSV.GetPixel(x,y,2) + b;

			/* Ausreisser abfangen */
			if( v > 255 ){
				v = 255;
			}else if( v < 0 ){
				v = 0;
			}

			// Wert speichern
			temp.SetPixel(x,y,2,v);
		}
	}

	// Wieder in RGB umwandeln
	ColorConversion::ToRGB(temp, dest);
}

void Histogram::Draw(Graphics2D::ImageBase* image) const {
	const vector<Coordinate> &coords = GetCoordinates();

	Coordinate top_left = coords.front();
	Coordinate bottom_right = coords.back();

	/* Breite eines Balken berechnen */
	float barWidth = (bottom_right.GetX() - top_left.GetX()) / 256.0;
	float height = bottom_right.GetY() - top_left.GetY();
	float barHeight;

	/* Skalierungsfaktor */
	float s = height / log10(MaxValue()+1);

	float x = top_left.GetX();
	float y = bottom_right.GetY();

	/* Histogrammelemente durchgehen und Histogramm zeichnen */
	for( int i=0; i < 256; i++ ){
		if( histogram_[i] != 0 ){
			barHeight = s * log10(histogram_[i]+1);

			// Rechteck zeichnen mit entsprechender Hoehe
			PrimitiveBox box( x,y-barHeight ,x+barWidth,y, GetColor() );
			box.Draw(image);
		}
		x += barWidth;
	}
}

int Histogram::FromImage(const Image& image, const int channel){
	if( image.Valid() ){
		int w = image.GetWidth(), h = image.GetHeight();
		/* Bild durchlaufen */
		for(int y = 0; y < h ; y++ ){
			for(int x = 0; x < w ; x++ ){
				/* jeweiligen Wert im Histogramm erhoehen */
				histogram_[ image.GetPixel(x,y,channel) ]++;
			}
		}
		return 0;
	}else{
		return 1;
	}
}

}
