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
	// nothing
}

HoughTransform::~HoughTransform() {
	// nothing
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
	GetLines_(houghspace_.GetWidth(), houghspace_.GetHeight(), lines);
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
					
					float myPhi = phi;
					float rad = myPhi/180.0*M_PI;
					
					int d = cos(rad)*x + sin(rad)*y;
					
					/* if(d < 0) {
						// Normalenvektor umkehren
						d = -d;
						myPhi += 180;
						// cerr << "Error: d< 0 " << phi << " " << rad << endl;
					} */
					
					int bin = floor(myPhi*resolution);
					
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

	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {

			if(houghspaceMax_.GetPixel(x, y) != 0) {

				// get d
				float d = y-maxD_;

				// print maximum for debugging purposes
				cout << "Maximum found at deg: " << x << ", d: " << d << "! " << endl;

				// re-get phi information
				float phiGrad = x/resolution_;

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

					// Berechne tatsaechliche Punkte
					float ps_x, ps_y;
					float pd_x, pd_y;

					if(0 <= y1 && y1 <= imHeight) {
						ps_x = 0; 
						ps_y = y1;
					} else if(0 <= y2 && y2 <= imHeight) {
						ps_x = imWidth;
						ps_y = y2;
					} else {
						assert(false);
					}

					if(0 <= x1 && x1 <= imWidth) {
						pd_x = x1;
						pd_y = 0;
					} else if(0 <= x2 && x2 <= imWidth) {
						pd_x = x2;
						pd_y = imHeight;
					} else {
						assert(false);
					}
					
					lines.push_back(PrimitiveLine(ps_x, ps_y, pd_x, pd_y));

				}

				cout << "Created Line from (" << lines.back().GetStartingPoint().GetX() <<
					", " << lines.back().GetStartingPoint().GetY() << 
					" to (" << lines.back().GetEndingPoint().GetX() << 
					", " << lines.back().GetEndingPoint().GetY() << ")!" << endl;
			}

		}
	}

}
}
