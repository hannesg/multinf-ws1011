/*
Gruppe: 02
Serie 12
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <Graphics2D/HoughTransform.hh>
#include <cassert>

using namespace std;

namespace Graphics2D {

HoughTransform::HoughTransform() {
	houghspace_.FillZero();
	houghspaceMax_.FillZero();
}

HoughTransform::~HoughTransform() {
	
}


void HoughTransform::StandardHoughTransform(const Image &input, const int resolution, vector<PrimitiveLine> &lines) {
	// call Create2DHistogram_
	Create2DHistogram_(input, resolution);
	// apply non maximum suppression
	Filter::NonMaximumSuppression(houghspace_, houghspaceMax_, 200);
	// save houghimage for debugging (optional)
	Image tmp;
	houghspaceMax_.GetAsGreyImage(tmp);
	tmp.SavePPM("tmp_houghspace_after_max_suppr.ppm");
	
	// call GetLines_
	GetLines_(input.GetWidth(), input.GetHeight(), lines);
}

void HoughTransform::FastHoughTransform(const StructureTensor &input, const int resolution, vector<PrimitiveLine> &lines) {
	// call Create2DHistogramFromStructureTensor_
	// apply non maximum suppression
	// save hough image for debugging (optional)
	// call GetLines_ (extend StructureTensor class for getting width and height)
}

// ---- protected

void HoughTransform::Create2DHistogram_(const Image &input, const int resolution) {
	// calculate hough transform
	// for all pixels with magnitude of gradients > 100 (fixed threshold)
	int width = input.GetWidth();
	int height = input.GetHeight();
	const int threshold = 50;
	resolution_ = resolution;
	
	Image filtered = input;
	Filter::FilterGradMag(input, filtered);
	Image mask;
	mask.Init(width, height); 
	mask.FillZero();
		
	// consider needed size for 2d histogram!
	
	// Init hough space
	maxD_ = ceil(sqrt(pow(width, 2.0) + pow(height, 2.0)));
	
	houghspace_.Init(180*resolution, 2*maxD_);
	
	// create histogram
	
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			
			// over threshold?
			if(filtered.GetPixel(x, y, 0) > threshold) {
			// if(true) {
				// debugging
				mask.SetPixel(x, y, 0, 255);
				mask.SetPixel(x, y, 1, 255);
				mask.SetPixel(x, y, 2, 255);
				
				for(float phi = 0; phi < 180; phi += 1.0/resolution) {
					
					float rad = phi/180.0*M_PI;
					
					int d = cos(rad)*(float)x + sin(rad)*(float)y;
					
					int bin = phi*resolution;
					
					houghspace_.SetPixel(bin, d+maxD_, 
										 houghspace_.GetPixel(bin, d+maxD_)+1);
				}
			}
			
		}
	}
	
	// debugging
	mask.SavePPM("tmp_mask1.ppm");
	
}

void HoughTransform::Create2DHistogramFromStructureTensor_(const StructureTensor &input, const int resolution) {
	// get elements of structure tensor  (extend StructureTensor class for getting Jxx, Jxy, Jyy)
	// calculate hough transform using structure tensor orientation
	// consider needed size for 2d histogram!
	// save hough image for debugging
}


void HoughTransform::GetLines_(int imWidth, int imHeight, std::vector<PrimitiveLine> &lines) {
	// for each pixel != 0 in hough space
	// calculate a line from one image border to another
	// by calculating the intersection points with the image borders
	// consider vertical/horizontal lines, you might need to consider different cases

	assert(houghspaceMax_.Valid());
	int width = houghspaceMax_.GetWidth();
	int height = houghspaceMax_.GetHeight();
	cout << "Image size: " << imWidth << ", " << imHeight << endl;

	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {

			if(houghspaceMax_.GetPixel(x, y) != 0) {

				// get d
				float d = y-maxD_;

				// print maximum for debugging purposes
				cout << "Maximum found at deg: " << x << ", d: " << d << "! " << endl;

				// re-get phi information
				float phiGrad = ((float)x)/resolution_;

				if(d < 0) {
					// Normalenvektor umkehren
					phiGrad += 180;
					d = -d;
				}

				// print new maximum: 
				cout << "    That is deg: " << phiGrad << ", d: " << d << "! " << endl;

				// ************** compute line **************//

				float phiRad = phiGrad/180.0*M_PI;

				// horizontale Linie
				if(phiGrad == 90) {
					lines.push_back(PrimitiveLine(0, d, imWidth, d));
				} else if(phiGrad == 270) {
					lines.push_back(PrimitiveLine(0, -d, imWidth, -d));
				}
				// vertikale Linie
				else if(phiGrad == 0) {
					lines.push_back(PrimitiveLine(d, 0, d, imHeight));
				} else if(phiGrad == 180) {
					lines.push_back(PrimitiveLine(-d, 0, -d, imHeight));
				}
				// keine der Spezialfaelle
				else {

					// Berechne Normalenvektor
					float nx = cos(phiRad);
					float ny = sin(phiRad);

					// Berechne Schnittpunkte mit Achsen
					float y1 = d/ny;
					float x1 = d/nx;

					float y2 = (d-nx*imWidth)/ny;
					float x2 = (d-ny*imHeight)/nx;

					float px[4];
					float py[4];

					px[0] = 0;
					py[0] = y1;

					px[1] = x1;
					py[1] = 0;

					px[2] = imWidth;
					py[2] = y2;

					px[3] = x2;
					py[3] = imHeight;

					/* cout << "Points: " << endl;
					for(int i = 0; i < 4; i++) {
						cout << "    (" << px[i] << " " << py[i] << ")" << endl;
					} */

					// Berechne tatsaechliche Punkte

					int i1 = 0;

					// ermittele ersten Punkt
					while(i1 < 4) {

						if(0 <= px[i1] && px[i1] <= imWidth
							&& 0 <= py[i1] && py[i1] <= imHeight) {
								break;
						} else {
							i1++;
						}
					}

					// keinen Punkt gefunden?
					if(i1 == 4) {
						cerr << "Gerade ausserhalb des Bildbereichs! " << endl;
					}

					// ermittele zweiten (verschiedenen!) Punkt

					int i2 = i1+1;

					while(i2 < 4) {

						if(0 <= px[i2] && px[i2] <= imWidth
							&& 0 <= py[i2] && py[i2] <= imHeight
							// verschieden!
							&& (px[i1] != px[i2] || py[i1] != py[i2])) {
								break;
						} else {
							i2++;
						}

					}

					// keinen Punkt gefunden?
					if(i2 == 4) {
						// Gerade geht durch Ecke
						i2 = i1;
					}
					
					lines.push_back(PrimitiveLine(px[i1], py[i1], px[i2], py[i2]));

				}

				cout << "Created Line from (" << lines.back().GetStartingPoint().GetX() <<
					", " << lines.back().GetStartingPoint().GetY() << 
					") to (" << lines.back().GetEndingPoint().GetX() << 
					", " << lines.back().GetEndingPoint().GetY() << ")!" << endl;
			}

		}
	}

}
}
