/*
Gruppe: 02
Serie 11
Matthias Boehm, 895778
Hannes Georg, 850360
*/
 
#include "StructureTensor.hh"
 
namespace Graphics2D {

StructureTensor::StructureTensor(int filterSize) {
	// initialize filters
	filterGx_ = Filter::CreateGradX();
	filterGy_ = Filter::CreateGradY();
	filterBinomial_ = Filter::CreateBinomial(filterSize);
}

StructureTensor::~StructureTensor() {
	// delete filters
	delete filterGx_;
	delete filterGy_;
	delete filterBinomial_;
}

void StructureTensor::SetFromImage(const Image &input) {
	
	unsigned int width = input.GetWidth();
	unsigned int height = input.GetHeight();

	// Bestimme Gradienten
	gx_.Init(width, height);
	gy_.Init(width, height);
	
	filterGx_->FilterImage(input, gx_);
	filterGy_->FilterImage(input, gy_);
	
	// Bestime Produkt
	
	gxx_.Init(width, height);
	gxy_.Init(width, height);
	gyy_.Init(width, height);

	for(unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {
			gxx_.SetPixel(x, y, gx_.GetPixel(x, y)*gx_.GetPixel(x, y));
			gxy_.SetPixel(x, y, gx_.GetPixel(x, y)*gy_.GetPixel(x, y));
			gyy_.SetPixel(x, y, gy_.GetPixel(x, y)*gy_.GetPixel(x, y));
		}
	}
	
	// Bestimme mit Binomialfilter
	Jxx_.Init(width, height);
	Jxy_.Init(width, height);
	Jyy_.Init(width, height);
	
	filterBinomial_->FilterImage(gxx_, Jxx_);
	filterBinomial_->FilterImage(gxy_, Jxy_);
	filterBinomial_->FilterImage(gyy_, Jyy_);
}

void StructureTensor::FoerstnerDetector(float thres, Image &corners) {

	unsigned int width = Jxx_.GetWidth();
	unsigned int height = Jxx_.GetHeight();

	for(unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {

			// Werte lesen
			float jxx = Jxx_.GetPixel(x, y);
			float jyy = Jyy_.GetPixel(x, y);
			float jxy = Jxy_.GetPixel(x, y);

			// Spur und Determinante berechnen
			float trace = jxx+jyy;
			float det = jxx*jyy-jxy*jxy;

			// Schwelle beachten
			if(trace > thres) {
				// q berechnen
				float q = 4*det/(trace*trace);

				// Kante?
				if(q <= 0.5) {
					corners.SetPixel(x, y, 0, Color::green().GetR());
					corners.SetPixel(x, y, 1, Color::green().GetG());
					corners.SetPixel(x, y, 2, Color::green().GetB());
				} // Punkt
				else {
					corners.SetPixel(x, y, 0, Color::red().GetR());
					corners.SetPixel(x, y, 1, Color::red().GetG());
					corners.SetPixel(x, y, 2, Color::red().GetB());
				}
			}

		}
	}

}

void StructureTensor::HarrisCornerDetector(float thres, Image &corners) {

}

}

