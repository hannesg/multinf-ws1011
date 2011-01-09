 
#include <stdexcept> 
#include <cassert>
#include "ColorConversion.hh"
#include "Filter.hh"
#include "Segmentation.hh"



namespace Graphics2D {

Segmentation::Segmentation(const Image &inputImage) {
	if(inputImage.GetColorModel() == ImageBase::cm_RGB) {
		// Convert image to hsv
		ColorConversion::ToHSV(inputImage, hsvImage_);
		// init label image
		labelImage_.Init(inputImage.GetWidth(), inputImage.GetHeight());
		labelImage_.SetColorModel(ImageBase::cm_Grey);
		labelImage_.FillZero();
	} else if(inputImage.GetColorModel() == ImageBase::cm_HSV) {
		// store input image
		hsvImage_ = inputImage;
		// init label image
		labelImage_.Init(inputImage.GetWidth(), inputImage.GetHeight());
		labelImage_.SetColorModel(ImageBase::cm_Grey);
		labelImage_.FillZero();
	} else if(inputImage.GetColorModel() == ImageBase::cm_Grey) {
		// store input image as label image
		labelImage_ = inputImage;
	}
	
}

Segmentation::~Segmentation() {
	
}

void Segmentation::AddHueSegment(const int label, const int minHue, const int maxHue, const int minSat) {
	// Bild durchgehen
	for(unsigned int x = 0; x < hsvImage_.GetWidth(); x++) {
		for(unsigned int y = 0; y < hsvImage_.GetHeight(); y++) {
			
			// hue und saturation lesen
			unsigned char pixel = hsvImage_.GetPixel(x, y, 0);
			unsigned char sat = hsvImage_.GetPixel(x, y, 1);
			
			// Pruefen, ob in bounds
			if(minHue <= pixel && pixel <= maxHue && minSat <= sat) {
				labelImage_.SetPixel(x, y, 0, label);
				labelImage_.SetPixel(x, y, 1, label);
				labelImage_.SetPixel(x, y, 2, label);
			}
		}
	}
}

void Segmentation::ClosingOperation() {
	Image tmp;
	// einmal Dilation und Erosion durchfuehren
	Filter::Rank3x3(labelImage_, tmp, 8);
	Filter::Rank3x3(tmp, labelImage_, 0);
}

void Segmentation::GetLabelImage(Image &labelImage) {
	labelImage = labelImage_;
}

int Segmentation::GetCenterAndArea(const int label, Coordinate &center, int &area) {
	
	// Initialisierung
	center = Coordinate(0, 0);
	area = 0;
	
	// Bild durchgehen
	for(unsigned int i = 0; i < labelImage_.GetWidth(); i++) {
		for(unsigned int j = 0; j < labelImage_.GetHeight(); j++) {
			unsigned char pixel = labelImage_.GetPixel(i, j, 0);
			
			// Wenn pixel im Label ist, Flaeche erhoehen und Punkt hinzufuegen
			if(pixel == label) {
				area++;
				center += Coordinate(i, j);
			}
		}
	}
	
	// Mittelwert berechnen
	center /= area;
	
	if(area != 0) {
		return 0;
	} else {
		return 1;
	}
}

// helper function for freeman code
int add(int x, int c) {
	return (x+8+c)%8;
}

// return the next point specified by the freeman code f
Coordinate nextPoint(const Coordinate &c, int f) {
	switch(f) {
	case 0:
		return Coordinate(c.GetX()+1, c.GetY()+0);
	case 1:
		return Coordinate(c.GetX()+1, c.GetY()-1);
	case 2:
		return Coordinate(c.GetX()+0, c.GetY()-1);
	case 3:
		return Coordinate(c.GetX()-1, c.GetY()-1);
	case 4:
		return Coordinate(c.GetX()-1, c.GetY()+0);
	case 5:
		return Coordinate(c.GetX()-1, c.GetY()+1);
	case 6:
		return Coordinate(c.GetX()+0, c.GetY()+1);
	case 7:
		return Coordinate(c.GetX()+1, c.GetY()+1);
	default:
		throw out_of_range("illegal freeman code! ");
		return Coordinate(0, 0);
	}
}



int Segmentation::GetFreemanCode(const int label, Coordinate &firstPoint, std::vector<int> &freemanCode) {
	
	bool firstPointFound = false;
	bool secondPointFound = false;
	
	// Ersten Punkt finden
	for(unsigned int y = 0; y < labelImage_.GetHeight(); y++) {
		for(unsigned int x = 0; x < labelImage_.GetWidth(); x++) {
			if(labelImage_.GetPixel(x, y, 0) == label) {
				if(!firstPointFound) {
					// Erster Punkt gefunden -> abspeichern
					firstPoint.SetX((int)x);
					firstPoint.SetY((int)y);
					firstPointFound = true;
				} else if(!secondPointFound) {
					secondPointFound = true;
					break;
				}
			}
		}
	}

	if(!secondPointFound) {
		// nothing to do
		freemanCode.clear();
		return 0;
		// throw out_of_range("No contour: Single pixel! ");
	}

	if(!firstPointFound) { 
		return 1;
	}

	// cout << "First point: (" << firstPoint.GetX() << ", " << firstPoint.GetY() << ")" << endl;
	
	// pavlidis algorithm
	freemanCode.clear();
	Coordinate currentPoint = firstPoint;

	// Initialization
	int cb = 6;

	do {

		int ck = getFreemanCodeOfNextCoutourPoint(label, currentPoint, cb);

		// no contour point found?
		if(ck == -1) {
			cb = add(cb, 2);
		}
		else if(ck == cb || ck == add(cb, 1)) {
			// do not change direction
		} else if(ck == add(cb, -1)) {
			// change direction
			cb = add(cb, -2);
		}
		else {
			// should not happen
			throw exception();
		}
		if(ck != -1) {
			// store freeman code and get next point
			freemanCode.push_back(ck);
			currentPoint = nextPoint(currentPoint, ck);
		}
		
	} while(currentPoint != firstPoint);
	
	return 0;
}

int Segmentation::getFreemanCodeOfNextCoutourPoint(const int label, const Coordinate &c, int cb) const {

	// von rechts nach links durchgehen
	for(int i = -1; i <= 1; i++) {
		Coordinate cnew = nextPoint(c, add(cb, i));

		// is point within image?
		if(!labelImage_.isInImage(cnew)) {
			continue;
		}

		// has point the label?
		if(labelImage_.GetPixel(cnew.GetX(), cnew.GetY(), 0) == label) {
			return add(cb, i);
		}
	}

	// no point with label found
	return -1;
}

void Segmentation::DrawContourFreeman(const Coordinate firstPoint, const std::vector<int> &freemanCode, 
          const Color color, Image &targetImage) {

	// target image should be rgb
	if(targetImage.GetColorModel() != ImageBase::cm_RGB) {
		throw out_of_range("Color model wrong! ");
	}

	Coordinate currentPoint = firstPoint;

	for(unsigned int i = 0; i < freemanCode.size(); i++) {
		// paint contour point
		targetImage.SetPixel(currentPoint.GetX(), currentPoint.GetY(), 0, color.GetR());
		targetImage.SetPixel(currentPoint.GetX(), currentPoint.GetY(), 1, color.GetG());
		targetImage.SetPixel(currentPoint.GetX(), currentPoint.GetY(), 2, color.GetB());

		// get next point
		currentPoint = nextPoint(currentPoint, freemanCode[i]);
	}

	assert(currentPoint == firstPoint);

}

}
