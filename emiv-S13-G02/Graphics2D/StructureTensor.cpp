/*
Gruppe: 02
Serie 11
Matthias Boehm, 895778
Hannes Georg, 850360
*/
 
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <list>
#include "StructureTensor.hh"
#include "Coordinate.hh"

using namespace std;

namespace Graphics2D {

StructureTensor::StructureTensor(int filterSize) {

	if(filterSize % 2 != 1) {
		throw out_of_range("filtersize");
	}

	// initialize filters
	filterGx_ = Filter::CreateGradX();
	filterGy_ = Filter::CreateGradY();
	filterBinomial_ = Filter::CreateBinomial(filterSize);

	halfwinSize_ = (filterSize-1)/2;
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

// helping class
class CornerPoint {

public:
	Coordinate c;
	float value;

	bool operator <(const CornerPoint &c2) {
		if(this->value < c2.value) {
			return true; 
		} else if(this->value > c2.value) {
			return false;
		} else {
			int pos1 = c.GetX()  + c.GetY()*width;
			int pos2 = c2.c.GetX() + c2.c.GetY()*width;
			return pos1 < pos2;
		}
	}

	int width;

};

void StructureTensor::HarrisCornerDetector(float thres, Image &imgCorners) {
	
	vector <Coordinate> corners;
	HarrisCornerDetector(thres, corners);
	
	for(unsigned int i = 0; i < corners.size(); i++) {
		imgCorners.SetPixel(corners[i].GetX(), corners[i].GetY(), 0, Color::red().GetR());
		imgCorners.SetPixel(corners[i].GetX(), corners[i].GetY(), 1, Color::red().GetG());
		imgCorners.SetPixel(corners[i].GetX(), corners[i].GetY(), 2, Color::red().GetB());
	}
}

void StructureTensor::HarrisCornerDetector(float thres, vector<Coordinate> &outCorners) {
	unsigned int width = Jxx_.GetWidth();
	unsigned int height = Jxx_.GetHeight();

	// initialization
	harrisCornerImage_.Init(width, height);

	labelCornerImage_.Init(width, height);
	labelCornerImage_.SetColorModel(ImageBase::cm_Grey);
	labelCornerImage_.FillZero();

	// Berechne grey-scale-harris-corner image
	for(unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {

			// Werte lesen
			float jxx = Jxx_.GetPixel(x, y);
			float jyy = Jyy_.GetPixel(x, y);
			float jxy = Jxy_.GetPixel(x, y);

			// Spur und Determinante berechnen
			float trace = jxx+jyy;
			float det = jxx*jyy-jxy*jxy;

			// festlegung
			float k = 0.04;

			// implizite Funktion berechnen
			float ch = det - k*trace*trace;

			// in Bild speichern
			harrisCornerImage_.SetPixel(x, y, ch);

			// in label Image auch speichern, wenn Punkt
			if(ch > thres) {
				labelCornerImage_.SetPixel(x, y, 0, 255);
				labelCornerImage_.SetPixel(x, y, 1, 255);
				labelCornerImage_.SetPixel(x, y, 2, 255);
			}
		}
	}

	

	// Maximum ermitteln und non-maximum suppression
	// Dazu wird ein Fenster ueber das gesamte Bild geschoben, und nur wenn 
	// die "Punktflaeche" vollstaendig im Fenster ist, wird das Maximum ermittelt
	// und gefaerbt
	unsigned int window = 13;
	unsigned int halfwindow = (window-1)/2; 

	// einmal ueber gesamtes grayscale-Bild laufen, und jeweils Maximum ermitteln
	for(unsigned int y = halfwindow; y < height-halfwindow; y++) {
		for(unsigned int x = halfwindow; x < width-halfwindow; x++) {

			// In vier Schritten den gesamten Rand auf Punkte absuchen
			bool windowFits = true;

			// upper bound
			for(unsigned int i = x-halfwindow; i <= x+halfwindow; i++) {

				float p = harrisCornerImage_.GetPixel(i, y+halfwindow);
				if(p > thres) {
					windowFits = false;
					break;
				}
			}

			// lower bound
			for(unsigned int i = x-halfwindow; i <= x+halfwindow; i++) {

				float p = harrisCornerImage_.GetPixel(i, y-halfwindow);
				if(p > thres) {
					windowFits = false;
					break;
				}
			}

			// left bound
			for(unsigned int j = y-halfwindow; j <= y+halfwindow; j++) {

				float p = harrisCornerImage_.GetPixel(x-halfwindow, j);

				if(p > thres) {
					windowFits = false;
					break;
				}
			}

			// right bound
			for(unsigned int j = y-halfwindow; j <= y+halfwindow; j++) {

				float p = harrisCornerImage_.GetPixel(x+halfwindow, j);

				if(p > thres) {
					windowFits = false;
					break;
				}
			}

			// window ist nicht vollstaendig ueber punkt?
			if(!windowFits) {
				continue;
			}

			list<CornerPoint> points;

			// einmal ueber Bildausschnitt laufen, Punkte und Werte speichern
			for(unsigned int j = y-halfwindow; j <= y+halfwindow; j++) {

				for(unsigned int i = x-halfwindow; i <= x+halfwindow; i++) {

					float p = harrisCornerImage_.GetPixel(i, j);

					// add p to list of points
					if(p > thres) {

						CornerPoint pnt;
						pnt.c = Coordinate(i, j);
						pnt.value = p;
						pnt.width = width;

						points.push_back(pnt);
					}
				}
			}

			// wenn Vektor leer, kein Punkt
			if(points.empty()) {
				continue;
			}

			// sortiere Vektor
			points.sort();

			// print vector
			/* cout << "(" << x << ", " << y << ")" << endl;
			for(list<CornerPoint>::iterator i = points.begin(); i != points.end(); i++) {
				cout << i->value << " ";
			}
			cout << endl; */

			// Nehme maximalen Wert, und faerbe Bild an dieser Stelle 
			CornerPoint max = points.back();

			Coordinate newCorner = Coordinate(max.c.GetX(), max.c.GetY());
			
			// check, whether corner is already in list
			bool contained = false;

			for(vector<Coordinate>::iterator it = outCorners.begin(); it != outCorners.end(); it++) {

				if(*it == newCorner) {
					contained = true;
					break;
				}
			}
			
			if(!contained) {
				outCorners.push_back(newCorner);
			}

		}
	}

}

}

