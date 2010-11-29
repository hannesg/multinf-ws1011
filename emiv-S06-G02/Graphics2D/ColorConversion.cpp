/*
Gruppe: 02
Serie 06
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <cmath>
#include <cassert>
#include "ColorConversion.hh"

using namespace std;

namespace Graphics2D {

void ColorConversion::ToGrey(const Image &src, Image &dst) {
	
	if(src.GetColorModel() == ImageBase::cm_Grey) {
		// do nothing
		dst = src;
		return;
	} 

	const Image *actualSrc;
	Image converted;

	if (src.GetColorModel() == ImageBase::cm_HSV) {
		ColorConversion::ToRGB(src, converted);
		actualSrc = &converted;
	} else {
		actualSrc = &src;
	}

	dst.Init(actualSrc->GetWidth(), actualSrc->GetHeight());
	dst.SetColorModel(ImageBase::cm_Grey);
	
	unsigned int size = actualSrc->GetWidth()*actualSrc->GetHeight();
	const unsigned char *data = actualSrc->GetData();
	unsigned char *dstData = dst.GetData();

	for(unsigned int i = 0; i < size; i++) {
		int r = data[3*i+0];
		int g = data[3*i+1];
		int b = data[3*i+2];
			
		int grey = 30*r + 59*g + 11*b;
		grey /= 100;

		/* Normalisieren, falls (sehr grosses falls) grey > 255 */
		if(grey > 255) { grey = 255; }
			
		dstData[3*i+0] = grey;
		dstData[3*i+1] = grey;
		dstData[3*i+2] = grey;
	}
}

void ColorConversion::ToRGB(const Image &src, Image &dst) {

	if(src.GetColorModel() == ImageBase::cm_Grey || 
		src.GetColorModel() == ImageBase::cm_RGB) {
		// do nothing 
		dst = src;
		dst.SetColorModel(ImageBase::cm_RGB);
		return;
	}

	dst.Init(src.GetWidth(), src.GetHeight());
	dst.SetColorModel(ImageBase::cm_HSV);

	unsigned int size = src.GetWidth()*src.GetHeight();
	const unsigned char *data = src.GetData();
	unsigned char *dstData = dst.GetData();

	for(unsigned int i = 0; i < size; i++) {
		// pixelwerte abrufen
		int hi = data[3*i+0];
		int si = data[3*i+1];
		int vi = data[3*i+2];

		// auf Bereich 0..1 bzw. 0..360 bringen
		float h = hi/255.0*360.0;
		float s = si/255.0;
		float v = vi/255.0;

		// Hilfsvariablen
		int h_i = floor(h/60.0);

		float f = h/60.0 - h_i;

		// Weitere Hilfsvariablen
		float p = v*(1-s);
		float q = v*(1-s*f);
		float t = v*(1-s*(1-f));

		/* Ergebniswerte */
		float r, g, b;

		/* Fallunterscheidung */
		switch(h_i) {
		case 0:
		case 6:
			r = v; g = t; b = p;
			break;
		case 1:
			r = q; g = v; b = p;
			break;
		case 2:
			r = p; g = v; b = t;
			break;
		case 3:
			r = p; g = q; b = v;
			break;
		case 4:
			r = t; g = p; b = v;
			break;
		case 5:
			r = v; g = p; b = q;
			break;
		default:
			assert(false);
		}

		/* auf Bereich 0..255 bringen */
		int ri = r*255;
		int gi = g*255;
		int bi = b*255;

		/* Speichern */
		dstData[3*i+0] = ri;
		dstData[3*i+1] = gi;
		dstData[3*i+2] = bi;
	}
	
}

void ColorConversion::ToHSV(const Image &src, Image &dst) {
	if(src.GetColorModel() == ImageBase::cm_HSV) {
		// do nothing
		dst = src;
		return;
	}

	dst.Init(src.GetWidth(), src.GetHeight());
	dst.SetColorModel(ImageBase::cm_HSV);

	unsigned int size = src.GetWidth()*src.GetHeight();
	const unsigned char *data = src.GetData();
	unsigned char *dstData = dst.GetData();

	for(unsigned int i = 0; i < size; i++) {

		// Ergebnisse
		float h;
		float s;
		float v;

		// pixelwerte abrufen
		int ri = data[3*i+0];
		int gi = data[3*i+1];
		int bi = data[3*i+2];

		// 0.0 entspricht 0, 1.0 entspricht 255
		float r = ri/255.0;
		float g = gi/255.0;
		float b = bi/255.0;

		float max = std::max(r, std::max(g, b));
		float min = std::min(r, std::min(g, b));

		/* hue berechnen */
		if(min == max) {
			h = 0; 
		} else if(max == r) {
			h = 60*(0 + (g-b)/(max-min));
		} else if(max == g) {
			h = 60*(2 + (b-r)/(max-min));
		} else if(max == b) {
			h = 60*(2 + (r-b)/(max-min));
		}

		if(h < 0) { h += 360; }

		/* saturation berechnen */
		if(max == 0) {
			s = 0;
		} else {
			s = (max-min)/max;
		}

		/* value berechnen */
		v = max;

		/* in Bereich 0..255 bringen */
		/* h kann maximal (eingeschlossen!) 360 annehmen */
		int hi = h/360.0*255.0;

		assert(hi < 256);

		int si = h*255;

		int vi = h*255;

		dstData[3*i+0] = hi;
		dstData[3*i+1] = si;
		dstData[3*i+2] = vi;

	}
}

} 
