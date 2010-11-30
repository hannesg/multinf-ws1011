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
	// TODO Auto-generated destructor stub
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

void Histogram::Autocontrast(const Image &src, Image &dest){
	Histogram hist;
	Image imgHSV;

	ColorConversion::ToHSV(src,imgHSV);
	hist.FromImage(imgHSV,2);
	int min = hist.Min(), max = hist.Max();
	// calculate mapping parameters
	float a = ((float) 255) / (max - min);
	float b = -( min * a );
	int w = src.GetWidth(), h = src.GetHeight();

	Image temp;
	temp.Init(w,h);
	temp.SetColorModel(ImageBase::cm_HSV);

	int v;
	for( int y = 0; y < h ; y ++ ){
		for( int x = 0; x < w ; x++ ){
			temp.SetPixel(x,y,0,imgHSV.GetPixel(x,y,0));
			temp.SetPixel(x,y,1,imgHSV.GetPixel(x,y,1));
			v = a * imgHSV.GetPixel(x,y,2) + b;
			if( v > 255 ){
				v = 255;
			}else if( v < 0 ){
				v = 0;
			}
			temp.SetPixel(x,y,2,v);
		}
	}

	ColorConversion::ToRGB(temp, dest);
}

void Histogram::Draw(Graphics2D::ImageBase* image) const {;
	vector<Coordinate> coords = GetCoordinates();
	Coordinate top_left = coords.front();
	Coordinate bottom_right = coords.back();
	float barWidth = (bottom_right.GetX() - top_left.GetX()) / (float) 256;
	float height = bottom_right.GetY() - top_left.GetY();
	float barHeight;
	float s = height / log10(MaxValue());
	float x = top_left.GetX();
	float y = bottom_right.GetY();
	for( int i=0; i < 256; i++ ){
		if( histogram_[i] != 0 ){
			barHeight = s * log10(histogram_[i]);
			PrimitiveBox box( x,y-barHeight ,x+barWidth,y, GetColor() );
			box.Draw(image);
		}
		x += barWidth;
	}
}

int Histogram::FromImage(const Image& image, const int channel){
	if( image.Valid() ){
		int w = image.GetWidth(), h = image.GetHeight();
		int x = 0, y = 0;
		for( ; y < h ; y++ ){
			for( ; x < w ; x++ ){
				histogram_[ image.GetPixel(x,y,channel) ]++;
			}
		}
		return 0;
	}else{
		return 1;
	}
}

}
