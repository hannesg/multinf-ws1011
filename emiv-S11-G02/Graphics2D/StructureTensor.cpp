/*
Gruppe: 02
Serie 11
Matthias Boehm, 895778
Hannes Georg, 850360
*/
 
#include "StructureTensor.hh"
 
namespace Graphics2D {

StructureTensor::StructureTensor(int filterSize) {
	filterGx_ = Filter::CreateGradX();
	filterGy_ = Filter::CreateGradY();
	filterBinomial_ = Filter::CreateBinomial(filterSize);
}

StructureTensor::~StructureTensor() {
	delete filterGx_;
	delete filterGy_;
	delete filterBinomial_;
}

void StructureTensor::SetFromImage(const Image &input) {
	
	// Bestimme Gradienten
	gx_.Init(input.GetWidth(), input.GetHeight());
	gy_.Init(input.GetWidth(), input.GetHeight());
	
	filterGx_->FilterImage(input, gx_);
	filterGy_->FilterImage(input, gy_);
	
	// Bestime Produkt
	
	gxx_.Init(input.GetWidth(), input.GetHeight());
	gxy_.Init(input.GetWidth(), input.GetHeight());
	gyy_.Init(input.GetWidth(), input.GetHeight());
	
	for(unsigned int y = 0; y < input.GetHeight(); y++) {
		for(unsigned int x = 0; x < input.GetWidth(); x++) {
			gxx_.SetPixel(x, y, gx_.GetPixel(x, y)*gx_.GetPixel(x, y));
			gxy_.SetPixel(x, y, gx_.GetPixel(x, y)*gy_.GetPixel(x, y));
			gyy_.SetPixel(x, y, gy_.GetPixel(x, y)*gy_.GetPixel(x, y));
		}
	}
	
	// Bestimme mit Binomialfilter
	
	Jxx_.Init(input.GetWidth(), input.GetHeight());
	Jxy_.Init(input.GetWidth(), input.GetHeight());
	Jyy_.Init(input.GetWidth(), input.GetHeight());
	
	filterBinomial_->FilterImage(gxx_, Jxx_);
	filterBinomial_->FilterImage(gxy_, Jxy_);
	filterBinomial_->FilterImage(gyy_, Jyy_);
}

void StructureTensor::FoerstnerDetector(float thres, Image &corners) {
}

void StructureTensor::HarrisCornerDetector(float thres, Image &corners) {
}

}
