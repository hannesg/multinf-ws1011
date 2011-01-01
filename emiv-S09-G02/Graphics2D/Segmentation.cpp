 
 
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

int Segmentation::GetFreemanCode(const int label, Coordinate &firstPoint, std::vector<int> &freemanCode) {
	
	bool firstPointFound = false;
	
	// Ersten Punkt finden
	for(unsigned int y = 0; y < labelImage_.GetHeight(); y++) {
		for(unsigned int x = 0; x < labelImage_.GetWidth(); x++) {
			if(labelImage_.GetPixel(x, y, 0) == label) {
				// Erster Punkt gefunden -> abspeichern
				firstPoint.SetX((int)x);
				firstPoint.SetY((int)y);
				firstPointFound = true;
				break;
			}
		}
	}

	if(!firstPointFound) { 
		return 1;
	}

	cout << "First point: (" << firstPoint.GetX() << ", " << firstPoint.GetY() << ")" << endl;
	
	
	
	return 0;
}

}
