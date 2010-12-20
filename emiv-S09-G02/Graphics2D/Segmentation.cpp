 
 
#include "ColorConversion.hh"
#include "Filter.hh"
#include "Segmentation.hh"



namespace Graphics2D {

Segmentation::Segmentation(const Image &inputImage) {
	if(inputImage.GetColorModel() == ImageBase::cm_RGB) {
		ColorConversion::ToHSV(inputImage, hsvImage_);
		labelImage_.Init(inputImage.GetWidth(), inputImage.GetHeight());
		labelImage_.SetColorModel(ImageBase::cm_Grey);
		labelImage_.FillZero();
	} else if(inputImage.GetColorModel() == ImageBase::cm_HSV) {
		hsvImage_ = inputImage;
		labelImage_.Init(inputImage.GetWidth(), inputImage.GetHeight());
		labelImage_.SetColorModel(ImageBase::cm_Grey);
		labelImage_.FillZero();
	} else if(inputImage.GetColorModel() == ImageBase::cm_Grey) {
		labelImage_ = inputImage;
	}
	
}

Segmentation::~Segmentation() {
	
}

void Segmentation::AddHueSegment(const int label, const int minHue, const int maxHue, const int minSat) {
	for(unsigned int x = 0; x < hsvImage_.GetWidth(); x++) {
		for(unsigned int y = 0; y < hsvImage_.GetHeight(); y++) {
			unsigned char pixel = hsvImage_.GetPixel(x, y, 0);
			unsigned char sat = hsvImage_.GetPixel(x, y, 1);
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
	Filter::Rank3x3(labelImage_, tmp, 8);
	Filter::Rank3x3(tmp, labelImage_, 0);
}

void Segmentation::GetLabelImage(Image &labelImage) {
	labelImage = labelImage_;
}

int Segmentation::GetCenterAndArea(const int label, Coordinate &center, int &area) {
	
	center = Coordinate(0, 0);
	area = 0;
	
	for(unsigned int i = 0; i < labelImage_.GetWidth(); i++) {
		for(unsigned int j = 0; j < labelImage_.GetHeight(); j++) {
			unsigned char pixel = labelImage_.GetPixel(i, j, 0);
						
			if(pixel == label) {
				area++;
				center += Coordinate(i, j);
			}
		}
	}
	
	center /= area;
	
	if(area != 0) {
		return 0;
	} else {
		return 1;
	}
}

}
